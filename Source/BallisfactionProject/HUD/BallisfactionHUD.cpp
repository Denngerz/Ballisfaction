
#include "BallisfactionHUD.h"
#include "CommonUserWidget.h"
#include "Blueprint/UserWidget.h"

void ABallisfactionHUD::InitializeHUD()
{
	if (IsValid(LayoutClass))
	{
		Layout = CreateWidget<UCommonUserWidget>(GetWorld(), LayoutClass);

		if (Layout)
		{
			Layout->AddToViewport();
			OnInitializationComplited.Broadcast();
		}
	}
}

void ABallisfactionHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeHUD();
}
