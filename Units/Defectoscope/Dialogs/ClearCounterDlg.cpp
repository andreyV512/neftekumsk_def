#include "stdafx.h"
#include "Dialogs.h"
#include "CountingTube.h"

void ClearCounterDlg::Do(HWND)
{
	CountingTube().Clear();
}