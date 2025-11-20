
#include "RoundConfigSubsystem.h"

#include "Subsystems/WorldSubsystems/SpawnSubsystem/BallSpawnSubsystem/BallisfactionBallsSpawnSubsystem.h"
#include "Subsystems/WorldSubsystems/SpawnSubsystem/BrickSpawnSubsystem/BallisfactionBrickSpawnSubsystem.h"

void URoundConfigSubsystem::InitializeSpawnChances(UDataTable* BallTierSpawnChances, UDataTable* BrickTierSpawnChances)
{
	InitializeBallsSpawnChances(BallTierSpawnChances);
	InitializeBricksSpawnChances(BrickTierSpawnChances);
}

void URoundConfigSubsystem::ConfigureNewSpawnChancesInfo(int32 RoundNumber)
{
	ConfigureNewBallSpawnChances(RoundNumber);
	ConfigureNewBrickSpawnChances(RoundNumber);
}

void URoundConfigSubsystem::ConfigureNewBallSpawnChances(int32 RoundNumber)
{
	LegendaryBallPickChance += RoundNumber * 2.0f;
	RareBallPickChance += RoundNumber * 1.5f;
	CommonBallPickChance += RoundNumber * 1.0f;

	TransferBallsSpawnChances();
}

void URoundConfigSubsystem::ConfigureNewBrickSpawnChances(const int32 RoundNumber)
{
	LegendaryBrickPickChance += RoundNumber * 2.0f;
	RareBrickPickChance += RoundNumber * 1.5f;
	CommonBrickPickChance += RoundNumber * 1.0f;
	
	TransferBricksSpawnChances();
}

void URoundConfigSubsystem::InitializeBallsSpawnChances(UDataTable* BallTierSpawnChances)
{
	BallTierDefaultSpawnChances = BallTierSpawnChances;

	TArray<FSpawnDataTableEntry*> Rows;
	BallTierDefaultSpawnChances->GetAllRows(TEXT("BallsTierSpawn"), Rows);

	if (Rows.Num() < 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Ball Tier Spawn DT MUST contain 3 rows."));
		return;
	}

	LegendaryBallPickChance = Rows[0]->TierPickChance;
	RareBallPickChance = Rows[1]->TierPickChance;
	CommonBallPickChance = Rows[2]->TierPickChance;
}

void URoundConfigSubsystem::InitializeBricksSpawnChances(UDataTable* BrickTierSpawnChances)
{
	BrickTierDefaultSpawnChances = BrickTierSpawnChances;

	TArray<FSpawnDataTableEntry*> Rows;
	BrickTierDefaultSpawnChances->GetAllRows(TEXT("BricksTierSpawn"), Rows);

	if (Rows.Num() < 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Brick Tier Spawn DT MUST contain 3 rows."));
		return;
	}

	LegendaryBrickPickChance = Rows[0]->TierPickChance;
	RareBrickPickChance = Rows[1]->TierPickChance;
	CommonBrickPickChance = Rows[2]->TierPickChance;
}

void URoundConfigSubsystem::TransferBallsSpawnChances()
{
	UBallisfactionBallsSpawnSubsystem* BallsSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBallsSpawnSubsystem>();
	if (BallsSpawnSubsystem)
	{
		BallsSpawnSubsystem->SetTierPickChance(LegendaryBallPickChance, ETierType::Legendary);
		BallsSpawnSubsystem->SetTierPickChance(RareBallPickChance, ETierType::Rare);
		BallsSpawnSubsystem->SetTierPickChance(CommonBallPickChance, ETierType::Common);
	}
}

void URoundConfigSubsystem::TransferBricksSpawnChances()
{
	UBallisfactionBrickSpawnSubsystem* BrickSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBrickSpawnSubsystem>();
	if (BrickSpawnSubsystem)
	{
		BrickSpawnSubsystem->SetTierPickChance(LegendaryBrickPickChance, ETierType::Legendary);
		BrickSpawnSubsystem->SetTierPickChance(RareBrickPickChance, ETierType::Rare);
		BrickSpawnSubsystem->SetTierPickChance(CommonBrickPickChance, ETierType::Common);
	}
}


