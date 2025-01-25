﻿#include "ItemBase.h"

/* Broken during upgrade from V17 to V22
UItemBase::UItemBase() : IsCopy(false), IsPickup(false)
{
}
*/


UItemBase::UItemBase()
{
}

void UItemBase::ResetFlags()
{
	IsCopy = false;
	IsPickup = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());
	ItemCopy->Id = this->Id;
	ItemCopy->Id = this->Id;
	
	ItemCopy->ItemRarity = this->ItemRarity;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemStats = this->ItemStats;
	ItemCopy->ItemAssetData = this->ItemAssetData;
	ItemCopy->ItemStorageInfo = this->ItemStorageInfo;

	return ItemCopy;
}

void UItemBase::SetQuanity(int32 NewQuantity)
{
	Quantity = FMath::Clamp(NewQuantity, 0 , ItemStorageInfo.IsStackable ? ItemStorageInfo.MaxStackSize : 1);
	if (Quantity <= 0)
	{
		// Remove from inventory
	}
}
