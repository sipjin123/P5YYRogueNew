#pragma once

UENUM(BlueprintType)
enum class EStatEvent : uint8
{
	NONE = 0 UMETA(DisplayName = "Event: None"),
	EVENT_ON_ASSIGNED  = 1 UMETA(DisplayName = "Event: Assigned"),
	EVENT_ON_UPDATED = 2 UMETA(DisplayName = "Event: Updated"),
	EVENT_DEPLETED = 3 UMETA(DisplayName = "Event: Depleted"),

	// Used to retrieve the number of elements in the enum
	LAST_EVENT          UMETA(Hidden)
};