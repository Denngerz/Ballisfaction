
#include "BallisfactionBrick.h"
#include "BallisfactionProject/Components/BallisfactionHealthComponent.h"
#include "BallisfactionProject/AbilitySystem/BallisfactionAbilitySystem.h"

ABallisfactionBrick::ABallisfactionBrick()
{
	PrimaryActorTick.bCanEverTick = false;

	BallisfactionAbilitySystemComponent = CreateDefaultSubobject<UBallisfactionAbilitySystem>(TEXT("AbilitySystemComponent"));

	HealthComponent = CreateDefaultSubobject<UBallisfactionHealthComponent>(TEXT("HealthComponent"));
}

UAbilitySystemComponent* ABallisfactionBrick::GetAbilitySystemComponent() const
{
	return BallisfactionAbilitySystemComponent;
}