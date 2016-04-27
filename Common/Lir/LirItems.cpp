#include "stdafx.h"
#include "LirItems.h"
#include "USPCData.h"
#include "DebugMess.h"
#include <MMSystem.h>

namespace
{
	RowData &rowData = Singleton<RowData>::Instance();
	Lir &lir = Singleton<Lir>::Instance();
	CrossLir &crossLir = Singleton<CrossLir>::Instance();
	LongLir &longLir = Singleton<LongLir>::Instance();
	ThicknessLir &thicknessLir = Singleton<ThicknessLir>::Instance();
}

void CommonLir::Tick(Lir::Data &d)
{
	unsigned t = ticks[counterTickTime - 1];
	t += d.lenZone;

	if(t >= predTick && t < d.tick)
	{
		ticks[counterTickTime] = t;
		double delta = double(t - predTick)/(d.tick - predTick);
		times[counterTickTime] = predTime + unsigned(delta * (d.time - predTime));		
		predTick = d.tick;
	    predTime = d.time;
		++counterTickTime;
	}	
}
//--------------------------------------------------------
unsigned startCross, startLong;
//-----------------------------------------------------------
void CrossLir::SQ0on(Lir::Data &d)
{
	predTick = d.tick;
	predTime = d.time;
	startCross = timeGetTime();
}
void CrossLir::SQ1on(Lir::Data &d)
{
	counterTickTime = 0;

	tTime = predTime + (d.time - predTime) / 2;
	tTick = predTick + (d.tick - predTick) / 2;

	int count = (d.tick - tTick) / d.lenZone;
	double delta = (double )(d.time - predTime)/ (d.tick - predTick);

	for(int i = 0; i < count; ++i)
	{
		unsigned t = i * d.lenZone;
		times[i] = tTime + unsigned(delta * t);
		ticks[i] = tTick + t;
	}


	predTick = ticks[count - 1];
	predTime = times[count - 1];

	counterTickTime = count;

	lir.SetCross<CrossLir>(this, &CrossLir::Tick);		
}

void CrossLir::SQ0off(Lir::Data &d)
{
	tTime = d.time;
	tTick = d.tick;
	lir.SetCross<Lir>(&lir, &Lir::Noop);	
}
void CrossLir::SQ1off(Lir::Data &d)
{
	tTick += (d.tick - tTick) / 2;
	unsigned deltaTime = times[counterTickTime - 1] - times[counterTickTime - 2];
	unsigned t = ticks[counterTickTime - 1];
	tTick += d.lenZone / 4;
	while(t < tTick)
	{
		t += d.lenZone;
		ticks[counterTickTime] = t;
		times[counterTickTime] = times[counterTickTime - 1] + deltaTime;
		++counterTickTime;
	}
	countZones = counterTickTime;
	int j = 0;
	for(unsigned i = 0; i < countZones; ++i)
	{
		unsigned t = times[i];
		for(; j < rowData.currentFrames; ++j)
		{
			if(t < rowData.timeFrames[j])
			{
				double delta = double(t - rowData.timeFrames[j - 1])/(rowData.timeFrames[j] - rowData.timeFrames[j - 1]);
                offsetsDataOfZone[i] = rowData.offsets[j - 1] + (unsigned)(delta * (rowData.offsets[j] - rowData.offsets[j - 1]));
				break;
			}
		}
	}	
	ItemData<Cross> &item = Singleton<ItemData<Cross>>::Instance();
	memcpy(item.offsets, offsetsDataOfZone, sizeof(item.offsets));
	CorrectionOffset();	
	item.currentOffsetZones = counterTickTime;	 
	//----------------------------------------------
}
void CrossLir::CorrectionOffset()
{
	double t = 45.0 / App::zone_length;
	for(unsigned i = 1; i < countZones; ++i)
	{		
		 unsigned offs = offsetsDataOfZone[i] - offsetsDataOfZone[i - 1];
		 double x = t * offs;
		 offsetsDataOfZone2[i - 1] = offsetsDataOfZone[i - 1] + (unsigned)x;
	}
	//ItemData<Cross> &item = Singleton<ItemData<Cross>>::Instance();
	//memcpy(item.offsets2, offsetsDataOfZone2, sizeof(item.offsets2));
}
//----------------------------------------------------------------------------
//---------------------------------------------------------------------
void LongLir::SQ0on(Lir::Data &d)
{
	predTick = d.tick;
	predTime = d.time;
	startLong = timeGetTime();
}
void LongLir::SQ1on(Lir::Data &d)
{
	counterTickTime = 0;

	tTime = predTime + (d.time - predTime) / 2;
	tTick = predTick + (d.tick - predTick) / 2;

	int count = (d.tick - tTick) / d.lenZone;
	double delta = (double )(d.time - predTime)/ (d.tick - predTick);

	for(int i = 0; i < count; ++i)
	{
		unsigned t = i * d.lenZone;
		times[i] = tTime + unsigned(delta * t);
		ticks[i] = tTick + t;
	}


	predTick = ticks[count - 1];
	predTime = times[count - 1];

	counterTickTime = count;

	lir.SetLong<LongLir>(this, &LongLir::Tick);	
	
}

