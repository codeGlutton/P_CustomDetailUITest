#include "ItemSetting.h"
#include "Misc/MessageDialog.h"
#include "ButtonEditorDetail.h"

UItemSetting::UItemSetting()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("ItemSetting", FOnGetDetailCustomizationInstance::CreateStatic(&FButtonEditorDetail::MakeInstance));
}

void UItemSetting::SaveData()
{
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("ItemList.itl");

	// 동적 할당과 동시에 파일 Open
	FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*FilePath, 0);
	if (FileWriter != nullptr)
	{
		int32 Count = Items.Num();
		*FileWriter << Count;
		for (auto& Item : Items)
		{
			*FileWriter << Item;
		}

		// 파일 Close
		FileWriter->Close();
		// 동적 해제
		delete FileWriter;
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Save!")));
}

void UItemSetting::LoadData()
{
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("ItemList.itl");

	// 동적 할당과 동시에 파일 Open
	FArchive* FileReader = IFileManager::Get().CreateFileReader(*FilePath, 0);
	if (FileReader != nullptr)
	{
		Items.Empty();
		int32 Count = 0;
		
		*FileReader << Count;
		Items.Init(FBaseItemInfo(), Count);
		
		for (auto& Item : Items)
		{
			*FileReader << Item;
		}

		// 파일 Close
		FileReader->Close();
		// 동적 해제
		delete FileReader;
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Load!")));
}
