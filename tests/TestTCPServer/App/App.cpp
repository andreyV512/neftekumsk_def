#include "stdafx.h"
#include "App.h"
#include "Config.h"
#include "DebugMess.h"
//#include "MainWindow.h"
//#include "WindowsPosition.h"
//#include "EmptyWindow.h"
//#include "Device1730.h"
#include "AppBase.h"
#include "Automat.h"
#include "USPCData.h"
#include "ConstData.h"
#include "AnalogBoard.h"
#include "AsyncServer.h"
//#include "Communication.h"
//#include "ComPort.h"
//#include "SendDataAsu.h"
//#include "Tablo.h"


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
{}

void App::Init()
{
	AppBase().Init();
	App::ProgrammExitEvent		= CreateEvent(NULL, TRUE, FALSE, NULL);
	App::ProgrammContinueEvent	= CreateEvent(NULL, TRUE, FALSE, NULL);
	App::ProgrammStopEvent		= CreateEvent(NULL, FALSE, FALSE, NULL);
	App::WaitThicknessEvent     = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void App::Destroy()
{
	SetEvent(ProgrammExitEvent);
	Sleep(1000);
}

void App::MainWindowTopLabel(wchar_t *txt)
{
}

void App::MainWindowBottomLabel(int n, wchar_t *text)
{
}

void App::MainWindowUpdate()
{
}

bool App::StopAfterCycle()
{
	return true;
}

App app;







