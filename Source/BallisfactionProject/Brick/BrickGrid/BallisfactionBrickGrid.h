
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallisfactionBrickGrid.generated.h"

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionBrickGrid : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnHolders(int32 Rows, int32 Columns);
	
	virtual void SpawnHolders_Implementation(int32 Rows, int32 Columns);
};
