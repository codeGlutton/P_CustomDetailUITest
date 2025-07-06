#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class P_TEST_API FButtonEditorDetail : public IDetailCustomization
{
public:
	FButtonEditorDetail();

public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

protected:
	FReply ClickSaveButton();
	FReply ClickLoadButton();

protected:
	TSharedPtr<SButton> _mSaveButton;
	TSharedPtr<SButton> _mLoadButton;
	TWeakObjectPtr<class UItemSetting> _mTarget;
};
