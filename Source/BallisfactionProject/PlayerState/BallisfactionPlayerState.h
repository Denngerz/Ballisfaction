
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BallisfactionPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, float, NewValue);

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

	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float CurrentScore;
	
};
