
#include "BallisfactionAbilitySystem.h"

void UBallisfactionAbilitySystem::AbilityInputTagPressed(FGameplayTag InputTag)
{
	TArray<FGameplayAbilitySpec*> Specs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(InputTag), Specs, false);

	for (FGameplayAbilitySpec* Spec : Specs)
	{
		if (Spec->Ability->AbilityTags.HasTagExact(InputTag))
		{
			Spec->InputPressed = true;
			
			if (!Spec->IsActive())
			{
				TryActivateAbility(Spec->Handle);
			}
			
			TArray<UGameplayAbility*> Instances = Spec->GetAbilityInstances();
			const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec->Handle, ActivationInfo.GetActivationPredictionKey());
		}
	}
}

void UBallisfactionAbilitySystem::AbilityInputTagReleased(FGameplayTag InputTag)
{
	TArray<FGameplayAbilitySpec*> Specs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(InputTag), Specs, false);

	for (FGameplayAbilitySpec* Spec : Specs)
	{
		if (Spec->Ability->AbilityTags.HasTagExact(InputTag))
		{
			Spec->InputPressed = false;
			
			TArray<UGameplayAbility*> Instances = Spec->GetAbilityInstances();
			const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec->Handle, ActivationInfo.GetActivationPredictionKey());
		}
	}
}
