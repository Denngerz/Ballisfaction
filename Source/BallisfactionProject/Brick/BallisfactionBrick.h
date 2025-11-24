
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "BallisfactionBrick.generated.h"

class UBallisfactionAbilitySystem;
class UBallisfactionHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrickDestroyed);

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionBrick : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	ABallisfactionBrick();

	UPROPERTY(BlueprintCallable)
	FOnBrickDestroyed OnBrickDestroyed;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|AbilitySystem", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionAbilitySystem> BallisfactionAbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ballisfaction|Health Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBallisfactionHealthComponent> HealthComponent;
};
