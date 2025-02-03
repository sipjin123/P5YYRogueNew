#pragma once

UENUM(BlueprintType)
enum class EBuffType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	SpeedBoost = 1 UMETA(DisplayName = "SpeedBoost"),
	DefenseBoost = 2 UMETA(DisplayName = "DefenseBoost"),
	DodgeBoost = 3 UMETA(DisplayName = "DodgeBoost"),
	AttackBoost = 4 UMETA(DisplayName = "AttackBoost"),
	AttackSpeedBoost = 5 UMETA(DisplayName = "AttackSpeedBoost"),
};

struct BuffType
{
	
};