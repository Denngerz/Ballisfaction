
#include "BallisfactionBrickSpawnSubsystem.h"
#include "BallisfactionProject/Structures/SpawnDataTableEntry.h"

void UBallisfactionBrickSpawnSubsystem::UpdateTiersDataTableInfo(UDataTable* NewTiersDataTable)
{
	TiersDataTable = NewTiersDataTable;
	
	TiersDataTable->GetAllRows(TEXT("Context"), TiersRows);

	for (auto Row : TiersRows)
	{
		Row->TotalWeight = CalculateOverallChanceForTierDT(Row->DataTable);
	}
}

UDataTable* UBallisfactionBrickSpawnSubsystem::GetTiersDataTable()
{
	return TiersDataTable;
}

void UBallisfactionBrickSpawnSubsystem::SetTierPickChance(float NewTierPickChance, ETierType TierType)
{
	for (auto Row : TiersRows)
	{
		if (Row->TierType == TierType)
		{
			Row->TierPickChance = NewTierPickChance;
		}
	}
}

TSubclassOf<ABallisfactionBrick> UBallisfactionBrickSpawnSubsystem::GetBrickClassToSpawn()
{
	UDataTable* TierDT = GetRandomTier();
	if (!TierDT)
	{
		return nullptr;
	}
	
	FBrickTier* Row = GetRandomRowFromTier(TierDT);
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

FBrickTier* UBallisfactionBrickSpawnSubsystem::GetRandomRowFromTier(UDataTable* TierDT)
{
	if (!TierDT) return nullptr;

	TArray<FBrickTier*> Rows;
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

UDataTable* UBallisfactionBrickSpawnSubsystem::DuplicateDataTable(UDataTable* SourceDT)
{
	if (!SourceDT)
		return nullptr;

	// Create a new DataTable object
	UDataTable* NewDT = NewObject<UDataTable>(this, UDataTable::StaticClass());

	// Copy the row struct type
	NewDT->RowStruct = SourceDT->RowStruct;

	// Copy each row manually
	for (const TPair<FName, uint8*>& Pair : SourceDT->GetRowMap())
	{
		uint8* NewRowData = (uint8*)FMemory::Malloc(NewDT->RowStruct->GetStructureSize());
		NewDT->AddRow(Pair.Key, NewRowData);
		NewDT->RowStruct->CopyScriptStruct(NewRowData, Pair.Value);
	}

	return NewDT;
}
