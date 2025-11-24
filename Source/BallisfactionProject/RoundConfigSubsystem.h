
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoundConfigSubsystem.generated.h"

struct FSpawnDataTableEntry;

UCLASS()
class BALLISFACTIONPROJECT_API URoundConfigSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void InitializeSpawnChances(UDataTable* BallTierSpawnChances, UDataTable* BrickTierSpawnChances);
	
	void ConfigureNewSpawnChancesInfo(const int32 RoundNumber);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TiersDT")
	UDataTable* BallTierDefaultSpawnChances;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TiersDT")
	UDataTable* BrickTierDefaultSpawnChances;

private:
	UPROPERTY()
	TArray<FSpawnDataTableEntry> BricksRuntimeTiers;
	
	UPROPERTY()
	TArray<FSpawnDataTableEntry> BallsRuntimeTiers;

	// Internal helpers
	void ConfigureNewBallSpawnChances(int32 RoundNumber);

	void ConfigureNewBrickSpawnChances(int32 RoundNumber);

	void InitializeBallsSpawnChances(UDataTable* BallTierSpawnChances);

	void InitializeBricksSpawnChances(UDataTable* BrickTierSpawnChances);

	void TransferBallsSpawnChances();

	void TransferBricksSpawnChances();
};
