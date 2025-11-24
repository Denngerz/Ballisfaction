#include "BallisfactionBallsSpawnSubsystem.h"
#include "BallisfactionProject/Structures/SpawnDataTableEntry.h"

void UBallisfactionBallsSpawnSubsystem::UpdateTiersDataTableInfo(UDataTable* NewTiersDataTable)
{
	TiersDataTable = NewTiersDataTable;

	TArray<FSpawnDataTableEntry*> BallTiersRows;
	TiersDataTable->GetAllRows(TEXT("Context"), BallTiersRows);

	int32 RowsAmount = BallTiersRows.Num();
	RuntimeTiers.SetNum(RowsAmount);

	for (int32 i = 0; i < RowsAmount; ++i)
	{
		RuntimeTiers[i].TierType        = BallTiersRows[i]->TierType;
        RuntimeTiers[i].TierPickChance  = BallTiersRows[i]->TierPickChance;
		RuntimeTiers[i].DataTable       = BallTiersRows[i]->DataTable;
		RuntimeTiers[i].TotalWeight     = CalculateOverallChanceForTierDT(RuntimeTiers[i].DataTable);
	}
}

UDataTable* UBallisfactionBallsSpawnSubsystem::GetTiersDataTable()
{
	return TiersDataTable;
}

void UBallisfactionBallsSpawnSubsystem::SetTierPickChance(float NewTierPickChance, ETierType TierType)
{
	for (auto& BallTier : RuntimeTiers)
	{
		if (BallTier.TierType == TierType)
		{
			BallTier.TierPickChance = NewTierPickChance;
		}
	}
}

TSubclassOf<ABallisfactionBall> UBallisfactionBallsSpawnSubsystem::GetBallClassToSpawn()
{
	const UDataTable* TierDT = GetRandomTier();
	if (!TierDT)
	{
		return nullptr;
	}

	const FBallTier* Row = GetRandomRowFromTier(TierDT);
	if (!Row)
	{
		return nullptr;
	}

	return Row->BallClass;
}

float UBallisfactionBallsSpawnSubsystem::CalculateOverallChanceForTierDT(const UDataTable* TierDT)
{
	TArray<FBallTier*> TierRows;
	TierDT->GetAllRows(TEXT("Context"), TierRows);

	float Total = 0.f;
	for (const auto& Row : TierRows)
	{
		Total += Row->ChanceToBeSpawned;
	}

	return Total;
}

UDataTable* UBallisfactionBallsSpawnSubsystem::GetRandomTier()
{
	if (RuntimeTiers.IsEmpty())
	{
		return nullptr;
	}

	float OverallWeight = 0.f;
	for (const auto& BallTier : RuntimeTiers)
	{
		OverallWeight += BallTier.TierPickChance;
	}

	float Roll = FMath::FRandRange(0.f, OverallWeight);

	for (const auto& BallTier : RuntimeTiers)
	{
		if (Roll <= BallTier.TierPickChance)
		{
			return BallTier.DataTable;
		}

		Roll -= BallTier.TierPickChance;
	}

	return nullptr;
}

FBallTier* UBallisfactionBallsSpawnSubsystem::GetRandomRowFromTier(const UDataTable* TierDT)
{
	if (!TierDT) return nullptr;

	TArray<FBallTier*> Rows;
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
