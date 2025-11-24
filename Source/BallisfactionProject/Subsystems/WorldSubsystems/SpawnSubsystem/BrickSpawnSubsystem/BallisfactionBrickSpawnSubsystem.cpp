
#include "BallisfactionBrickSpawnSubsystem.h"
#include "BallisfactionProject/Structures/SpawnDataTableEntry.h"

void UBallisfactionBrickSpawnSubsystem::UpdateTiersDataTableInfo(UDataTable* NewTiersDataTable)
{
	TiersDataTable = NewTiersDataTable;
	
	TArray<FSpawnDataTableEntry*> BricksTiersRows;
	TiersDataTable->GetAllRows(TEXT("Context"), BricksTiersRows);

	int TiersRowsAmount = BricksTiersRows.Num();
	RuntimeTiers.SetNum(TiersRowsAmount);

	for (int i = 0; i < TiersRowsAmount; ++i)
	{
		RuntimeTiers[i].TierType       = BricksTiersRows[i]->TierType;
		RuntimeTiers[i].TierPickChance = BricksTiersRows[i]->TierPickChance;
		RuntimeTiers[i].DataTable      = BricksTiersRows[i]->DataTable;
		RuntimeTiers[i].TotalWeight    = CalculateOverallChanceForTierDT(RuntimeTiers[i].DataTable);
	}
}

UDataTable* UBallisfactionBrickSpawnSubsystem::GetTiersDataTable()
{
	return TiersDataTable;
}

void UBallisfactionBrickSpawnSubsystem::SetTierPickChance(float NewTierPickChance, ETierType TierType)
{
	for (auto& BrickTier : RuntimeTiers)
	{
		if (BrickTier.TierType == TierType)
		{
			BrickTier.TierPickChance = NewTierPickChance;
		}
	}
}

TSubclassOf<ABallisfactionBrick> UBallisfactionBrickSpawnSubsystem::GetBrickClassToSpawn()
{
	const UDataTable* TierDT = GetRandomTier();
	if (!TierDT)
	{
		return nullptr;
	}
	
	const FBrickTier* Row = GetRandomRowFromTier(TierDT);
	if (!Row)
	{
		return nullptr;
	}

	return Row->BrickClass;
}

float UBallisfactionBrickSpawnSubsystem::CalculateOverallChanceForTierDT(const UDataTable* TierDT)
{
	TArray<FBrickTier*> TierRows;
	TierDT->GetAllRows(TEXT("Context"), TierRows);

	float TierOverallChance = 0;
	for (auto Row : TierRows)
	{
		TierOverallChance += Row->ChanceToBeSpawned;
	}

	return TierOverallChance;
}

UDataTable* UBallisfactionBrickSpawnSubsystem::GetRandomTier()
{
	if (RuntimeTiers.IsEmpty())
	{
		return nullptr;
	}
	
	float OverallWeight = 0;
	for (const auto& BrickTier : RuntimeTiers)
	{
		OverallWeight += BrickTier.TierPickChance;
	}

	float RandomRoll = FMath::FRandRange(0.f, OverallWeight);

	for (const auto& BrickTier  : RuntimeTiers)
	{
		if (RandomRoll <= BrickTier.TierPickChance)
		{
			return BrickTier.DataTable;
		}

		RandomRoll -= BrickTier.TierPickChance;
	}
	return nullptr;
}

FBrickTier* UBallisfactionBrickSpawnSubsystem::GetRandomRowFromTier(const UDataTable* TierDT)
{
	if (!TierDT) return nullptr;

	TArray<FBrickTier*> Rows;
	TierDT->GetAllRows(TEXT("Context"), Rows);

	float TotalWeight = 0.f;
	for (const auto& Row : Rows)
	{
		TotalWeight += Row->ChanceToBeSpawned;
	}

	float Roll = FMath::FRandRange(0.f, TotalWeight);

	for (const auto& Row : Rows)
	{
		if (Roll < Row->ChanceToBeSpawned)
		{
			return Row;
		}
		Roll -= Row->ChanceToBeSpawned;
	}

	return nullptr;
}