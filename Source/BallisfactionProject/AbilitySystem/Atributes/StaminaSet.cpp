
#include "StaminaSet.h"

UStaminaSet::UStaminaSet()
	: StaminaPoints(100.0f)
	, MaxStaminaPoints(100.0f)
{
}

void UStaminaSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UStaminaSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}


void UStaminaSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetStaminaPointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStaminaPoints());
	}
	else if (Attribute == GetMaxStaminaPointsAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
