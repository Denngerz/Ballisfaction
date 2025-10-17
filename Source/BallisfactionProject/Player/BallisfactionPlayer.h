
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "BallisfactionPlayer.generated.h"

class UBallisfactionAbilitySystem;
class UBallisfactionPlayerStats;
class UBallisfactionHealthComponent;
class UBallisfactionStaminaComponent;

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionPlayer : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABallisfactionPlayer();

	bool InitializeUnitAbilities();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|AbilitySystem", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionAbilitySystem> BallisfactionAbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Player Stats", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionPlayerStats> PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Health Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Health Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionStaminaComponent> StaminaComponent;
};
