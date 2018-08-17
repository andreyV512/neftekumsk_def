#include "stdafx.h"
#include "App.h"
#include "Config.h"
#include "DebugMess.h"
#include "MainWindow.h"
#include "WindowsPosition.h"
#include "EmptyWindow.h"
#include "Device1730.h"
#include "AppBase.h"
#include "Automat.h"
#include "USPCData.h"
#include "ConstData.h"
#include "AnalogBoard.h"
#include "AsyncServer.h"
#include "Communication.h"
#include "ComPort.h"
#include "SendDataAsu.h"
#include "Tablo.h"


extern HINSTANCE hInstance;

HANDLE App::ProgrammExitEvent;
HANDLE App::ProgrammContinueEvent;
HANDLE App::ProgrammStopEvent;
HANDLE App::WaitThicknessEvent;
bool App::measurementOfRunning = false;

namespace
{
  AnalogBoard &analogBoard = Singleton<AnalogBoard>::Instance();
  Lir &lir = Singleton<Lir>::Instance();
}

//---------------------------------------------------------------
App::App()	
	: mainWindow(Singleton<MainWindow>::Instance())
{}

void App::Init()
{
	Singleton<Tablo>::Instance();
	AppBase().Init();
	ConstData::Init();
	App::ProgrammExitEvent		= CreateEvent(NULL, TRUE, FALSE, NULL);
	App::ProgrammContinueEvent	= CreateEvent(NULL, TRUE, FALSE, NULL);
	App::ProgrammStopEvent		= CreateEvent(NULL, FALSE, FALSE, NULL);
	App::WaitThicknessEvent     = CreateEvent(NULL, TRUE, FALSE, NULL);
	/////tes
	//SendDataAsu();
	////est	 
	/////
	RECT r;
	WindowPosition::Get<MainWindow>(r);
	HWND h = WindowTemplate(&mainWindow, L"Дефектоскоп \"Буран 9000\"", r.left, r.top, r.right, r.bottom);
	ShowWindow(h, SW_SHOWNORMAL);
	if(!device1730_0.Init(Singleton<Descriptor1730Table>::Instance().items.get<Descriptor1730_0>().value))
	{
		MessageBox(h, L"Не могу инициировать плату 1730-1", L"Ошибка !!!", MB_ICONERROR);
#ifndef DEBUG_ITEMS
		return;
#endif
	}
	if(!device1730_1.Init(Singleton<Descriptor1730Table>::Instance().items.get<Descriptor1730_1>().value))
	{
		MessageBox(h, L"Не могу инициировать плату 1730-2", L"Ошибка !!!", MB_ICONERROR);
#ifndef DEBUG_ITEMS
		return;
#endif
	}
	if(analogBoard.Init() || analogBoard.SetupParams())
	{
#ifndef L502OFF
		MessageBox(0, L"Не могу инициировать плату L502", L"Ошибка !!!", MB_ICONERROR);
#elif !defined(L791OFF)
		MessageBox(0, L"Не могу инициировать плату L791", L"Ошибка !!!", MB_ICONERROR);
#endif
#ifndef DEBUG_ITEMS
		return;
#endif
	}

	///////
	//analogBoard.Start();
	//ULONG *signal;
	//int k = 0;
	//for(int i = 0; i < 256; ++i)
	//{
	// int count = analogBoard.Read(signal);
	// if(count > 0)
	// {
	// //Singleton<RowData>::Instance().SetData(signal, count);
	//// dprint("%d  %d\n", i, count);
	//	
	//	 for(int j = 0; j < count; ++j)
	//	 {
	//		 dprint("%d  %d\n", j % 16, (short)signal[j]);
	//	 }
	//	 Sleep(10000);
	// }	 
	//}

	//////
#pragma message("Добавить настроечный параметр")
	if(!lir.Init(Singleton<DescriptorLir>::Instance().value))
	{
		MessageBox(0, L"Не могу инициировать плату 1784(лир)", L"Ошибка !!!", MB_ICONERROR);
	}
	Communication::Init();
	ComPort &comPort = Singleton<ComPort>::Instance();

	ComPortTable &comPortTable = Singleton<ComPortTable>::Instance();

	comPort.Open(
		comPortTable.items.get<ComPortAddr>().value
		, comPortTable.items.get<BaudRate>().value
		, comPortTable.items.get<Parity>().value
		,comPortTable.items.get<StopBits>().value
		);

	if(!comPort.IsOpen())
	{
		MessageBox(0, L"Не могу инициировать КОМ-ПОРТ", L"Ошибка !!!", MB_ICONERROR);
	}

	AsyncServer::Create(Singleton<IPAddressTable>::Instance().items.get<IPPort>().value);
	automat.Init();	
}

void App::Destroy()
{
	SetEvent(ProgrammExitEvent);
	Sleep(1000);
}

void App::MainWindowTopLabel(wchar_t *txt)
{
	mainWindow.topLabelViewer.SetMessage(txt);
}

void App::MainWindowBottomLabel(int n, wchar_t *text)
{
	SendMessage(mainWindow.hStatusWindow, SB_SETTEXT, n, (LONG)text);
}

void App::MainWindowUpdate()
{
	RepaintWindow(mainWindow.hWnd);
}

bool App::StopAfterCycle()
{
	return app.mainWindow.sycleCheckBox.value;
}

Device1730 device1730_0;
Device1730 device1730_1;

App app;// = Singleton<App>::Instance();

Automat automat;






