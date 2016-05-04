#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"

MIN_EQUAL_VALUE(Offset<Cross>, 0)
MAX_EQUAL_VALUE(Offset<Cross>, 200)
PARAM_TITLE(Offset<Cross>, L"Поперечного контроля(мм)")

MIN_EQUAL_VALUE(Offset<Long>, 0)
MAX_EQUAL_VALUE(Offset<Long>, 200)
PARAM_TITLE(Offset<Long>, L"Продольного контроля(мм)")

void OffsetsTubeDlg::Do(HWND h)
{
	if(TemplDialog<OffsetsTable>(Singleton<OffsetsTable>::Instance()).Do(h, L"Смещение измерений"))
	{
	}
}