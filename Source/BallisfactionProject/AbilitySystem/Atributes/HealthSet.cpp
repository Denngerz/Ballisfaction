
#include "HealthSet.h"

UHealthSet::UHealthSet()
	: HealthPoints(100.0f)
	, MaxHealthPoints(100.0f)
{
}

void UHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (NewValue <= 0.0f)
	{
		OnOutOfHealth.Broadcast();
	}
}

void UHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthPointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealthPoints());
	}
	else if (Attribute == GetMaxHealthPointsAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
