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

	// ���� �Ҵ�� ���ÿ� ���� Open
	FArchive* FileWriter = IFileManager::Get().CreateFileWriter(*FilePath, 0);
	if (FileWriter != nullptr)
	{
		int32 Count = Items.Num();
		*FileWriter << Count;
		for (auto& Item : Items)
		{
			*FileWriter << Item;
		}

		// ���� Close
		FileWriter->Close();
		// ���� ����
		delete FileWriter;
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Save!")));
}

void UItemSetting::LoadData()
{
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("ItemList.itl");

	// ���� �Ҵ�� ���ÿ� ���� Open
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

		// ���� Close
		FileReader->Close();
		// ���� ����
		delete FileReader;
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Load!")));
}
