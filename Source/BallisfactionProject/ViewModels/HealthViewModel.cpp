
#include "HealthViewModel.h"
#include "BallisfactionProject/BallisfactionHealthComponent.h"

void UHealthViewModel::Initialize(UBallisfactionHealthComponent* InHealthComponent)
{
	if (!InHealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("HealthViewModel: InHealthComponent is NULL"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("HealthViewModel: Initialize called with %s"), *InHealthComponent->GetName());
	
	HealthComponent = InHealthComponent;
	
	HealthComponent->OnCurrentHealthChanged.AddDynamic(this, &UHealthViewModel::OnHealthChanged);
	HealthComponent->OnMaxHealthChanged.AddDynamic(this, &UHealthViewModel::OnMaxHealthChanged);
	
	OnHealthChanged(HealthComponent->GetHealth());
	OnMaxHealthChanged(HealthComponent->GetMaxHealth());
}

void UHealthViewModel::OnHealthChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth: Health=%f"), Health);
}

void UHealthViewModel::OnMaxHealthChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("MaxHealth: MaxHealth=%f"), MaxHealth);
}
