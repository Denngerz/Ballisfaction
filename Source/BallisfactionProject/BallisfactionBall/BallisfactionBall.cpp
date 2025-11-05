
#include "BallisfactionBall.h"

ABallisfactionBall::ABallisfactionBall(): VelocityDamageDivisor(50.0f), TimeWithoutContact(5), PointsOnGoal(1)
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	StaticMesh->SetSimulatePhysics(true);
}

float ABallisfactionBall::GetPotentialDamage_Implementation()
{
	return (GetVelocity().Length() / (VelocityDamageDivisor));
}

void ABallisfactionBall::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateContactTimer();
}

void ABallisfactionBall::DestroySelf()
{
	Destroy();
}

float ABallisfactionBall::GetPointsOnGoal()
{
	return PointsOnGoal;
}

void ABallisfactionBall::UpdateContactTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		MyTimerHandle,
		this,
		&ABallisfactionBall::DestroySelf,
		0.1f,
		false,
		TimeWithoutContact
	);
}
