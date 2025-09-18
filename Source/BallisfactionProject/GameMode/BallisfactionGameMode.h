
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BallisfactionGameMode.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ABallisfactionGameMode();

public:
	UFUNCTION(BlueprintCallable)
	int32 GetMaxBallsOnMap();

	UFUNCTION(BlueprintCallable)
	void AddNewBall();

	UFUNCTION(BlueprintCallable)
	void RemoveExistingBall();

	UFUNCTION(BlueprintCallable)
	bool CanSpawnNewBall();

private:
	UPROPERTY(EditDefaultsOnly, Category="Balls Ammount")
	int32 MaxBallsOnMap;
};
