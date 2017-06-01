#pragma once
class Lir
{
public:
	struct Data
	{
		unsigned tick;
		unsigned time;
		unsigned lenZone;
	};
private:
	void *cnt0_, *cnt1_;
	unsigned tmpTick, tick;
public:
	unsigned (Lir::*ptrTick)();
private:
	struct Obj{};
	typedef void(Obj::*TPtr)(Data &);
	TPtr ptrCross, ptrLong, ptrThick;
	Obj *oCross, *oLong, *oThick;
public:
	int startLir0, startLir1, stopLir0, stopLir1;
	void Noop(Data &){}
public:
	int &zone0, &zone1;
	int lenZone;
	Lir();
	bool Init(int );
	void Clear();
	unsigned Tick0();
	unsigned Tick1();
	static void Do(unsigned);
	void __Do__();
	void SetTick1();
	template<class T>void SetCross(T *t, void(T::*ptr)(Data &))
	{
		oCross = (Obj *)t;
		ptrCross = (TPtr)ptr;
	}
	template<class T>void SetLong(T *t, void(T::*ptr)(Data &))
	{
		oLong = (Obj *)t;
		ptrLong = (TPtr)ptr;
	}
	template<class T>void SetThick(T *t, void(T::*ptr)(Data &))
	{
		oThick = (Obj *)t;
		ptrThick = (TPtr)ptr;
	}
	void Start0();
	void Start1();
	void Stop0();
	void Stop1();
	void TestLir();
};