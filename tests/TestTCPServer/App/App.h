#pragma once
#include <windows.h>
class App
{
public:
	static HANDLE WaitThicknessEvent;
	static HANDLE ProgrammContinueEvent;
	void MainWindowTopLabel(wchar_t *);
	void MainWindowBottomLabel(int, wchar_t *);
};

extern App app;