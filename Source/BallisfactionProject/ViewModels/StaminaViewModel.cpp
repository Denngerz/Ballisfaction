
#include "StaminaViewModel.h"
#include "BallisfactionProject/BallisfactionStaminaComponent.h"

void UStaminaViewModel::Initialize(UBallisfactionStaminaComponent* InStaminaComponent)
{
	if (!InStaminaComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("StaminaViewModel: InStaminaComponent is NULL"));
		return;
	}
	
	StaminaComponent = InStaminaComponent;

	StaminaComponent->OnCurrentStaminaChanged.AddDynamic(this, &UStaminaViewModel::OnStaminaChanged);
	StaminaComponent->OnMaxStaminaChanged.AddDynamic(this, &UStaminaViewModel::OnMaxStaminaChanged);

	OnStaminaChanged(StaminaComponent->GetStamina());
	OnMaxStaminaChanged(StaminaComponent->GetMaxStamina());
}

void UStaminaViewModel::OnStaminaChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Stamina, NewValue);
}

void UStaminaViewModel::OnMaxStaminaChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewValue);
}
