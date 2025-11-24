
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "BallisfactionPlayerStats.generated.h"

USTRUCT()
struct FAbilityRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityDefinition;

	UPROPERTY(EditDefaultsOnly)
	bool IsStatusAbility = false;

	UPROPERTY(EditDefaultsOnly)
	FText Description;
};

UCLASS()
class BALLISFACTIONPROJECT_API UBallisfactionPlayerStats : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> UsedAbilities;
};
