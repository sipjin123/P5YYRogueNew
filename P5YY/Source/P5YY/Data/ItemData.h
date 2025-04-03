#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

UENUM()
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Legendary UMETA(DisplayName = "Legendary"),
};

UENUM()
enum class EItemType : uint8
{
	None UMETA(DisplayName = "None"),
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Trinket UMETA(DisplayName = "Trinket"),
	Ring UMETA(DisplayName = "Ring"),
	Consumable UMETA(DisplayName = "Consumable"),
	Material UMETA(DisplayName = "Material"),
	Misc UMETA(DisplayName = "Misc"),
	Quest UMETA(DisplayName = "Quest"),
};

USTRUCT()
struct FItemStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 StatValue = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	int32 Durability = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	float SellPrice = 0;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Asset")
	UTexture2D* Icon = nullptr;
	UPROPERTY(EditAnywhere, Category="Asset")
	UStaticMesh* Mesh = nullptr;
};

USTRUCT()
struct FItemStorageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Storage")
	int32 SlotsOccupied = 0;
	UPROPERTY(EditAnywhere, Category="Storage")
	float Weight = 0;
	UPROPERTY(EditAnywhere, Category="Storage")
	bool IsStackable = false;
	UPROPERTY(EditAnywhere, Category="Storage")
	int32 MaxStackSize = 0;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Text")
	FText Name;
	UPROPERTY(EditAnywhere, Category="Text")
	FText Description;
	UPROPERTY(EditAnywhere, Category="Text")
	FText InteractionText;
	UPROPERTY(EditAnywhere, Category="Text")
	FText UsageText;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	//Generated_UStruct_Body()

	UPROPERTY(VisibleAnywhere, Category="Item Data")
	int32 Id = 0;
	UPROPERTY(EditAnywhere, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemRarity ItemRarity = EItemRarity::Common;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemTextData ItemTextData;
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemType ItemType = EItemType::None;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemStats ItemStats;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemAssetData ItemAssetData;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemStorageInfo ItemStorageInfo;
};
