#pragma once

#include "../P_Test.h"
#include "Engine/DeveloperSettings.h"
#include "ItemSetting.generated.h"

USTRUCT()
struct FBaseItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category="Item")
	FName Name;

	UPROPERTY(EditAnywhere, Config, Category = "Item")
	int32 Id;

	UPROPERTY(EditAnywhere, Config, Category = "Item")
	
	TSoftObjectPtr<UMaterialInstance> Material;

	friend FArchive& operator<<(FArchive& Ar, FBaseItemInfo& Target)
	{
		Ar << Target.Name << Target.Id;

		return Ar;
	}
};

/**
 * 
 */
UCLASS(config = CustomItem, DefaultConfig, meta = (DisplayName = "CustomItem"))
class P_TEST_API UItemSetting : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UItemSetting();

public:
	UFUNCTION(CallInEditor, Category = "Item")
	void SaveData();

	UFUNCTION(CallInEditor, Category = "Item")
	void LoadData();

public:
	UPROPERTY(EditAnywhere, Config, Category = "Item")
	TArray<FBaseItemInfo> Items;

	UPROPERTY(EditAnywhere, Config, Category = "Item")
	int32 PrefixId;
};
