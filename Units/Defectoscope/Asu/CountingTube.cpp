#include "stdafx.h"
#include "CountingTube.h"
#include <WindowsX.h>
#include "App.h"
#include "MainWindow.h"
#include "ItemIni.h"
namespace
{
	wchar_t *section = L"CountingTube";

	struct __Common__{};
	struct __Brak__{};

	template<class T>struct NameParam;
#define NAME_PARAM(type, param)template<>struct NameParam<type>{wchar_t *operator()(){return param;}};

	NAME_PARAM(__Common__, L"common")
	NAME_PARAM(__Brak__, L"brak")

	template<class T>struct Hwnd;
#define HWNDD(type, param)template<>struct Hwnd<type>{template<class Z>HWND operator()(Z &z){return z.app.mainWindow.param;}};
	HWNDD(__Common__, hCommonTube)
	HWNDD(__Brak__, hBrakTube)

		template<class T>struct Text;
#define TEXTD(type, param)template<>struct Text<type>\
	{\
	wchar_t buf[64];\
	wchar_t *operator()(int d){wsprintf(buf, param, d); return buf;}};

	TEXTD(__Common__, L"Общее количество труб: %d")
    TEXTD(__Brak__  , L"Бракованных труб         : %d")

	template<class T>struct AddT
	{
		template<class Z>void operator()(Z &z)
		{
			int t = ItemIni::Get(section, NameParam<T>()(), 0, z.fileName);
			++t;
			ItemIni::Set(section, NameParam<T>()(), t, z.fileName);
			Static_SetText(Hwnd<T>()(z), Text<T>()(t));
		}
	};
	template<class T>struct UpdateT
	{
		template<class Z>void operator()(Z &z)
		{
			int t = ItemIni::Get(section, NameParam<T>()(), 0, z.fileName);
			Static_SetText(Hwnd<T>()(z), Text<T>()(t));
		}
	};
	template<class T>struct ClearT
	{
		template<class Z>void operator()(Z &z)
		{
			ItemIni::Set(section, NameParam<T>()(), 0, z.fileName);
			Static_SetText(Hwnd<T>()(z), Text<T>()(0));
		}
	};
}


CountingTube::CountingTube()
	: app( Singleton<App>::Instance())
{
    GetModuleFileName(0, fileName, dimention_of(fileName));
	int len = wcslen(fileName);
	wsprintf(&fileName[len - 4], L"Counting.ini");
}
void CountingTube::AddCommon()
{
	AddT<__Common__>()(*this);
}
void CountingTube::AddBrak()
{
	AddT<__Common__>()(*this);
	AddT<__Brak__>()(*this);
}
void CountingTube::Update()
{
	UpdateT<__Common__>()(*this);
	UpdateT<__Brak__>()(*this);
}
void CountingTube::Clear()
{
	ClearT<__Common__>()(*this);
	ClearT<__Brak__>()(*this);
}