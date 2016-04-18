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
bool ACh13::Do()
{
	//1unsigned t = timeGetTime();
	//1if(t > lastTime)
	//1{
	//1	lastTime = t + 3000;
	//1	double d = analogBoard.ReadAsunc(solenoid0Id);
	//1	res = d > tresh0;
	//1	if(res)
	//1	{
	//1		Log::Mess<LogMess::TemperatureOverheadedSolenoid0>();
	//1	}
	//1}
	return false;//return res;
	//return res;
	return false;
}
unsigned ACh14::lastTime;
bool ACh14::res;
bool ACh14::Do()
{
	//unsigned t = timeGetTime();
	//if(t > lastTime)
	//{
	//	lastTime = t + 3000;
	//	double d = analogBoard.ReadAsunc(solenoid1Id);
	//	res = d > tresh1;
	//	if(res)
	//	{
	//		Log::Mess<LogMess::TemperatureOverheadedSolenoid1>();
	//	}
	//}
	//return res;
	return false;
}

bool ACh15::Do()
{
	return true;//analogBoard.ReadAsunc(magneticId) < 1.0;
}
