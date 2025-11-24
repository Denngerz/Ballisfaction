
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffect.h"
#include "BallisfactionStaminaComponent.generated.h"

class UAbilitySystemComponent;
class UStaminaSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChanged, float, NewCurrentValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewCurrentValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLISFACTIONPROJECT_API UBallisfactionStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBallisfactionStaminaComponent();

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnOutOfStamina OnOutOfStamina;

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnCurrentStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnMaxStaminaChanged OnMaxStaminaChanged;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stamina")
	float GetStamina() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stamina")
	float GetMaxStamina() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<const UStaminaSet> StaminaSet;
	
	void OnNewStamina(const FOnAttributeChangeData& Data) const;

	void OnNewMaxStamina(const FOnAttributeChangeData& Data) const;
	
	void InitASCStamina();
	
};
