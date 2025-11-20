
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallisfactionBrickHolder.generated.h"

class ABallisfactionBrick;

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionBrickHolder : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateBrickClass();

protected:
	UFUNCTION(BlueprintCallable)
	void SpawnBrick();

	UFUNCTION()
	void HandleBrickDestroyed();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABallisfactionBrick> BrickClass;

	UPROPERTY(VisibleInstanceOnly, Category="Brick")
	TObjectPtr<ABallisfactionBrick> Brick;
};
