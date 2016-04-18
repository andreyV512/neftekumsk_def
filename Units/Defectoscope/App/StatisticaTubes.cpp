#include "stdafx.h"
#include "App.h"
#include <WindowsX.h>
#include "ItemIni.h"
#include "typelist.hpp"
#include "MainWindow.h"

namespace
{
wchar_t *section = L"Statistica";
wchar_t *tube = L"Tube";
wchar_t *brak = L"Brak";

struct __Common__{};
struct __Brak__{};

template<class T>struct Type;
template<>struct Type<__Common__>{wchar_t *operator()(){return tube;}};
template<>struct Type<__Brak__>{wchar_t *operator()(){return brak;}};
template<class T>struct Hwnd;
template<>struct Hwnd<__Common__>
{
	template<class Z>HWND operator()(Z &z){return z.app.mainWindow.hCommonTube;}
};
template<>struct Hwnd<__Brak__>
{
	template<class Z>HWND operator()(Z &z){return z.app.mainWindow.hBrakTube;}
};

template<class T>struct Title;
template<>struct Title<__Common__>
{
	wchar_t buf[64];
	wchar_t *operator()(int n){ wsprintf(buf, L"Общее количество: %d", n); return buf;}
};
template<>struct Title<__Brak__>
{
	wchar_t buf[64];
	wchar_t *operator()(int n){ wsprintf(buf, L"Брак количество : %d", n); return buf;}
};
template<class T>struct AddT
{
	template<class Z>void operator()(Z &z)
	{
		int t =  ItemIni::Get(section, Type<T>()(), 0, z.path);
		++t;
		ItemIni::Set(section, Type<T>()(), t, z.path);
		Static_SetText(Hwnd<T>()(z), Title<T>()(t));
	}
};
template<class T>struct Print
{
	template<class Z>void operator()(Z &z)
	{
		int t =  ItemIni::Get(section, Type<T>()(), 0, z.path);
		Static_SetText(Hwnd<T>()(z), Title<T>()(t));
	}
};
}
class Statistica
{
public:
	App &app;
	wchar_t path[1024];
public:
	Statistica::Statistica(App &app)
		: app(app)
	{
		GetModuleFileName(0, path, dimention_of(path));
	    int len = wcslen(path);
	    wcsncpy_s(&path[len - 4], 9, L"Base.ini", 9);
	}
	void Statistica::AddTube()
	{
		//int t = ItemIni::Get(section, tube, 0, path);
		//++t;
		//ItemIni::Set(section, tube, t, path);
		//wchar_t buf[128];
		//wsprintf(buf, L"Общее количество: %d", t);
		//Static_SetText(app.mainWindow.hCommonTube, buf);
        AddT<__Common__>()(*this);
	}
	void Statistica::AddBrakTube()
	{
		//int t = ItemIni::Get(section, tube, 0, path);
		//++t;
		//ItemIni::Set(section, tube, t, path);
		//wchar_t buf[128];
		//wsprintf(buf, L"Брак количество : %d", t);
		//Static_SetText(app.mainWindow.hBrakTube, buf);
		 AddT<__Brak__>()(*this);
	}
	void Statistica::Clear()
	{

	}
};