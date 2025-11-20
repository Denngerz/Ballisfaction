
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoundConfigSubsystem.generated.h"

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
	// Ball pick chances
	float LegendaryBallPickChance;
	
	float RareBallPickChance;
	
	float CommonBallPickChance;

	// Brick pick chance
	float LegendaryBrickPickChance;
	
	float RareBrickPickChance;
	
	float CommonBrickPickChance;

	// Internal helpers
	void ConfigureNewBallSpawnChances(int32 RoundNumber);

	void ConfigureNewBrickSpawnChances(int32 RoundNumber);

	void InitializeBallsSpawnChances(UDataTable* BallTierSpawnChances);

	void InitializeBricksSpawnChances(UDataTable* BrickTierSpawnChances);

	void TransferBallsSpawnChances();

	void TransferBricksSpawnChances();
};
