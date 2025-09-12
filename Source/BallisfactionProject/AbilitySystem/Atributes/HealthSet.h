
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfHealth);

UCLASS()
class BALLISFACTIONPROJECT_API UHealthSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHealthSet();
	
	ATTRIBUTE_ACCESSORS(UHealthSet, HealthPoints);
	ATTRIBUTE_ACCESSORS(UHealthSet, MaxHealthPoints);

	UPROPERTY(BlueprintAssignable)
	FOnOutOfHealth OnOutOfHealth;

protected:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthPoints;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealthPoints;
};
