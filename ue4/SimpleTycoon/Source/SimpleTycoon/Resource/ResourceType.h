#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{	
    Coin = 0	UMETA(DisplayName = "Coin"),
	Max			UMETA( Hidden )	
};