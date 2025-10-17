
#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "StaminaViewModel.generated.h"

class UBallisfactionStaminaComponent;

UCLASS()
class BALLISFACTIONPROJECT_API UStaminaViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, BlueprintReadWrite, Category = "Stamina")
	float Stamina;

	UPROPERTY(FieldNotify, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina;

	UFUNCTION(BlueprintCallable)
	void Initialize(UBallisfactionStaminaComponent* InStaminaComponent);

protected:
	UFUNCTION()
	void OnStaminaChanged(float NewValue);

	UFUNCTION()
	void OnMaxStaminaChanged(float NewValue);

private:
	UPROPERTY()
	TObjectPtr<UBallisfactionStaminaComponent> StaminaComponent;
	
};
