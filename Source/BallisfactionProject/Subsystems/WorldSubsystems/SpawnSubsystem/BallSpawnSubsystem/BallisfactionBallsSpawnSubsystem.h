
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BallisfactionBallsSpawnSubsystem.generated.h"

struct FSpawnDataTableEntry;
class ABallisfactionBall;

USTRUCT(BlueprintType)
struct FBallTier : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABallisfactionBall> BallClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToBeSpawned = 1.0f;
};

UCLASS()
class BALLISFACTIONPROJECT_API UBallisfactionBallsSpawnSubsystem : public UWorldSubsystem
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
	TSubclassOf<ABallisfactionBall> GetBrickClassToSpawn();

private:
	UPROPERTY()
	UDataTable* TiersDataTable;

	TArray<FSpawnDataTableEntry*> TiersRows;

	float CalculateOverallChanceForTierDT(const UDataTable* TierDT);

	UDataTable* GetRandomTier();

	FBallTier* GetRandomRowFromTier(UDataTable* TierDT);
};
