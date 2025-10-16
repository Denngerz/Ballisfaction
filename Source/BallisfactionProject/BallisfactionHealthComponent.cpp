
#include "BallisfactionHealthComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Atributes/HealthSet.h"

UBallisfactionHealthComponent::UBallisfactionHealthComponent()
	: AbilitySystemComponent (nullptr)
	, HealthSet (nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UBallisfactionHealthComponent::GetHealth() const
{
	return HealthSet->GetHealthPoints();
}

float UBallisfactionHealthComponent::GetMaxHealth() const
{
	return HealthSet->GetMaxHealthPoints();
}

void UBallisfactionHealthComponent::BeginPlay()
{
	InitASCHealth();
}

void UBallisfactionHealthComponent::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnOutOfHealth.Broadcast(Data.NewValue);
}

void UBallisfactionHealthComponent::InitASCHealth()
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(GetOwner()))
	{
		AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
	}
	
	if (!ensureMsgf(AbilitySystemComponent, TEXT("BallisfactionHealthComponent [%s]: AbilitySystemComponent is null!"), *GetNameSafe(this)))
	{
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<UHealthSet>();
	if (!ensureMsgf(HealthSet, TEXT("BallisfactionHealthComponent [%s]: Failed to retrieve HealthSet!"), *GetNameSafe(this)))
	{
		return;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthPointsAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}


