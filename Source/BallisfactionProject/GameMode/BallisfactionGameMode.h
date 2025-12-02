
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BallisfactionGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStart);

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABallisfactionGameMode();
		
	UPROPERTY(BlueprintAssignable)
	FOnRoundEnd OnRoundEnd;

	UPROPERTY(BlueprintAssignable)
	FOnRoundStart OnRoundStart;
	
	UFUNCTION(BlueprintCallable)
	int32 GetMaxBallsOnMap();

	UFUNCTION(BlueprintCallable)
	int32 GetRoundNumber();

	UFUNCTION(BlueprintCallable)
	int32 GetBrickRowsAmount();

	UFUNCTION(BlueprintCallable)
	void AddNewBall();

	UFUNCTION(BlueprintCallable)
	void RemoveExistingBall();

	UFUNCTION(BlueprintCallable)
	bool CanSpawnNewBall();

protected:
	virtual void BeginPlay() override;

	FTimerHandle RoundTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BrickTiersSpawnTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BallsTiersSpawnTable;
	
	UFUNCTION(BlueprintCallable)
	void StartNextRound();

	UFUNCTION()
	void StopRound();

	UFUNCTION()
	void CalculateBrickRowsAmount();

	UFUNCTION()
	void CalculateRoundTime();

	UFUNCTION()
	void StartRoundTimer();

private:
	UPROPERTY(EditDefaultsOnly, Category="Round Info")
	int32 MaxBallsOnMap;

	UPROPERTY(EditDefaultsOnly, Category="Round Info")
	int32 RoundNumber;

	UPROPERTY(EditDefaultsOnly, Category="Round Info")
	int32 BrickRowsAmount;

	UPROPERTY(EditDefaultsOnly, Category="Round Info")
	float RoundTime;
};
