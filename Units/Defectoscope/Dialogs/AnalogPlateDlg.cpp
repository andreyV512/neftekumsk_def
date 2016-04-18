#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"

MIN_EQUAL_VALUE(PerChannelFrequency, 100)
MAX_EQUAL_VALUE(PerChannelFrequency, 50000)
PARAM_TITLE(PerChannelFrequency, L"Частота сбора данных на канал")

void AnalogBoardDlg::Do(HWND h)
{
	if(TemplDialog<AnalogBoardTable>(Singleton<AnalogBoardTable>::Instance()).Do(h, L"Аналоговая плата"))
	{
	}
}
