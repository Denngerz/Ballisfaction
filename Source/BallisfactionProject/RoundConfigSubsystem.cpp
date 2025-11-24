
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
	for (auto& Tier : BallsRuntimeTiers)
	{
		Tier.TierPickChance += RoundNumber * Tier.RoundModificator;
	}

	TransferBallsSpawnChances();
}

void URoundConfigSubsystem::ConfigureNewBrickSpawnChances(const int32 RoundNumber)
{
	for (auto& Tier : BricksRuntimeTiers)
	{
		Tier.TierPickChance += RoundNumber * Tier.RoundModificator;
	}
	
	TransferBricksSpawnChances();
}

void URoundConfigSubsystem::InitializeBallsSpawnChances(UDataTable* BallTierSpawnChances)
{
	TArray<FSpawnDataTableEntry*> BallTiersRows;
	BallTierSpawnChances->GetAllRows(TEXT("BallsTierSpawn"), BallTiersRows);

	int RowsAmmount = BallTiersRows.Num();
	BallsRuntimeTiers.SetNum(RowsAmmount);
	
	for (int i = 0; i < RowsAmmount; ++i)
	{
		BallsRuntimeTiers[i].TierType         = BallTiersRows[i]->TierType;
		BallsRuntimeTiers[i].TierPickChance   = BallTiersRows[i]->TierPickChance;
		BallsRuntimeTiers[i].RoundModificator = BallTiersRows[i]->RoundModificator;
	}
}

void URoundConfigSubsystem::InitializeBricksSpawnChances(UDataTable* BrickTierSpawnChances)
{
	TArray<FSpawnDataTableEntry*> BrickTiersRows;
	BrickTierSpawnChances->GetAllRows(TEXT("BricksTierSpawn"), BrickTiersRows);

	int RowsAmmount = BrickTiersRows.Num();
	BricksRuntimeTiers.SetNum(RowsAmmount);
	
	for (int i = 0; i < RowsAmmount; ++i)
	{
		BricksRuntimeTiers[i].TierType         = BrickTiersRows[i]->TierType;
		BricksRuntimeTiers[i].TierPickChance   = BrickTiersRows[i]->TierPickChance;
		BricksRuntimeTiers[i].RoundModificator = BrickTiersRows[i]->RoundModificator;
	}
}

void URoundConfigSubsystem::TransferBallsSpawnChances()
{
	UBallisfactionBallsSpawnSubsystem* BallsSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBallsSpawnSubsystem>();
	if (BallsSpawnSubsystem)
	{
		for (auto Tier : BallsRuntimeTiers)
		{
			BallsSpawnSubsystem->SetTierPickChance(Tier.TierPickChance, Tier.TierType);
		}
	}
}

void URoundConfigSubsystem::TransferBricksSpawnChances()
{
	UBallisfactionBrickSpawnSubsystem* BrickSpawnSubsystem = GetWorld()->GetSubsystem<UBallisfactionBrickSpawnSubsystem>();
	if (BrickSpawnSubsystem)
	{
		for (auto Tier : BricksRuntimeTiers)
		{
			BrickSpawnSubsystem->SetTierPickChance(Tier.TierPickChance, Tier.TierType);
		}
	}
}


