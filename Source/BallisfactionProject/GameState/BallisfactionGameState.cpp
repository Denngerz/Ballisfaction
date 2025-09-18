
#include "BallisfactionGameState.h"

void ABallisfactionGameState::AddNewBall()
{
	CurrentBallsAmount++;
}

void ABallisfactionGameState::RemoveExistingBall()
{
	CurrentBallsAmount--;
}

int32 ABallisfactionGameState::GetCurrentBallsAmount()
{
	return CurrentBallsAmount;
}
