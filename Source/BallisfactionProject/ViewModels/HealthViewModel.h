#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "HealthViewModel.generated.h"

class UBallisfactionHealthComponent;

UCLASS(BlueprintType)
class BALLISFACTIONPROJECT_API UHealthViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, BlueprintReadWrite, Category="Health")
	float Health;

	UPROPERTY(FieldNotify, BlueprintReadWrite, Category="Health")
	float MaxHealth;
	
	UFUNCTION(BlueprintCallable)
	void Initialize(UBallisfactionHealthComponent* InHealthComponent);

protected:
	UFUNCTION()
	void OnHealthChanged(float NewValue);

	UFUNCTION()
	void OnMaxHealthChanged(float NewValue);

private:
	UPROPERTY()
	TObjectPtr<UBallisfactionHealthComponent> HealthComponent;
};