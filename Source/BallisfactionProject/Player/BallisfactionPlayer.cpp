
#include "BallisfactionPlayer.h"
#include "BallisfactionPlayerStats.h"
#include "BallisfactionProject/BallisfactionHealthComponent.h"
#include "BallisfactionProject/AbilitySystem/BallisfactionAbilitySystem.h"
#include "BallisfactionProject/AbilitySystem/Atributes/HealthSet.h"

ABallisfactionPlayer::ABallisfactionPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	BallisfactionAbilitySystemComponent = CreateDefaultSubobject<UBallisfactionAbilitySystem>(TEXT("AbilitySystemComponent"));

	HealthComponent = CreateDefaultSubobject<UBallisfactionHealthComponent>(TEXT("HealthComponent"));
}

bool ABallisfactionPlayer::InitializeUnitAbilities()
{
	if(!ensureMsgf(PlayerStats, TEXT("UnitStats DA is invalid!")))
	{
		return false;
	}
	if(!ensureMsgf(PlayerStats->UsedAbilities, TEXT("Used Abilities DT is invalid!")))
	{
		return false;
	}
	
	TArray<FAbilityRow*> AbilitiesInfos;
	PlayerStats->UsedAbilities->GetAllRows(TEXT("Player Abilities"), AbilitiesInfos);

	for (auto AbilityInfo : AbilitiesInfos)
	{
		if (!AbilityInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability row was null in %s"), *GetNameSafe(PlayerStats->UsedAbilities));
			return false;
		}

		if (!AbilityInfo->AbilityDefinition)
		{
			UE_LOG(LogTemp, Warning, TEXT("AbilityDefinition is null in AbilityRow of %s"), *GetNameSafe(PlayerStats->UsedAbilities));
			return false;
		}
		
		FGameplayAbilitySpec AbilitySpec(AbilityInfo->AbilityDefinition, 1);

		if (AbilityInfo->IsStatusAbility)
		{
			BallisfactionAbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}
		else
		{
			BallisfactionAbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}

	return true;
}

void ABallisfactionPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitializeUnitAbilities();
}
