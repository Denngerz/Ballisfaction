
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BallisfactionAbilitySystem.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BALLISFACTIONPROJECT_API UBallisfactionAbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AbilityInputTagPressed(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable)
	void AbilityInputTagReleased(FGameplayTag InputTag);
};
