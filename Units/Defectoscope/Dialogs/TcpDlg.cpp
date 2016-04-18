#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"

PARAM_TITLE(IPPort, L"IP порт")
PARAM_TITLE(IPName, L"Имя компьютера")

DO_NOT_CHECK(IPPort)
DO_NOT_CHECK(IPName)

//template<>struct DlgSubItems<IPAddr, int >: IPAddresControl<IPAddr>{};

//template<>struct __handler_data_widget__<DlgItem<IPAddr>, int>
//{
//	int operator()(HWND h)
//	{
//		int dwAddr;
//		SendMessage((HWND) h,(UINT) IPM_GETADDRESS, 0, (LPARAM)&dwAddr);
//		return dwAddr;
//	}
//};


void TcpDlg::Do(HWND h)
{
   if(TemplDialog<IPAddressTable>(Singleton<IPAddressTable>::Instance()).Do(h, L"Настройки TCP"))
	{
#pragma message("Инициализировать TCP")
	}
}