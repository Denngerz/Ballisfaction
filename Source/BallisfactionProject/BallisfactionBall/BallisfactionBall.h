
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

	UFUNCTION(BlueprintCallable)
	void DestroySelf();

	UFUNCTION(BlueprintCallable)
	float GetPointsOnGoal();
	
protected:
	virtual void BeginPlay() override;
	
	FTimerHandle MyTimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartDeathTimer();

	UFUNCTION(BlueprintCallable)
	void PauseDeathTimer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeBeforeDeath;

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	float VelocityDamageDivisor;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	float PointsOnGoal;
};
