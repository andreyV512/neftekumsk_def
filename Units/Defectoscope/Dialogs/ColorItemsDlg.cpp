#include "stdafx.h"
#include "Dialogs.h"
#include "DebugMess.h"
#include "Dlgfiles.h"
#include "..\DlgTemplates\ParamDlg.hpp"
#include "AppBase.h"

namespace{
void __color_wm_paint(HWND hwnd, int color)
{
	PAINTSTRUCT p;
	HDC hdc = BeginPaint(hwnd, &p);
	{		
		Gdiplus::Graphics g(hdc);
		RECT r;
		GetClientRect(hwnd, &r);
		g.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(color)), 0, 0, r.right, r.bottom);
	}
	EndPaint(hwnd, &p);
}

int __color_l_button_down(HWND hwnd)
{
	dprint("%s", __FUNCTION__);
	ColorDialog c(hwnd);
	char d[4] = {-1};
	if(c())
	{
		dprint("%s %x", __FUNCTION__, c.color.rgbResult);

		*(int *)d = c.color.rgbResult | 0xff000000;
		char t = d[0];
		d[0] = d[2];
		d[2] = t;
		InvalidateRect(hwnd, NULL, true);
	}
	return *(int *)d;
}

template<class T>struct __color__
{	
	static LRESULT CALLBACK Proc_(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_PAINT:
			{
				T *t = (T *)GetWindowLong(hwnd, GWL_USERDATA);
				if(t)
				{
					__color_wm_paint(hwnd, t->value);
				}
			}
			return 0;
		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
			{
				T *t = (T *)GetWindowLong(hwnd, GWL_USERDATA);
				if(t)
				{
			    t->value = __color_l_button_down(hwnd);
				}
			}
			return 0;
		}
		return CallWindowProc(OldWndProc, hwnd, msg, wParam, lParam);
	}
	static WNDPROC OldWndProc;
};

 template<class T>WNDPROC __color__<T>::OldWndProc;

template<class T>struct ColorButtonItem
{
	HWND Init(HWND h, int &width, int &dy, T &t)
	{
		HWND hWnd = CreateWindow(L"button", L""
			, WS_VISIBLE | WS_CHILD | WS_TABSTOP
			,10, dy, 100, 30, h, (HMENU)0, hInstance, 0
			);
		__color__<T>::OldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
		SetWindowLong(hWnd, GWL_WNDPROC, (long ) __color__<T>::Proc_);
		SetWindowLong(hWnd, GWL_USERDATA, (long )&t);
		CreateWindow(L"static", ParamTitle<T>()()
			, WS_VISIBLE | WS_CHILD
			, 100 + 20, dy + 7, dlg_width, 20, h, 0, hInstance, NULL
			);
		dy += 35;

		return hWnd;
	}
};

//class CopyFactory
//{
//template<class O, class P>struct loc
//{
//	void operator ()(O *o, P *p)
//	{
//		o->value = p->get<O>().value;
//	}
//};
//public:
//	template<class List>static void Do(TL::Factory<List> &to, TL::Factory<List> &from)
//	{
//		TL::foreach<List, loc>()(&to, &from);
//	}
//};

#define DLG_SUB(n)template<>struct DlgSubItems<n, int>: ColorButtonItem<n>{};\
template<>struct __data_from_widget__<DlgItem<n>, int>\
{\
    int operator()(DlgItem<n> &o)\
	{\
		return o.value.value;\
	}\
};

DLG_SUB(Clr<Undefined>			)
DLG_SUB(Clr<Nominal  >			)
DLG_SUB(Clr<DeathZone>			)
DLG_SUB(Clr<BKlass2<Long>      >)
DLG_SUB(Clr<BKlass2<Thickness> > )
DLG_SUB(Clr<BDefect<Thickness> > )
DLG_SUB(Clr<BDefect<Long>      >)
DLG_SUB(Clr<BKlass2<Cross>     >)
DLG_SUB(Clr<BDefect<Cross>     >)

