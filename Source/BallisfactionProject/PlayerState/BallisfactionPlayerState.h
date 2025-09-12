
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "BallisfactionPlayerState.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void AddPointsToScore(float ScoredAmount);

	UFUNCTION(BlueprintCallable)
	float GetCurrentScore() const;

private:
	UPROPERTY(VisibleAnywhere, Blueprintable)
	float CurrentScore;
	
};
