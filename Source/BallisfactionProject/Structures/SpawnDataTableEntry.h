
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpawnDataTableEntry.generated.h"

UENUM(BlueprintType)
enum class ETierType : uint8
{
	Legendary UMETA(DisplayName = "Legendary"),
	Rare      UMETA(DisplayName = "Rare"),
	Common    UMETA(DisplayName = "Common"),
};

USTRUCT(BlueprintType)
struct FSpawnDataTableEntry : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETierType TierType = ETierType::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TierPickChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RoundModificator = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float TotalWeight = 0.0f;
};
