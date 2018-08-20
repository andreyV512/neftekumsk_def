#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"
#include "AnalogBoard.h"
#include "Common.h"

namespace
{
	AnalogBoard &analogBoard = Singleton<AnalogBoard>::Instance();
}

template<class X, int N, template<class>class Wapper, class Z>struct Skip<Wapper<ASignal<X, N>>, Z>
{
	template<class P>bool operator()(Wapper<ASignal<X, N>> *, P *){return true;}
};

#define	JOIN2(a, b) a##,##b

PARAM_TITLE(JOIN2(ASignal<Cross,  0>), L"Поперечный датчик  0")
PARAM_TITLE(JOIN2(ASignal<Cross,  1>), L"Поперечный датчик  1")
PARAM_TITLE(JOIN2(ASignal<Cross,  2>), L"Поперечный датчик  2")
PARAM_TITLE(JOIN2(ASignal<Cross,  3>), L"Поперечный датчик  3")
PARAM_TITLE(JOIN2(ASignal<Cross,  4>), L"Поперечный датчик  4")
PARAM_TITLE(JOIN2(ASignal<Cross,  5>), L"Поперечный датчик  5")
PARAM_TITLE(JOIN2(ASignal<Cross,  6>), L"Поперечный датчик  6")
PARAM_TITLE(JOIN2(ASignal<Cross,  7>), L"Поперечный датчик  7")
PARAM_TITLE(JOIN2(ASignal<Cross,  8>), L"Поперечный датчик  8")
PARAM_TITLE(JOIN2(ASignal<Cross,  9>), L"Поперечный датчик  9")
PARAM_TITLE(JOIN2(ASignal<Cross, 10>), L"Поперечный датчик 10")
PARAM_TITLE(JOIN2(ASignal<Cross, 11>), L"Поперечный датчик 11")

PARAM_TITLE(JOIN2(ASignal<Long,  0>), L"Продольный датчик  0")
PARAM_TITLE(JOIN2(ASignal<Long,  1>), L"Продольный датчик  1")
PARAM_TITLE(JOIN2(ASignal<Long,  2>), L"Продольный датчик  2")
PARAM_TITLE(JOIN2(ASignal<Long,  3>), L"Продольный датчик  3")
#undef	JOIN2

template<class X, int N>struct DlgSubItems<ASignal<X, N>, int >: UpDownSubItem<ASignal<X, N>>{};

void ASignalCrossDlg::Do(HWND h)
{

	if(TemplDialogList<
		ASignalTable
		, Common::__select_type_sensors__<ASignalTable::items_list, ASignal, Cross>::Result
	>(Singleton<ASignalTable>::Instance()).Do(h, L"Аналоговые входа с поперечных датчиков"))
	{
		if(analogBoard.SetupParams())
		{			
			MessageBox(h, L"Не могу инициировать плату L791", L"Ошибка!!!", MB_ICONERROR);
		}
	}
}

void ASignalLongDlg::Do(HWND h)
{
	if(TemplDialogList<
		ASignalTable
		, Common::__select_type_sensors__<ASignalTable::items_list, ASignal, Long>::Result
	>(Singleton<ASignalTable>::Instance()).Do(h, L"Аналоговые входа с продольных датчиков"))
	{
		if(analogBoard.SetupParams())
		{			
			MessageBox(h, L"Не могу инициировать плату L791", L"Ошибка!!!", MB_ICONERROR);
		}
	}
}

const wchar_t *SyncGainData[] ={L"10", L"5", L"2.5", L"1.25", L"0.625", L"0.312", L"0.156", L"0.078"};

template<class X, int N>struct FillComboboxList<Gain<ASignal<X, N>>>
{
	void operator()(HWND h, Gain<ASignal<X, N>> &)
	{
		for(int i = 0; i < dimention_of(SyncGainData); ++i)
		{
			ComboBox_AddString(h, SyncGainData[i]);
		}
	}
};

template<class X, int N>struct ParamTitle<Gain<ASignal<X, N> > >
{
	wchar_t *operator()(){return ParamTitle<ASignal<X, N>>()();}
};
template<class X, int N, template<class>class Wapper, class Z>struct Skip<Wapper<Gain<ASignal<X, N>>>, Z>
{
	template<class P>bool operator()(Wapper<Gain<ASignal<X, N>>> *, P *){return true;}
};



template<class X, int N>struct CurrentValue<Gain<ASignal<X, N> >>
{
	void operator()(HWND h, Gain<ASignal<X, N> > &)
	{
		const int id = Singleton<GainSignalTable>::Instance().items.get<Gain<ASignal<X, N> > >().value;
		ComboBox_SetCurSel(h, id);
	}
};

template<class X, int N>struct __handler_data_widget__<DlgItem<Gain<ASignal<X,N>> >	, int>
{
	int operator()(HWND h)
	{
		return ComboBox_GetCurSel(h);
	}
};
template<class X, int N>struct DlgSubItems<Gain<ASignal<X, N>>, int >: ComboBoxSubItem<Gain<ASignal<X, N>>>{};

void GainCrossDlg::Do(HWND h)
{
    typedef TL::ListToWapperList<
		Common::__select_type_sensors__<ASignalTable::items_list, ASignal, Cross>::Result 
		, Gain
	>::Result list; 

	if(TemplDialogList<
		GainSignalTable
		, list
	>(Singleton<GainSignalTable>::Instance()).Do(h, L"Усиление входов поперечных датчиков"))
	{
		if(analogBoard.SetupParams())
		{			
			MessageBox(h, L"Не могу инициировать плату L791", L"Ошибка!!!", MB_ICONERROR);
		}
	}
}

void GainLongDlg::Do(HWND h)
{
	typedef TL::ListToWapperList<
		Common::__select_type_sensors__<ASignalTable::items_list, ASignal, Long>::Result 
		, Gain
	>::Result list; 

	if(TemplDialogList<
		GainSignalTable
		, list
	>(Singleton<GainSignalTable>::Instance()).Do(h, L"Усиление входов продольных датчиков"))
	{
		if(analogBoard.SetupParams())
		{			
			MessageBox(h, L"Не могу инициировать плату L791", L"Ошибка!!!", MB_ICONERROR);
		}
	}
}



