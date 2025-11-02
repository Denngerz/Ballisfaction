
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallisfactionBall.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionBall : public AActor
{
	GENERATED_BODY()

public:
	ABallisfactionBall();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetPotentialDamage();

	virtual float GetPotentialDamage_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DestroySelf();

	virtual void DestroySelf_Implementation();
	
protected:
	void BeginPlay() override;

	void Destroyed() override;
	
	FTimerHandle MyTimerHandle;

	UFUNCTION(BlueprintCallable)
	void UpdateContactTimer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeWithoutContact;

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	float VelocityDamageDivisor;
};
