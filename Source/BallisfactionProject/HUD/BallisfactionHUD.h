
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BallisfactionHUD.generated.h"

class UCommonUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializationComplited);

UCLASS()
class BALLISFACTIONPROJECT_API ABallisfactionHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD();

	UPROPERTY(BlueprintAssignable, Category="UI")
	FOnInitializationComplited OnInitializationComplited;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UCommonUserWidget* Layout;

private:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UCommonUserWidget> LayoutClass;
};
