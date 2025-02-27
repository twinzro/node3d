//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once /* DlgShortcuts.h */
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "UIDialog.h"
#include "TSingleton.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CDlgShortcuts : public CUIDialog, public TSingleton<CDlgShortcuts>
{
public:
	void OnControlRegister();
protected:
	void OnBtnCharInfo();
	void OnBtnMove();
	void OnBtnBag();
	void OnBtnSetup();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------