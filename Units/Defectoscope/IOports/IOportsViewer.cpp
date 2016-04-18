#include "stdafx.h"
#include "IOportsViewer.h"
#include "ColorLabel.h"
#include "AppBase.h"
#include "DebugMess.h"
#include "Chart.h"
#include "Device1730.h"
#include "App.h"
using namespace Gdiplus;
//-----------------------------------------------------------------------------
namespace
{
struct __draw_data__
{
	int x, dY;
	Graphics &g;
	int colorOn;
	int value;
	__draw_data__(int x, Graphics &g, int colorOn, int value)  : x(x), dY(15), g(g), colorOn(colorOn), value(value) {}
};

template<class T>struct MessageField
{
	wchar_t buf[128];
	wchar_t *Text()
	{		
		wsprintf(buf, L"%S", &__FUNCTION__[43]);
		int len = wcslen(buf);
		buf[len - 7] = 0;
		return buf;
	}
};

template<class O, class P>struct __draw__
{
	void operator()(O *o, P *p)
	{
		ColorLabel l;
		l.left = p->x;
		l.top = p->dY;
		wsprintf(l.buffer, L"<55>%s",  MessageField<O>().Text());
		l.Draw(p->g);
		int color = 0xffcccccc;
		p->g.FillRectangle(&SolidBrush(Color(color)), p->x - 20, p->dY - 3, 15, 15);
		p->dY += 20;
	}
};
//------------------------------------------------------------------------------------
struct __update_data__
{
	int x, dY;
	HDCGraphics &g;
	int colorOn;
	int value;
	__update_data__(int x, HDCGraphics &g, int colorOn, int value)  : x(x), dY(15), g(g), colorOn(colorOn), value(value) {}
};
template<class O, class P>struct __update__
{
	void operator()(O *o, P *p)
	{
		int color = 0xffcccccc;
		if(o->value & p->value) color = p->colorOn;
		p->g.graphics.FillRectangle(&SolidBrush(Color(color)), p->x - 20, p->dY - 3, 15, 15);
		p->dY += 20;
	}
};
struct __mouse_down_data__
{
	int x, dY;
	HDCGraphics &g;
	int colorOn;
	unsigned &value;
	TLButtonDown &l;
	Device1730 &device1730;
	__mouse_down_data__(int x, HDCGraphics &g, int colorOn, unsigned &value, TLButtonDown &l, Device1730 &device1730)  
		: x(x), dY(15), g(g), colorOn(colorOn), value(value), l(l) 
		, device1730(device1730)
	{}
};
template<class O, class P>struct __mouse_down__
{
	void operator()(O *o, P *p)
	{
		int x0 = p->x - 20;
		int x1 = x0 + 15;
		int y0 = p->dY - 3;
		int y1 = y0 + 15;
		if(p->l.x > x0 && p->l.x < x1 && p->l.y > y0 && p->l.y < y1)
		{
			p->value ^= o->value;
			p->device1730.WriteOutput(p->value);
		}
		int color = 0xffcccccc;
		unsigned output = p->device1730.ReadOutput();
		if(o->value & output) color = p->colorOn;
		p->g.graphics.FillRectangle(&SolidBrush(Color(color)), x0, y0, 15, 15);
		p->dY += 20;
	}
};
VOID CALLBACK __Update__(PVOID oo, BOOLEAN)
{	
	IOportsViewer *o = (IOportsViewer *)oo;
	if(App::measurementOfRunning != o->lastTitle)
	{
		o->lastTitle = App::measurementOfRunning;
		wchar_t *title = o->lastTitle
			? L"Просмотр дискретных входов-выходов (плата 0)"
			: L"Управление дискретными выходами (плата 0)"
		;
		SetWindowText(o->hWnd, title);
	}
	HDCGraphics g(o->hWnd, o->backScreen);
    unsigned input = device1730_0.Read();
	unsigned output = device1730_0.ReadOutput(); 
	TL::foreach<InputsTable<0>::items_list, __update__>()(&Singleton<InputsTable<0>>::Instance().items, &__update_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<0>::items_list, __update__>()(&Singleton<OutputsTable<0>>::Instance().items, &__update_data__(230, g, 0xffff0000, output));
}
VOID CALLBACK __Update_1__(PVOID oo, BOOLEAN)
{	
	IOportsViewer1 *o = (IOportsViewer1 *)oo;
	if(App::measurementOfRunning != o->lastTitle)
	{
		o->lastTitle = App::measurementOfRunning;
		wchar_t *title = o->lastTitle
			? L"Просмотр дискретных входов-выходов (плата 1)"
			: L"Управление дискретными выходами (плата 1)"
		;
		SetWindowText(o->hWnd, title);
	}
	HDCGraphics g(o->hWnd, o->backScreen);
    unsigned input = device1730_1.Read();
	unsigned output = device1730_1.ReadOutput(); 
	TL::foreach<InputsTable<1>::items_list, __update__>()(&Singleton<InputsTable<1>>::Instance().items, &__update_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<1>::items_list, __update__>()(&Singleton<OutputsTable<1>>::Instance().items, &__update_data__(230, g, 0xffff0000, output));
}
}
//--------------------------------------------------------------------------------------
IOportsViewer::IOportsViewer(HWND &h, Bitmap *&bs)
	: hWnd(h)
	, backScreen(bs)
	, hTimer(NULL)
{}
//----------------------------------------------------------------------------------------
void IOportsViewer::Size(Graphics &g, int width, int height)
{
	g.FillRectangle(&SolidBrush(Color(0xffaaaaaa)), 0, 0, width, height);
	unsigned input = device1730_0.Read();
	unsigned output = device1730_0.ReadOutput(); 
	TL::foreach<InputsTable<0>::items_list, __draw__>()(&Singleton<InputsTable<0>>::Instance().items, &__draw_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<0>::items_list, __draw__>()(&Singleton<OutputsTable<0>>::Instance().items, &__draw_data__(230, g, 0xffff0000, output));
}
//---------------------------------------------------------------------------------------
void IOportsViewer::Start()
{
	lastTitle = false;
	CreateTimerQueueTimer(&hTimer, NULL, __Update__, this, 2000, 500, WT_EXECUTEDEFAULT);
}
//------------------------------------------------------------------------------------------
void IOportsViewer::Stop()
{
	if(hTimer)DeleteTimerQueueTimer( NULL, hTimer, NULL );
}
//-------------------------------------------------------------------------------------------------
void IOportsViewer::MouseLDown(TLButtonDown &l)
{
	if(App::measurementOfRunning) return;
	HDCGraphics g(hWnd, backScreen);
	unsigned input = device1730_0.Read();
	unsigned output = device1730_0.ReadOutput();
	TL::foreach<InputsTable<0>::items_list, __update__>()(&Singleton<InputsTable<0>>::Instance().items, &__update_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<0>::items_list, __mouse_down__>()(&Singleton<OutputsTable<0>>::Instance().items
		, &__mouse_down_data__(230, g, 0xffff0000, output, l, device1730_0)
		);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
IOportsViewer1::IOportsViewer1(HWND &h, Bitmap *&bs)
	: hWnd(h)
	, backScreen(bs)
	, hTimer(NULL)
{}
//----------------------------------------------------------------------------------------
void IOportsViewer1::Size(Graphics &g, int width, int height)
{
	g.FillRectangle(&SolidBrush(Color(0xffaaaaaa)), 0, 0, width, height);
	unsigned input = device1730_1.Read();
	unsigned output = device1730_1.ReadOutput(); 
	TL::foreach<InputsTable<1>::items_list, __draw__>()(&Singleton<InputsTable<1>>::Instance().items, &__draw_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<1>::items_list, __draw__>()(&Singleton<OutputsTable<1>>::Instance().items, &__draw_data__(230, g, 0xffff0000, output));
}
//---------------------------------------------------------------------------------------
void IOportsViewer1::Start()
{
	lastTitle = false;
	CreateTimerQueueTimer(&hTimer, NULL, __Update_1__, this, 2000, 500, WT_EXECUTEDEFAULT);
}
//------------------------------------------------------------------------------------------
void IOportsViewer1::Stop()
{
	if(hTimer)DeleteTimerQueueTimer( NULL, hTimer, NULL );
}
//-------------------------------------------------------------------------------------------------
void IOportsViewer1::MouseLDown(TLButtonDown &l)
{
	if(App::measurementOfRunning) return;
	HDCGraphics g(hWnd, backScreen);
	unsigned input = device1730_1.Read();
	unsigned output = device1730_1.ReadOutput();
	TL::foreach<InputsTable<1>::items_list, __update__>()(&Singleton<InputsTable<1>>::Instance().items, &__update_data__(40, g, 0xff0000ff, input));
	TL::foreach<OutputsTable<1>::items_list, __mouse_down__>()(&Singleton<OutputsTable<1>>::Instance().items
		, &__mouse_down_data__(230, g, 0xffff0000, output, l, device1730_1)
		);
}

