// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffect.h"
#include "BallisfactionHealthComponent.generated.h"

class UAbilitySystemComponent;
class UHealthSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOutOfHealthSignature, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLISFACTIONPROJECT_API UBallisfactionHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBallisfactionHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnOutOfHealthSignature OnOutOfHealth;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<const UHealthSet> HealthSet;
	
	void OnHealthChanged(const FOnAttributeChangeData& Data) const;
	
	void InitASCHealth();
};
