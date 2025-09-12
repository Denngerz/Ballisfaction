
#pragma once

#include "CoreMinimal.h"
#include "BallisfactionAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "StaminaSet.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API UStaminaSet : public UBallisfactionAttributeSet
{
	GENERATED_BODY()

public:
	UStaminaSet();
	
	ATTRIBUTE_ACCESSORS(UStaminaSet, StaminaPoints);
	ATTRIBUTE_ACCESSORS(UStaminaSet, MaxStaminaPoints);

protected:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaPoints;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStaminaPoints;
};