//------------------------------------------------------------------------------------------------
//PARAM_TITLE(LessMinimumEnergy, L"Энергия меньше минимума")
//PARAM_TITLE(GreaterMaximumEnergy, L"Энергия больше максимума")
//PARAM_TITLE(ValueLessThreshold, L"Импульс меньше порога")
//PARAM_TITLE(ThicknessLessThreshold, L"Измеренная величина меньше минимальной")
//PARAM_TITLE(Crl<Undefined>, L"Результат не определён")
//PARAM_TITLE(Nominal, L"Номинальная толщина")
//PARAM_TITLE(Defect, L"Брак")
//PARAM_TITLE(Treshold2Class, L"Класс 2")
//PARAM_TITLE(DeathZone, L"Мёртвая зона")

PARAM_TITLE(Clr<Undefined>			 , L"Результат не определён")
PARAM_TITLE(Clr<Nominal  >			 , L"\"1 класс\"")
PARAM_TITLE(Clr<DeathZone>			 , L"Мёртвая зона")
PARAM_TITLE(Clr<BKlass2<Thickness> > , L"\"2 класс\" толщина")
PARAM_TITLE(Clr<BDefect<Thickness> > , L"Брак толщина")
PARAM_TITLE(Clr<BKlass2<Long>      > , L"\"2 класс\" продольный дефект")
PARAM_TITLE(Clr<BDefect<Long>      > , L"Продольный дефект")
PARAM_TITLE(Clr<BKlass2<Cross>     > , L"\"2 класс\" поперечный дефект")
PARAM_TITLE(Clr<BDefect<Cross>     > , L"Поперечный дефект")

DO_NOT_CHECK(Clr<Undefined>			)
DO_NOT_CHECK(Clr<Nominal  >			)
DO_NOT_CHECK(Clr<DeathZone>			)
DO_NOT_CHECK(Clr<BKlass2<Thickness>> )
DO_NOT_CHECK(Clr<BDefect<Thickness>>)
DO_NOT_CHECK(Clr<BKlass2<Long>     >)
DO_NOT_CHECK(Clr<BDefect<Long>     >)
DO_NOT_CHECK(Clr<BKlass2<Cross>    >)
DO_NOT_CHECK(Clr<BDefect<Cross>    >)

struct DefaultBtn
{
	static const int width = 160;
	static const int height = 30;
	static const int ID = IDRETRY;
	wchar_t *Title(){return L"Встроенные настройки";}
	template<class Owner>void BtnHandler(Owner &o, HWND h)
	{
		dprint(__FUNCTION__"test");
		if(TestPassword<Owner::Table>()(h))
		{
			CBase base(ParametersBase().name());
			if(base.IsOpen())
			{
				ColorTable color;
				UpdateWhere<ColorTable>(color, base).ID(1).Execute();
				CopyFactory::Do(Singleton<ColorTable>::Instance().items, color.items);
			}
			EndDialog(h, FALSE);
		}
	}
};
}
void ColorItemsDlg::Do(HWND h)
{
	ColorTable color;
	CopyFactory::Do(color.items, Singleton<ColorTable>::Instance().items);
	if(TemplDialogList<ColorTable
		, TL::MkTlst<
		Clr<Undefined>	
		, Clr<DeathZone>	
		, Clr<Nominal  >			
		, Clr<BKlass2<Thickness>>
		, Clr<BDefect<Thickness>>
		, Clr<BKlass2<Long>     >
		, Clr<BDefect<Long>     >
		, Clr<BKlass2<Cross>    >
		, Clr<BDefect<Cross>    >
		>::Result
		, TL::MkTlst<OkBtn, CancelBtn, DefaultBtn>::Result>(color).Do(h, L"Цвета"))
	{
		CopyFactory::Do(Singleton<ColorTable>::Instance().items, color.items);
	}
}

