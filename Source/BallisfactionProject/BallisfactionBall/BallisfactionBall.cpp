
#include "BallisfactionBall.h"

ABallisfactionBall::ABallisfactionBall(): VelocityDamageDivisor(50.0f), TimeWithoutContact(5)
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	StaticMesh->SetSimulatePhysics(true);
}

float ABallisfactionBall::GetPotentialDamage_Implementation()
{
	return (GetVelocity().Length() / (VelocityDamageDivisor));
}

void ABallisfactionBall::DestroySelf_Implementation()
{
	Destroy();
}

void ABallisfactionBall::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateContactTimer();
}

void ABallisfactionBall::Destroyed()
{
	Super::Destroyed();

	DestroySelf();
}

void ABallisfactionBall::UpdateContactTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		MyTimerHandle,
		this,
		&ABallisfactionBall::DestroySelf,
		1.0f,
		true,
		TimeWithoutContact
	);
}
