#pragma once
#include "AppBase.h"
#include "MenuApi.h"

#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"

class LongWindow;
class CrossWindow;
class ThicknessWindow;
template<class T>struct ChangeType;
template<>struct ChangeType<LongWindow>
{
	typedef Long Type;
};
template<>struct ChangeType<CrossWindow>
{
	typedef Cross Type;
};

template<class T, int N>struct ParamTitle<Corec<ASignal<T,N>>>{wchar_t *operator()(){return L"Корректировка";}};

template<class T, int N>struct Less<typename Corec<ASignal<T,N>>>{typename Corec<ASignal<T,N>>::type_value operator()(){return 0.1;}};
template<class T, int N>struct Largen<typename Corec<ASignal<T,N>>>{typename Corec<ASignal<T,N>>::type_value operator()(){return 2.0;}};

template<class T, int N>struct TopMenu<ASignal<T, N>>			   
	{										   
		typedef NullType list;				   
	};										   
	
	template<class T, int N>struct NameMenu<TopMenu<ASignal<T, N>>>{wchar_t *operator()(HWND){return L"Коэффициент";}};	

template<class T>struct ViewMenu;

template<class T, int N>struct ViewMenu<Corec<ASignal<T,N>>>
{
	static void Do(HWND h)
	{
		wchar_t buf[128];
		wsprintf(buf, L"Корректировка датчика %d", N);
		if(TemplDialogList<
			CorecSignalTable
			, typename TL::MkTlst<Corec<ASignal<typename ChangeType<T>::Type, N>>>::Result
		>(Singleton<CorecSignalTable>::Instance()).Do(h, buf))
		{		
			RepaintWindow(GetParent(h));
		}
	}
};
											   
template<class T, int N>struct Event<TopMenu<ASignal<T, N>> >	   
{										   
	static void Do(HWND h)				   
	{									   
		ViewMenu<Corec<ASignal<T, N>>>::Do(h);	
	}									   
};
template<class T, int N>struct SubMenuLine
{
	typedef typename TL::MkTlst<						   
		TopMenu<ASignal<T, N>>						   
		>::Result items_list;	
	void operator()(HWND h)
	{
		PopupMenu<items_list>::Do(h, h);
	}
};
template<int N>struct SubMenuLine<ThicknessWindow,N>
{
	void operator()(HWND)
	{		
	}
};

template<class T, int N>struct Line: LineTresholdsViewer<typename TL::SelectT<ThresholdsTable::items_list, typename T::sub_type>::Result>
{
	typedef LineTresholdsViewer<typename TL::SelectT<ThresholdsTable::items_list, typename T::sub_type>::Result> Parent;
	T *owner;		
	DataViewer<typename T::sub_type, N> dataViewer;
	Line()
	{
		((Parent::TChart *)chart)->items.get<BarSeries>().SetColorBarHandler(this, &Line::GetColorBar);
		cursor->SetMouseMoveHandler(this, &Line<T, N>::CursorDraw);
	}	
	bool GetColorBar(int offs, double &data, unsigned &color)
	{
		if(NULL != dataViewer.data && offs < dataViewer.count)
		{
			data = dataViewer.data[offs];
			color = ConstData::ZoneColor(dataViewer.status[offs]);
			return true;
		}
		return false;
	}

	bool CursorDraw(TMouseMove &l, VGraphics &g)	  
	{	
		if(owner->drawZones)
		{
			double valY = ((Parent::TChart *)chart)->items.get<BarSeries>().ValueY(offsetX);
			int color;
			bool b;
			char *s = StatusText()(dataViewer.status[offsetX], color, b);
			wsprintf(label.buffer, L"<ff>Зона <ff0000>%d <ff>датчик <ff0000>%d <ff>смещение %d  величина %s   %S     "
				, 1 + owner->lastZone, 1 + N, offsetX, Wchar_from<double, 5>(valY)(), s);
			zprint("\n");
		}
		else
		{
			label.buffer[0] = 0;
		}
		label.Draw(g());
		return true;
	}
void operator()(TRButtonDown &l)
{
	SubMenuLine<T, N>()(l.hwnd);
}
};