#include "stdafx.h"
#include "Config.h"
#include "Lir.h"
#include <MMSystem.h>
#include "AppBase.h"
#include "inc/bdaqctrl.h"
#include "AnalogBoard.h"
#include "DebugMess.h"
#include "USPCData.h"
using namespace Automation::BDaq;
namespace
{
	Lir &lir = Singleton<Lir>::Instance();
	AnalogBoard &analogBoard = Singleton<AnalogBoard>::Instance();
	RowData &rowData = Singleton<RowData>::Instance();
}
Lir::Lir()
	: zone0(Singleton<LirParamTable>::Instance().items.get<TickPerZoneLir0>().value)
	, zone1(Singleton<LirParamTable>::Instance().items.get<TickPerZoneLir1>().value)
{}

#define cnt0 ((UdCounterCtrl *)cnt0_)
#define cnt1 ((UdCounterCtrl *)cnt1_)

bool Lir::Init(int id)
{
#ifndef DEBUG_ITEMS
	cnt0_  = (void *)AdxUdCounterCtrlCreate();
	cnt1_  = (void *)AdxUdCounterCtrlCreate();

	DeviceInformation devInfo(id);
	ErrorCode ret = cnt0->setSelectedDevice(devInfo);
	if(Success == ret)ret = cnt1->setSelectedDevice(devInfo);
	if(Success == ret)ret = cnt0->setChannel(0);
	if(Success == ret)ret = cnt1->setChannel(1);
	if(Success == ret)ret = cnt0->setCountingType(PulseDirection);
	if(Success == ret)ret = cnt1->setCountingType(PulseDirection);
	if(Success == ret)ret= cnt0->setEnabled(true);
	if(Success == ret)ret= cnt1->setEnabled(true);
	return Success == ret;
#else
	return true;
#endif
}
void Lir::Clear()   
{
	cnt0->setInitialValue(0);
	cnt1->setInitialValue(0);
	ptrTick = &Lir::Tick0;
	lenZone = zone0;
	SetCross(this, &Lir::Noop);
	SetLong(this, &Lir::Noop);
	SetThick(this, &Lir::Noop);
	rowData.Clear();
}

unsigned Lir::Tick0()
{
	tmpTick = cnt1->getValue();
	return tick = cnt0->getValue();	
}
unsigned Lir::Tick1()
{
	return tick + cnt1->getValue() - tmpTick;
}
void Lir::__Do__()
{
	Data data = {(this->*ptrTick)(), timeGetTime(), lenZone};
	ULONG *signal;
	int count = analogBoard.Read(signal);
	if(count > 0)
	{
		rowData.SetData(signal, count);
	}
	(oCross->*ptrCross)(data);
	(oLong->*ptrLong)(data);
	(oThick->*ptrThick)(data);
}
void Lir::Do()
{
	lir.__Do__();
}

void Lir::SetTick1()
{
	lenZone = zone1;
	ptrTick = &Lir::Tick1;
}

void Lir::TestLir()
{
	double countZones = (double)App::distance_between_sensors / App::zone_length;
	double t0 = (double)(stopLir0 - startLir0) / countZones;
	double t1 = (double)(stopLir1 - startLir1) / countZones;
	dprint("-----## -- lir %d %d %d %d\n", startLir0, stopLir0, startLir1, stopLir1);
	wchar_t buf[128];
	wsprintf(buf, L"лир0-%s лир1-%s"
		, Wchar_from<double, 4>(t0)()
		, Wchar_from<double, 4>(t1)()
		);
	app.MainWindowBottomLabel(App::status_lir, buf);
}

void Lir::Start0()
{
	startLir0 = cnt0->getValue();
}
void Lir::Start1()
{
	startLir1 = cnt1->getValue();
}
void Lir::Stop0() 
{
	stopLir0 = cnt0->getValue();
}
void Lir::Stop1()
{
	stopLir1 = cnt1->getValue();
}

#undef cnt0
#undef cnt1