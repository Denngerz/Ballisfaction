
#pragma once

#include "CoreMinimal.h"
#include "BallisfactionAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "MovementSet.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API UMovementSet : public UBallisfactionAttributeSet
{
	GENERATED_BODY()

public:
	UMovementSet();
	
	ATTRIBUTE_ACCESSORS(UMovementSet, Speed);
	ATTRIBUTE_ACCESSORS(UMovementSet, MaxSpeed);
	ATTRIBUTE_ACCESSORS(UMovementSet, RotationSpeed);
	ATTRIBUTE_ACCESSORS(UMovementSet, MaxRotationSpeed);

protected:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData RotationSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxRotationSpeed;
	
};
