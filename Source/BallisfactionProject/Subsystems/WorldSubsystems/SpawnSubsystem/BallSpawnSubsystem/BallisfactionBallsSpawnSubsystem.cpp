
#include "BallisfactionBallsSpawnSubsystem.h"
#include "BallisfactionProject/Structures/SpawnDataTableEntry.h"

void UBallisfactionBallsSpawnSubsystem::UpdateTiersDataTableInfo(UDataTable* NewTiersDataTable)
{
	TiersDataTable = NewTiersDataTable;
	
	TiersDataTable->GetAllRows(TEXT("Context"), TiersRows);

	for (auto Row : TiersRows)
	{
		Row->TotalWeight = CalculateOverallChanceForTierDT(Row->DataTable);
	}
}

UDataTable* UBallisfactionBallsSpawnSubsystem::GetTiersDataTable()
{
	return TiersDataTable;
}

void UBallisfactionBallsSpawnSubsystem::SetTierPickChance(float NewTierPickChance, ETierType TierType)
{
	for (auto Row : TiersRows)
	{
		if (Row->TierType == TierType)
		{
			Row->TierPickChance = NewTierPickChance;
		}
	}
}

TSubclassOf<ABallisfactionBall> UBallisfactionBallsSpawnSubsystem::GetBrickClassToSpawn()
{
	UDataTable* TierDT = GetRandomTier();
	if (!TierDT)
	{
		return nullptr;
	}
	
	FBallTier* Row = GetRandomRowFromTier(TierDT);
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

	float TierOverallChance = 0;
	for (auto Row : TierRows)
	{
		TierOverallChance += Row->ChanceToBeSpawned;
	}

	return TierOverallChance;
}

UDataTable* UBallisfactionBallsSpawnSubsystem::GetRandomTier()
{
	if (TiersRows.IsEmpty())
	{
		return nullptr;
	}
	
	float OverallTierChance = 0;
	for (auto Row : TiersRows)
	{
		OverallTierChance += Row->TierPickChance;
	}

	float Roll = FMath::FRandRange(0.f, OverallTierChance);

	for (auto Row : TiersRows)
	{
	    if (Roll <= Row->TierPickChance)
	    {
	    	return Row->DataTable;
	    }
		
	    Roll -= Row->TierPickChance;
	}

	return nullptr;
}

FBallTier* UBallisfactionBallsSpawnSubsystem::GetRandomRowFromTier(UDataTable* TierDT)
{
	if (!TierDT) return nullptr;

	TArray<FBallTier*> Rows;
	TierDT->GetAllRows(TEXT("Context"), Rows);

	float TotalWeight = 0.f;
	for (auto Row : Rows)
	{
		TotalWeight += Row->ChanceToBeSpawned;
	}

	float Roll = FMath::FRandRange(0.f, TotalWeight);

	for (auto Row : Rows)
	{
		if (Roll < Row->ChanceToBeSpawned)
		{
			return Row;
		}
		Roll -= Row->ChanceToBeSpawned;
	}

	return nullptr;
}