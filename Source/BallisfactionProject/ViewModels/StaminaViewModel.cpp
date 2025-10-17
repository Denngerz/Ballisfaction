
#include "StaminaViewModel.h"
#include "BallisfactionProject/BallisfactionStaminaComponent.h"

void UStaminaViewModel::Initialize(UBallisfactionStaminaComponent* InStaminaComponent)
{
	if (!InStaminaComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("StaminaViewModel: InStaminaComponent is NULL"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("StaminaViewModel: Initialize called with %s"), *InStaminaComponent->GetName());
	
	StaminaComponent = InStaminaComponent;

	StaminaComponent->OnCurrentStaminaChanged.AddDynamic(this, &UStaminaViewModel::OnStaminaChanged);
	StaminaComponent->OnMaxStaminaChanged.AddDynamic(this, &UStaminaViewModel::OnMaxStaminaChanged);

	OnStaminaChanged(StaminaComponent->GetStamina());
	OnMaxStaminaChanged(StaminaComponent->GetMaxStamina());
}

void UStaminaViewModel::OnStaminaChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Stamina, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("CurrentStamina: Stamina=%f"), Stamina);
}

void UStaminaViewModel::OnMaxStaminaChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("MaxStamina: MaxStamina=%f"), MaxStamina);
}
