
#pragma once

#include "CoreMinimal.h"
#include "BallisfactionProject/Structures/SpawnDataTableEntry.h"
#include "Subsystems/WorldSubsystem.h"
#include "BallisfactionBrickSpawnSubsystem.generated.h"

struct FSpawnDataTableEntry;
class ABallisfactionBrick;

USTRUCT(BlueprintType)
struct FBrickTier : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABallisfactionBrick> BrickClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToBeSpawned = 1.0f;
};

UCLASS()
class BALLISFACTIONPROJECT_API UBallisfactionBrickSpawnSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateTiersDataTableInfo(UDataTable* NewTiersDataTable);

	UFUNCTION(BlueprintCallable)
	UDataTable* GetTiersDataTable();

	UFUNCTION(BlueprintCallable)
	void SetTierPickChance(float NewTierPickChance, ETierType TierType);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<ABallisfactionBrick> GetBrickClassToSpawn();

private:
	UPROPERTY()
	UDataTable* TiersDataTable;

	TArray<FSpawnDataTableEntry*> TiersRows;

	float CalculateOverallChanceForTierDT(const UDataTable* TierDT);

	UDataTable* GetRandomTier();

	FBrickTier* GetRandomRowFromTier(UDataTable* TierDT);

	UDataTable* DuplicateDataTable(UDataTable* SourceDT);
};