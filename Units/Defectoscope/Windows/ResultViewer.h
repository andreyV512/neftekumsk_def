#pragma once
#include "message.h"
#include "ColorLabel.h"
#include "Chart.h"
#include "ResultData.h"
#include "Chart.hpp"
#include "BarSeries.h"
#include "FixedGridSeries.h"
#include "EmptyLeftAxes.h"
#include "Borders.h"

class ResultViewer
{
	class BottomAxesMeters__: public BottomAxesMeters
	{
	public:
		BottomAxesMeters__(Chart &c): BottomAxesMeters(c, App::zone_length){}
	};
	class Cutting0: public VBorder{public: Cutting0(Chart &); void Draw();};
	class Cutting1: public VBorder{public: Cutting1(Chart &); void Draw();};
public:
	typedef ChartDraw<Chart, TL::MkTlst<
		EmptyLeftAxes
		, BottomAxesMeters__
		, BarSeries
		, FixedGrid		
		, Cutting0
		, Cutting1
	>::Result> TChart;
	TChart chart;
	bool mouseMove;
	Gdiplus::Bitmap *backScreen;
	ColorLabel label;
	Cursor cursor;
	bool painting;
public:
	HWND hWnd;
	TMouseMove storedMouseMove;
	bool openDetailedWindow;
	ResultViewerData &viewerData;
	ResultViewer();
	unsigned operator()(TCreate &);
	void operator()(TSize &);
	void operator()(TPaint &);
	void operator()(TMouseMove &);
	void operator()(TLButtonDbClk &);
	void operator()(TMouseWell &);
	void operator()(TLButtonDown &l);
	void operator()(TDestroy &);

	bool Draw(TMouseMove &, VGraphics &);
	bool GetColorBar(int , double &, unsigned &);
};

