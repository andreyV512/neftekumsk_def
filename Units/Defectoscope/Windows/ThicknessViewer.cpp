#include "stdafx.h"
#include "ThicknessViewer.h"
#include <stdio.h>
#include "EmptyWindow.h"
#include "LabelMessage.h"
#include "DebugMess.h"
#include "AppBase.h"
#include "App.h"
#include "ThicknessWindow.h"
#include "ViewersMenu.hpp"
#include "ResultData.h"
//------------------------------------------------------------------------------------------------------
using namespace Gdiplus;

bool ThicknessViewer::Draw(TMouseMove &l, VGraphics &g)
{
	int x, y;
	chart.CoordCell(l.x, l.y, x, y);
	bool drawZones =  x < viewerData.currentOffsetZones;
	if(drawZones)
	{
		ResultViewerData &r = Singleton<ResultViewerData>::Instance();
		int color;
		bool b;
		char *s = StatusText()(viewerData.status[x], color, b);
		wchar_t buf[128];
		if(b)
		{

			wsprintf(buf, L"<ff>толщина <ff0000>%s <ff>\"1 класс %s\" \"2 класс %s\" \"3 класс %s\"",
				Wchar_from<double, 3>(viewerData.buffer[0][x])()
				, Wchar_from<double, 4>(r.tresholdKlass1)()
				, Wchar_from<double, 4>(r.tresholdKlass2)()
				, Wchar_from<double, 4>(r.tresholdKlass3)()
				);
		}
		else
		{
			buf[0] = 0;
		}
		wsprintf(label.buffer, L"<ff>Толщина зона %d  <%6x>%S %s"
			, 1 + x
			, color
			, s
			, buf
			);
		label.Draw(g());
	}
	return drawZones;
}

bool ThicknessViewer::GetColorBar(int zone, double &data_, unsigned &color)
{
	data_ = viewerData.buffer[0][zone];
	ColorBar()(
		data_
		, color
		, viewerData.status[zone]
		, Singleton<ThresholdsTable>::Instance().items.get<BNominal<Thickness> >().value//[zone]
	);

	return zone < viewerData.currentOffsetZones;	  
}
//-----------------------------------------------------------------------------
ThicknessViewer::ThicknessViewer()
	: backScreen(NULL)
	, chart(backScreen)
	, cursor(chart)
	, openDetailedWindow(false)
	, painting(true)
	, mouseMove(true)
	, viewerData(Singleton<ItemData<Thickness> >::Instance())
{
	chart.rect.top = 17;
	
	chart.minAxesX = 0;
	chart.maxAxesX = App::zonesCount;
	chart.minAxesY = 0;

	label.fontHeight = 12;
	label.top = 0;	

	cursor.SetMouseMoveHandler(this, &ThicknessViewer::Draw);
	chart.items.get<BarSeries>().SetColorBarHandler(this, &ThicknessViewer::GetColorBar);
}
//----------------------------------------------------------------------------------------------------
#pragma warning(disable : 4996)
void ThicknessViewer::operator()(TSize &l)
{
	if(l.resizing == SIZE_MINIMIZED || 0 == l.Width || 0 == l.Height) return;	
	
	if(NULL != backScreen)
	{
		if(backScreen->GetWidth() < l.Width || backScreen->GetHeight() < l.Height)
		{
			delete backScreen;
		    backScreen = new Bitmap(l.Width, l.Height);
		}
	}
	else if(l.Width > 0 && l.Height > 0)
	{
		backScreen = new Bitmap(l.Width, l.Height);
	}
	else
	{
		return;
	}
    Graphics g(backScreen);
	SolidBrush solidBrush(Color(0xffaaaaaa));
	g.FillRectangle(&solidBrush, 0, 29, 10, l.Height);   
	g.FillRectangle(&solidBrush, 0, 0, l.Width, 29);  

	chart.rect.right = l.Width;
	chart.rect.bottom = l.Height;
	chart.minAxesY = Singleton<AxesTable>::Instance().items.get<AxesYMin<Thickness> >().value;
	chart.maxAxesY = Singleton<AxesTable>::Instance().items.get<AxesYMax<Thickness> >().value;
	chart.Draw(g);
}
//----------------------------------------------------------------------------------------------------
void ThicknessViewer::operator()(TPaint &l)
{
	if(NULL == backScreen) return;
	PAINTSTRUCT p;
	HDC hdc = BeginPaint(l.hwnd, &p);
	{		
		Graphics g(hdc);		
		g.DrawCachedBitmap(&CachedBitmap(backScreen, &g), 0, 0);
		cursor.VerticalCursor(storedMouseMove, PaintGraphics(g));
	}
	EndPaint(l.hwnd, &p);
}
//-----------------------------------------------------------------------------------------------------
void ThicknessViewer::operator()(TMouseMove &l)
{
	if(mouseMove)
	{
		if(cursor.VerticalCursor(l, HDCGraphics(l.hwnd, backScreen)))
		{
			storedMouseMove = l;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void ThicknessViewer::operator()(TLButtonDown &l)
{
	mouseMove = false;
}
//--------------------------------------------------------------------------
void ThicknessViewer::operator()(TLButtonDbClk &l)
{
	mouseMove = true;
	if(cursor.VerticalCursor(*(TMouseMove *)&l, HDCGraphics(l.hwnd, backScreen)))
	{
		storedMouseMove.x = l.x;
	}
}
void ThicknessViewer::operator()(TMouseWell &l)
{	
		mouseMove = false;

		OffsetToPixel(
			chart
			, storedMouseMove.x
			, storedMouseMove.y
			, l.delta / 120
			, true 
			);
		cursor.VerticalCursor(storedMouseMove, HDCGraphics(storedMouseMove.hwnd, backScreen));
}
//------------------------------------------------------------------------------------------------------
unsigned ThicknessViewer::operator()(TCreate &l)
{
	storedMouseMove.hwnd = l.hwnd;
	storedMouseMove.x = 0;	
	storedMouseMove.y = WORD(chart.rect.top + 1);
	return 0;
}
//------------------------------------------------------------------------------------------
//CONTEXT_MENU(ThicknessWindow)
void ThicknessViewer::operator()(TRButtonDown &l)
{
	//PopupMenu<ContextMenuThicknessWindow::items_list>::Do(l.hwnd, l.hwnd);
}
//--------------------------------------------------------------------------------
/*
void ThicknessViewer::operator()(TDestroy &m)
{
	delete backScreen;
    backScreen = NULL;
	SetWindowLongPtr(m.hwnd, GWLP_USERDATA, NULL);
}
*/
