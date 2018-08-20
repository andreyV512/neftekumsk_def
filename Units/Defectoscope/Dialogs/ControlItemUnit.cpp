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

PARAM_TITLE(JOIN2(ASignal<Solenoid0U,  0>), L"Контроль температуры соленоида 1")
PARAM_TITLE(JOIN2(ASignal<Solenoid1U,  0>), L"Контроль температуры соленоида 2")
PARAM_TITLE(JOIN2(ASignal<MagneticFieldTurnedOn,  0>), L"Контроль магнитного поля")

#undef	JOIN2

template<class X, int N>struct DlgSubItems<ASignal<X, N>, int >: UpDownSubItem<ASignal<X, N>>{};

void ControlItemOffsetDlg::Do(HWND h)
{

	if(TemplDialog<
		UnitControlsOffsetTable
	>(Singleton<UnitControlsOffsetTable>::Instance()).Do(h, L"Аналоговые входа"))
	{
		if(analogBoard.SetupParams())
		{			
			MessageBox(h, L"Не могу инициировать плату L791", L"Ошибка!!!", MB_ICONERROR);
		}
	}
}

DO_NOT_CHECK(Solenoid0U)
DO_NOT_CHECK(Solenoid1U)
//DO_NOT_CHECK(MagneticFieldTurnedOn)
PARAM_TITLE(Solenoid0U, L"Порог контролируемого напряжения соленоида 1")
PARAM_TITLE(Solenoid1U, L"Порог контролируемого напряжения соленоида 2")
//PARAM_TITLE(MagneticFieldTurnedOn, L"Наличие магнитного поля")

void ControlItemDlg::Do(HWND h)
{
	if(TemplDialog<UnitControlsTable>(Singleton<UnitControlsTable>::Instance()).Do(h, L"Мёртвые зоны"))
	{
	}
}