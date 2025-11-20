
#include "BallisfactionStaminaComponent.h"
#include "AbilitySystemInterface.h"
#include "../AbilitySystem/Atributes/StaminaSet.h"

UBallisfactionStaminaComponent::UBallisfactionStaminaComponent()
	: AbilitySystemComponent (nullptr)
	, StaminaSet (nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UBallisfactionStaminaComponent::GetStamina() const
{
	return StaminaSet->GetStaminaPoints();
}

float UBallisfactionStaminaComponent::GetMaxStamina() const
{
	return StaminaSet->GetMaxStaminaPoints();
}

void UBallisfactionStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	InitASCStamina();
}

void UBallisfactionStaminaComponent::OnNewStamina(const FOnAttributeChangeData& Data) const
{
	if (Data.NewValue <= 0.f)
	{
		OnOutOfStamina.Broadcast();
	}
	OnCurrentStaminaChanged.Broadcast(Data.NewValue);
}

void UBallisfactionStaminaComponent::OnNewMaxStamina(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

void UBallisfactionStaminaComponent::InitASCStamina()
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(GetOwner()))
	{
		AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
	}
	
	if (!ensureMsgf(AbilitySystemComponent, TEXT("BallisfactionHealthComponent [%s]: AbilitySystemComponent is null!"), *GetNameSafe(this)))
	{
		return;
	}

	StaminaSet = AbilitySystemComponent->GetSet<UStaminaSet>();
	if (!ensureMsgf(StaminaSet, TEXT("BallisfactionHealthComponent [%s]: Failed to retrieve HealthSet!"), *GetNameSafe(this)))
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(StaminaSet->GetStaminaPointsAttribute()).AddUObject(this, &ThisClass::OnNewStamina);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(StaminaSet->GetMaxStaminaPointsAttribute()).AddUObject(this, &ThisClass::OnNewMaxStamina);
}


