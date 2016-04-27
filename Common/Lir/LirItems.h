#pragma once

#include "Lir.h"
#include "App.h"

template<class T, void(T::*ptr)(Lir::Data &)>struct ItemsDo
{
	static void Do()
	{
		T &t = Singleton<T>::Instance();
		Lir &lir = Singleton<Lir>::Instance();
		Lir::Data d = {(lir.*lir.ptrTick)(), timeGetTime(), lir.lenZone};
		(t.*ptr)(d);
	}
};

struct CommonLir
{
	unsigned firstDeathZoneSamples;
	unsigned lastDeathZoneSamples;
	unsigned predTick, predTime;
	unsigned tTick, tTime;
	unsigned counterTickTime, countZones;
	unsigned times[App::zonesCount + 2];
	unsigned ticks[App::zonesCount + 2];
	unsigned offsetsDataOfZone[App::zonesCount + 2];
	void Tick(Lir::Data &);
};

struct LongLir: CommonLir
{	
	void SQ0on(Lir::Data &);
	void SQ1on(Lir::Data &);
	void SQ0off(Lir::Data &);
	void SQ1off(Lir::Data &);
};

struct LongSQ0on: ItemsDo<LongLir, &LongLir::SQ0on>{};
struct LongSQ1on: ItemsDo<LongLir, &LongLir::SQ1on>{};
struct LongSQ0off: ItemsDo<LongLir, &LongLir::SQ0off>{};
struct LongSQ1off: ItemsDo<LongLir, &LongLir::SQ1off>{};

struct CrossLir: CommonLir
{	
	unsigned offsetsDataOfZone2[App::zonesCount + 2];
	void SQ0on(Lir::Data &);
	void SQ1on(Lir::Data &);
	void SQ0off(Lir::Data &);
	void SQ1off(Lir::Data &);
	void CorrectionOffset();
};

struct CrossSQ0on:  ItemsDo<CrossLir, &CrossLir::SQ0on>{};
struct CrossSQ1on:  ItemsDo<CrossLir, &CrossLir::SQ1on>{};
struct CrossSQ0off: ItemsDo<CrossLir, &CrossLir::SQ0off>{};
struct CrossSQ1off: ItemsDo<CrossLir, &CrossLir::SQ1off>{};

struct ThicknessLir: CommonLir
{	
	void SQ0on(Lir::Data &);
	void SQ1on(Lir::Data &);
	void SQ0off(Lir::Data &);
	void SQ1off(Lir::Data &);
};

struct ThicknessSQ0on:  ItemsDo<ThicknessLir, &ThicknessLir::SQ0on>{};
struct ThicknessSQ1on:  ItemsDo<ThicknessLir, &ThicknessLir::SQ1on>{};
struct ThicknessSQ0off: ItemsDo<ThicknessLir, &ThicknessLir::SQ0off>{};
struct ThicknessSQ1off: ItemsDo<ThicknessLir, &ThicknessLir::SQ1off>{};

template<class T>struct ABoard;

template<>struct ABoard<Cross>
{
	typedef CrossLir Type;
};
template<>struct ABoard<Long>
{
	typedef LongLir Type;
};
template<>struct ABoard<ThicknessLir>
{
	typedef ThicknessLir Type;
};

