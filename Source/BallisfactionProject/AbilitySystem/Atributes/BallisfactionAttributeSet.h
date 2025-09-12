
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BallisfactionAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BALLISFACTIONPROJECT_API UBallisfactionAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
};
