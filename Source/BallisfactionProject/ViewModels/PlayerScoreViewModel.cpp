
#include "PlayerScoreViewModel.h"
#include "BallisfactionProject/PlayerState/BallisfactionPlayerState.h"

void UPlayerScoreViewModel::Initialize(ABallisfactionPlayerState* PlayerState)
{
	if (!PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerScoreViewModel: PlayerState is NULL"));
		return;
	}

	PlayerStateRef = PlayerState;

	PlayerStateRef->OnScoreChanged.AddDynamic(this, &UPlayerScoreViewModel::OnScoreChanged);

	OnScoreChanged(PlayerStateRef->GetCurrentScore());
}

void UPlayerScoreViewModel::OnScoreChanged(float NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Score, NewValue);
}
