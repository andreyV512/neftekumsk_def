#pragma once
#include "WindowsPosition.h"
#include "Dialogs.h"
namespace IOportsWindowMenu
{
	struct MainFile{};
	MENU_TEXT(L"Файл", TopMenu<MainFile>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct MainExit{static void Do(HWND h){DestroyWindow(h);}};

	MENU_ITEM(L"Выход", MainExit)

	template<>struct TopMenu<MainFile>
	{
		typedef TL::MkTlst<
			MenuItem<MainExit>
		>::Result list;
	};
//-----------------------------------------------------------------------------
	struct MainOptionUnits{};
	MENU_TEXT(L"Настройки", TopMenu<MainOptionUnits>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowPosition : WindowPositionDlg<IOportsWindow>{};

	MENU_ITEM(L"Сохранить координаты окна", WindowPosition)

	template<>struct TopMenu<MainOptionUnits>
	{
		typedef TL::MkTlst<
			MenuItem<WindowPosition>
		>::Result list;
	};

	typedef TL::MkTlst<
		TopMenu<MainFile>
		, TopMenu<MainOptionUnits>
	>::Result MainMenu;
//..++++++++++++++++++
	struct MainOptionUnits1{};
	MENU_TEXT(L"Настройки", TopMenu<MainOptionUnits1>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowPosition1 : WindowPositionDlg<IOportsWindow1>{};

	MENU_ITEM(L"Сохранить координаты окна", WindowPosition1)

	template<>struct TopMenu<MainOptionUnits1>
	{
		typedef TL::MkTlst<
			MenuItem<WindowPosition1>
		>::Result list;
	};

	typedef TL::MkTlst<
		TopMenu<MainFile>
		, TopMenu<MainOptionUnits1>
	>::Result MainMenu1;
}

