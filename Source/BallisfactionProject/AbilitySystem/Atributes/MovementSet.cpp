
#include "MovementSet.h"

UMovementSet::UMovementSet()
	: Speed(1.0f)
	, MaxSpeed(1.0f)
    , RotationSpeed(1.0f)
	, MaxRotationSpeed(1.0f)
{
}

void UMovementSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UMovementSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UMovementSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSpeed());
	}
	else if (Attribute == GetMaxSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	else if (Attribute == GetRotationSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxRotationSpeed());
	}
	else if (Attribute == GetMaxRotationSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}
