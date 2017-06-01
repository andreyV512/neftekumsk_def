#include "stdafx.h"
#include "SolenoidControl.h"
#include <MMSystem.h>
#include "AnalogBoard.h"
#include "DebugMess.h"
#include "AppBase.h"
#include "LogBuffer.h"

namespace
{
	AnalogBoard &analogBoard = Singleton<AnalogBoard>::Instance();
	UnitControlsOffsetTable::TItems &items = Singleton<UnitControlsOffsetTable>::Instance().items;
	int &solenoid0Id = items.get<ASignal<Solenoid0U, 0>>().value; 
	int &solenoid1Id = items.get<ASignal<Solenoid1U, 0>>().value; 
	int &magneticId = items.get<ASignal<MagneticFieldTurnedOn, 0>>().value; 

	UnitControlsTable::TItems &vals = Singleton<UnitControlsTable>::Instance().items;
	double &tresh0 = vals.get<Solenoid0U>().value;
	double &tresh1 = vals.get<Solenoid1U>().value;

}
unsigned ACh13::lastTime;
bool ACh13::res;
bool ACh13::Do(unsigned)
{
	return false;
}
unsigned ACh14::lastTime;
bool ACh14::res;
bool ACh14::Do(unsigned)
{
	return false;
}

bool ACh15::Do(unsigned)
{
	return true;
}
