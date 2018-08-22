#include "App.h"
#include "MainWindow.h"
#include "EmptyWindow.h"
#include "DebugMess.h"
#include "LogBuffer.h"
#include "WindowsPosition.h"

namespace{
	MainWindow mainWindow;
}

App::App()
{
	zprint("%s %s", __DATE__, __TIME__);
    RECT r;
	WindowPosition::Get<MainWindow>(r);
	HWND h = WindowTemplate(&mainWindow, L"�������", r.left, r.top, r.right, r.bottom, IDI_LETTER);
	ShowWindow(h, SW_SHOWNORMAL);
}

void App::Destroy()
{
}