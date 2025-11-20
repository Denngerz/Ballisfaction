
#include "BallisfactionGameMode.h"

#include "BallisfactionProject/RoundConfigSubsystem.h"
#include "BallisfactionProject/Subsystems/WorldSubsystems/SpawnSubsystem/BrickSpawnSubsystem/BallisfactionBrickSpawnSubsystem.h"
#include "BallisfactionProject/GameState/BallisfactionGameState.h"
#include "BallisfactionProject/Subsystems/WorldSubsystems/SpawnSubsystem/BallSpawnSubsystem/BallisfactionBallsSpawnSubsystem.h"

ABallisfactionGameMode::ABallisfactionGameMode()
	:MaxBallsOnMap(5),
	BrickRowsAmount(1),
	RoundNumber(0),
	RoundTime(45),
	BrickTiersSpawnTable(nullptr),
	BallsTiersSpawnTable(nullptr)
{
}

void ABallisfactionGameMode::BeginPlay()
{
	Super::BeginPlay();

	UBallisfactionBrickSpawnSubsystem* BrickSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBrickSpawnSubsystem>();
	if (BrickSpawnSubsystem && BrickTiersSpawnTable)
	{
		BrickSpawnSubsystem->UpdateTiersDataTableInfo(BrickTiersSpawnTable);
	}
	
	UBallisfactionBallsSpawnSubsystem* BallSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBallsSpawnSubsystem>();
	if (BallSpawnSubsystem && BallsTiersSpawnTable)
	{
		BallSpawnSubsystem->UpdateTiersDataTableInfo(BallsTiersSpawnTable);
	}

	URoundConfigSubsystem* RoundConfigSubsystem = GetWorld()->GetSubsystem<URoundConfigSubsystem>();
	if (RoundConfigSubsystem && BrickTiersSpawnTable && BallsTiersSpawnTable)
	{
		RoundConfigSubsystem->InitializeSpawnChances(BallsTiersSpawnTable, BrickTiersSpawnTable);
	}
	
	StartNextRound();
}
 
int32 ABallisfactionGameMode::GetMaxBallsOnMap()
{
	return MaxBallsOnMap;
}

int32 ABallisfactionGameMode::GetRoundNumber()
{
	return RoundNumber;
}

int32 ABallisfactionGameMode::GetBrickRowsAmount()
{
	return BrickRowsAmount;
}

void ABallisfactionGameMode::AddNewBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS) 
	{
		BallisfactionGS->AddNewBall();
	}
}

void ABallisfactionGameMode::RemoveExistingBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS)
	{
		BallisfactionGS->RemoveExistingBall();
	}
}

bool ABallisfactionGameMode::CanSpawnNewBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS)
	{ 
		return BallisfactionGS->GetCurrentBallsAmount() < MaxBallsOnMap;
	}

	return false;
}

void ABallisfactionGameMode::StartNextRound()
{
	RoundNumber++;
	
	URoundConfigSubsystem* RoundConfigSubsystem = GetWorld()->GetSubsystem<URoundConfigSubsystem>();
	if (RoundConfigSubsystem)
	{
		RoundConfigSubsystem->ConfigureNewSpawnChancesInfo(RoundNumber);
	}

	CalculateBrickRowsAmount();
	CalculateRoundTime();

	StartRoundTimer();
}

void ABallisfactionGameMode::StopRound()
{
	OnRoundEnd.Broadcast();
}

void ABallisfactionGameMode::CalculateBrickRowsAmount()
{
	BrickRowsAmount = 1 + RoundNumber / 3;

	BrickRowsAmount = FMath::Min(5, BrickRowsAmount);
}

void ABallisfactionGameMode::CalculateRoundTime()
{
	RoundTime = RoundTime + ((RoundNumber / 5) * 15.0f);
}

void ABallisfactionGameMode::StartRoundTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
	RoundTimerHandle,
	this,
	&ABallisfactionGameMode::StopRound,
	0.f,
	false,
	RoundTime
);
}
