
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "BallisfactionGameState.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddNewBall();

	UFUNCTION(BlueprintCallable)
	void RemoveExistingBall();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentBallsAmount();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Balls Ammount")
	int32 CurrentBallsAmount;
};
