
#include "BallisfactionPlayerState.h"

void ABallisfactionPlayerState::BeginPlay()
{
	Super::BeginPlay();

	CurrentScore = 0;
}

void ABallisfactionPlayerState::AddPointsToScore(float ScoredAmount)
{
	CurrentScore += ScoredAmount;
}

float ABallisfactionPlayerState::GetCurrentScore() const
{
	return CurrentScore;
}
