
#include "BallisfactionBrickHolder.h"
#include "BallisfactionBrick.h"
#include "BallisfactionProject/Subsystems/WorldSubsystems/SpawnSubsystem/BrickSpawnSubsystem/BallisfactionBrickSpawnSubsystem.h"

void ABallisfactionBrickHolder::UpdateBrickClass()
{
	UBallisfactionBrickSpawnSubsystem* Subsystem = GetWorld()->GetSubsystem<UBallisfactionBrickSpawnSubsystem>();
	BrickClass = Subsystem->GetBrickClassToSpawn();
}

void ABallisfactionBrickHolder::SpawnBrick()
{
	ShouldRespawnBrick = true;
	
	UpdateBrickClass();
	
	if (IsValid(Brick))
	{
		Brick->Destroy();
		Brick = nullptr;
		HandleBrickDestroyed();
	}
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	const FTransform SpawnTransform = GetActorTransform();

	ABallisfactionBrick* NewBrick  = World->SpawnActor<ABallisfactionBrick>(
		BrickClass,
		SpawnTransform,
		SpawnParams
	);

	if (!IsValid(NewBrick))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn brick for %s"), *GetName());
		return;
	}

	Brick = NewBrick;
	
	Brick->OnBrickDestroyed.AddDynamic(this, &ABallisfactionBrickHolder::HandleBrickDestroyed);
}

void ABallisfactionBrickHolder::HandleBrickDestroyed()
{
	if (ShouldRespawnBrick)
	{
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &ABallisfactionBrickHolder::SpawnBrick, 1.0f, false, 1.0f);
	}
}

ABallisfactionBrick* ABallisfactionBrickHolder::GetBrick()
{
	return Brick;
}
