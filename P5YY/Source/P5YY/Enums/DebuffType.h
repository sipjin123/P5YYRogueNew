#pragma once

UENUM(BlueprintType)
enum class EDebuffType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Stun = 1 UMETA(DisplayName = "Stun"),
	Slow = 2 UMETA(DisplayName = "Slow"),
	Poison = 3 UMETA(DisplayName = "Poison"),
	Freeze = 4 UMETA(DisplayName = "Freeze"),
	Burn = 5 UMETA(DisplayName = "Burn"),
	Bleed = 6 UMETA(DisplayName = "Bleed"),
};

struct DebuffType
{
	
};
