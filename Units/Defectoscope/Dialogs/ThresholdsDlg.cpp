#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"

PARAM_TITLE(BKlass2<Long>, L"порог 2 класс")
PARAM_TITLE(BDefect<Long>, L"порог брака")

DO_NOT_CHECK(BKlass2<Long>)
DO_NOT_CHECK(BDefect<Long>)
void LongThresholdsDlg  ::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<BKlass2<Long>, BDefect<Long>>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"Продольные пороги"))
	{
	}
}

PARAM_TITLE(BKlass2<Cross>, L"порог 2 класс")
PARAM_TITLE(BDefect<Cross>, L"порог брака")

DO_NOT_CHECK(BKlass2<Cross>)
DO_NOT_CHECK(BDefect<Cross>)
void CrossThresholdsDlg  ::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<BKlass2<Cross>, BDefect<Cross>>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"Поперечные пороги"))
	{
	}
}

PARAM_TITLE(MimimumTubeLength, L"Минимальная длина трубы(в зонах)")

MIN_EQUAL_VALUE(MimimumTubeLength, 20)
MAX_EQUAL_VALUE(MimimumTubeLength, 60)

void MinimumTubeLengthDlg::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<MimimumTubeLength>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"Минимальная длина трубы"))
	{
	}
}