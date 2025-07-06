#include "ButtonEditorDetail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "ItemSetting.h"

FButtonEditorDetail::FButtonEditorDetail()
{
}

TSharedRef<IDetailCustomization> FButtonEditorDetail::MakeInstance()
{
	return MakeShared<FButtonEditorDetail>();
}

void FButtonEditorDetail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> TargetObjects;
	DetailBuilder.GetObjectsBeingCustomized(TargetObjects);
	for (auto& Obj : TargetObjects)
	{
		if (Obj.IsValid() == true)
		{
			auto Setting = Cast<UItemSetting>(Obj);
			if (IsValid(Setting) == true)
			{
				_mTarget = Setting;
			}
		}
	}

	IDetailCategoryBuilder& FileDataCategory = DetailBuilder.EditCategory(TEXT("File Data"));
	FileDataCategory.AddCustomRow(FText::FromString(TEXT("FileIORow")))
		.ValueContent()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().FillWidth(1).Padding(3)
				[
					SNew(SButton).OnClicked(this, &FButtonEditorDetail::ClickSaveButton)
						[
							SNew(STextBlock).Text(FText::FromString(TEXT("Save")))
						]
				]
				+ SHorizontalBox::Slot().FillWidth(1).Padding(3)
				[
					SNew(SButton).OnClicked(this, &FButtonEditorDetail::ClickLoadButton)
						[
							SNew(STextBlock).Text(FText::FromString(TEXT("Load")))
						]
				]
		];
}

FReply FButtonEditorDetail::ClickSaveButton()
{
	auto Setting = _mTarget.Get();
	if (Setting != nullptr)
	{
		Setting->SaveData();
	}
	return FReply::Handled();
}

FReply FButtonEditorDetail::ClickLoadButton()
{
	auto Setting = _mTarget.Get();
	if (Setting != nullptr)
	{
		Setting->LoadData();
	}
	return FReply::Handled();
}
