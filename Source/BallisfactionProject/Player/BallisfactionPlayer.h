
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallisfactionPlayer.generated.h"

class UBallisfactionAbilitySystem;
class UBallisfactionPlayerStats;
class UBallisfactionHealthComponent;

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionPlayer : public APawn
{
	GENERATED_BODY()

public:
	ABallisfactionPlayer();

	bool InitializeUnitAbilities();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|AbilitySystem", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionAbilitySystem> BallisfactionAbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Player Stats", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionPlayerStats> PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Health Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionHealthComponent> HealthComponent;
};
