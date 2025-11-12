
#include "BallisfactionBrickHolder.h"
#include "BallisfactionBrick.h"

void ABallisfactionBrickHolder::SetBrickClass(TSubclassOf<ABallisfactionBrick> NewBrickClass)
{
	BrickClass = NewBrickClass;
}

void ABallisfactionBrickHolder::BeginPlay()
{
	Super::BeginPlay();

	SpawnBrick();
}

void ABallisfactionBrickHolder::SpawnBrick()
{
	if (IsValid(Brick))
	{
		Brick->Destroy();
		Brick = nullptr;
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
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ABallisfactionBrickHolder::SpawnBrick, 1.0f, false, 1.0f);
}
