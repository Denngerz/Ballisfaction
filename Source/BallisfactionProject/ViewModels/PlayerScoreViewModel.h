
#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerScoreViewModel.generated.h"

class ABallisfactionPlayerState;

UCLASS()
class BALLISFACTIONPROJECT_API UPlayerScoreViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, BlueprintReadWrite, Category = "Score")
	float Score;

	UFUNCTION(BlueprintCallable)
	void Initialize(ABallisfactionPlayerState* PlayerState);

protected:
	UFUNCTION()
	void OnScoreChanged(float NewValue);

private:
	UPROPERTY()
	TObjectPtr<ABallisfactionPlayerState> PlayerStateRef;
};
