
#include "BallisfactionGameMode.h"

#include "BallisfactionProject/GameState/BallisfactionGameState.h"

ABallisfactionGameMode::ABallisfactionGameMode()
	:MaxBallsOnMap(5)
{
}

int32 ABallisfactionGameMode::GetMaxBallsOnMap()
{
	return MaxBallsOnMap;
}

void ABallisfactionGameMode::AddNewBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS)
	{
		BallisfactionGS->AddNewBall();
	}
}

void ABallisfactionGameMode::RemoveExistingBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS)
	{
		BallisfactionGS->RemoveExistingBall();
	}
}

bool ABallisfactionGameMode::CanSpawnNewBall()
{
	ABallisfactionGameState* BallisfactionGS = Cast<ABallisfactionGameState>(GameState);

	if (BallisfactionGS)
	{
		return BallisfactionGS->GetCurrentBallsAmount() < MaxBallsOnMap;
	}

	return false;
}