void LongLir::SQ0off(Lir::Data &d)
{
	tTime = d.time;
	tTick = d.tick;
	lir.SetLong<Lir>(&lir, &Lir::Noop);	
}
void LongLir::SQ1off(Lir::Data &d)
{
	tTick += (d.tick - tTick) / 2;
	unsigned deltaTime = times[counterTickTime - 1] - times[counterTickTime - 2];
	unsigned t = ticks[counterTickTime - 1];
	tTick += d.lenZone / 4;
	while(t < tTick)
	{
		t += d.lenZone;
		ticks[counterTickTime] = t;
		times[counterTickTime] = times[counterTickTime - 1] + deltaTime;
		++counterTickTime;
	}
	countZones = counterTickTime;	
	int j = 0;
	for(unsigned i = 0; i < countZones; ++i)
	{
		unsigned t = times[i];
		for(; j < rowData.currentFrames; ++j)
		{
			if(t < rowData.timeFrames[j])
			{
				double delta = double(t - rowData.timeFrames[j - 1])/(rowData.timeFrames[j] - rowData.timeFrames[j - 1]);
                offsetsDataOfZone[i] = rowData.offsets[j - 1] + (unsigned)(delta * (rowData.offsets[j] - rowData.offsets[j - 1]));
				break;
			}
		}
	}
	dprint("stop long %d", timeGetTime() - startLong);
	ItemData<Long> &item = Singleton<ItemData<Long>>::Instance();
	memcpy(item.offsets, offsetsDataOfZone, sizeof(item.offsets));
	item.currentOffsetZones = counterTickTime;	
	//----------------------------------------------
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//--------------------------------------------------------------------------------
//void ThicknessLir::SQ0on(Lir::Data &){}
//void ThicknessLir::SQ1on(Lir::Data &){}
//void ThicknessLir::SQ0off(Lir::Data &){}
//void ThicknessLir::SQ1off(Lir::Data &){}
void ThicknessLir::SQ0on(Lir::Data &d)
{
	predTick = d.tick;
	predTime = d.time;
	startLong = timeGetTime();
}
void ThicknessLir::SQ1on(Lir::Data &d)
{
	counterTickTime = 0;

	tTime = predTime + (d.time - predTime) / 2;
	tTick = predTick + (d.tick - predTick) / 2;

	int count = (d.tick - tTick) / d.lenZone;
	double delta = (double )(d.time - predTime)/ (d.tick - predTick);

	for(int i = 0; i < count; ++i)
	{
		unsigned t = i * d.lenZone;
		times[i] = tTime + unsigned(delta * t);
		ticks[i] = tTick + t;
	}


	predTick = ticks[count - 1];
	predTime = times[count - 1];

	counterTickTime = count;

	lir.SetThick<ThicknessLir>(this, &ThicknessLir::Tick);	
	
}

void ThicknessLir::SQ0off(Lir::Data &d)
{
	tTime = d.time;
	tTick = d.tick;
	lir.SetThick<Lir>(&lir, &Lir::Noop);	
}
void ThicknessLir::SQ1off(Lir::Data &d)
{
	tTick += (d.tick - tTick) / 2;
	unsigned deltaTime = times[counterTickTime - 1] - times[counterTickTime - 2];
	unsigned t = ticks[counterTickTime - 1];
	tTick += d.lenZone / 4;
	while(t < tTick)
	{
		t += d.lenZone;
		ticks[counterTickTime] = t;
		times[counterTickTime] = times[counterTickTime - 1] + deltaTime;
		++counterTickTime;
	}
	countZones = counterTickTime;	
	//int j = 0;
	//for(unsigned i = 0; i < countZones; ++i)
	//{
	//	unsigned t = times[i];
	//	for(; j < rowData.currentFrames; ++j)
	//	{
	//		if(t < rowData.timeFrames[j])
	//		{
	//			double delta = double(t - rowData.timeFrames[j - 1])/(rowData.timeFrames[j] - rowData.timeFrames[j - 1]);
    //            offsetsDataOfZone[i] = rowData.offsets[j - 1] + (unsigned)(delta * (rowData.offsets[j] - rowData.offsets[j - 1]));
	//			break;
	//		}
	//	}
	//}
	//dprint("stop long %d", timeGetTime() - startLong);
	//ItemData<Thickness> &item = Singleton<ItemData<Thickness>>::Instance();
	//memcpy(item.offsets, offsetsDataOfZone, sizeof(item.offsets));
	//item.currentOffsetZones = counterTickTime;	
	//----------------------------------------------
}
//--------------------------------------------------------------------------------
