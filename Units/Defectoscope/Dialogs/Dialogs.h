#pragma once
#include <windows.h>
#include "typelist.hpp"
//-----------------------------------------------------------------
class CopyFactory
{
template<class O, class P>struct loc
{
	void operator ()(O *o, P *p)
	{
		o->value = p->get<O>().value;
	}
};
public:
	template<class List>static void Do(TL::Factory<List> &to, TL::Factory<List> &from)
	{
		TL::foreach<List, loc>()(&to, &from);
	}
};
//-------------------------------------------------------------------
#define DLG(n)struct n{static void Do(HWND);};

DLG(Descriptor1730Dlg)
DLG(Outputs0Dlg)
DLG(Inputs0Dlg)

DLG(Outputs1Dlg)
DLG(Inputs1Dlg)

DLG(AddTypeSizeDlg)
DLG(DelTypeSizeDlg)
DLG(DeadZonesDlg)
DLG(AboutWindowDlg)
DLG(IOportsDlg)
DLG(TestTabsDlg)
DLG(RecalculationDlg)
DLG(MedianFiltreDlg)
DLG(CrossDefectFiltreDlg)
DLG(LongDefectFiltreDlg)

DLG(CrossThresholdsDlg)
DLG(LongThresholdsDlg)
DLG(MinimumTubeLengthDlg)

DLG(ASignalCrossDlg)
DLG(ASignalLongDlg)
DLG(GainCrossDlg)
DLG(GainLongDlg)

DLG(ComPortDlg)
DLG(AnalogBoardDlg)

DLG(TcpDlg)

DLG(IOports1Dlg)

DLG(LirParamDlg)

DLG(StoreDataDlg)

DLG(ClearCounterDlg)
DLG(BaseLirDlg)
DLG(LirDescriptorDlg)
DLG(ColorItemsDlg)

DLG(ControlItemOffsetDlg)
DLG(ControlItemDlg)

DLG(OffsetsTubeDlg)

struct LoadDataDlg{static bool Do(HWND);};

#undef DLG

template<class T>struct WindowPositionDlg
{
	static void Do(HWND h)
	{
		RECT r;
		GetWindowRect(h, &r);
		WindowPosition::Set<T>(r);
	}
};