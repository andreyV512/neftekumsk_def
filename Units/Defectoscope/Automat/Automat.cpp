#include "stdafx.h"
#include "Automat.h"
#include <MMSystem.h>
#include "App.h"
#include "AppBase.h"
#include "Device1730.h"
#include "LogMessages.h"
#include "LogBuffer.h"
#include "LogMessageToTopLabel.h"
#include "Communication.h"
#include "AnalogBoard.h"
#include "Lir.h"
#include "LirItems.h"
#include "Compute.h"
#include "DebugMess.h"
#include "CommunicationWapper.h"
#include "ResultData.h"
#include "SendDataAsu.h"
#include "SendDataTablo.h"
#include "SolenoidControl.h"
#include "StopAfterCycle.h"
#include "Communication.h"

struct Impl
{
	struct ExceptionExitProc{};
	struct ExceptionStopProc{};
	struct ExceptionTimeOutProc{};
	struct ExceptionContinueProc{};

	//struct ExceptionMissingSignalFromLift{};

	HANDLE hThread;
	static bool block;
	static unsigned &sycle_ts;
	Impl() 
		
	{}
	static Impl &Instance(){static Impl x; return x;};
	void Do();
	static DWORD WINAPI ProcDo(LPVOID)
	{
		Impl::Instance().Do();
		return 0;
	}
	void Init()
	{
		hThread = CreateThread(NULL, 0, ProcDo, NULL, 0, NULL);
	}
	void Suspend()
	{
		SuspendThread(hThread);
	}
	void Resume()
	{
		while(ResumeThread(hThread));
	}

	template<class>struct On{};
	template<class>struct Off{};
	template<class>struct Inv{};
	template<class>struct Proc{};
	template<class>struct Once{};
	template<class T>struct Ex;

#define EX(n)template<>struct Ex<Exception##n##Proc>\
	{\
	HANDLE &handle;\
	Ex() : handle(App::Programm##n##Event){}\
	};

	EX(Exit)
	EX(Stop)
	EX(Continue)

#undef EX

	 template<class list>struct ArrEvents
	 {
		 template<class O, class P>struct loc
		 {
			 void operator()(O *, P *p)
			 {
				 p[TL::IndexOf<list, O>::value] = Ex<O>().handle;
			 }
		 };
		 template<class O, class P>struct ev
		 {
			 void operator()(O *, P *p)
			 {
				if(TL::IndexOf<list, O>::value == *p) throw O();
			 }
		 };
		 template<class P>struct ev<ExceptionContinueProc, P>
		 {
			 void operator()(ExceptionContinueProc *, P *){}
		 };
		 HANDLE h[TL::Length<list>::value];
		 ArrEvents()
		 {
			 TL::foreach<list, loc>()((TL::Factory<list> *)0, h);
		 }

		 void Throw(unsigned t)
		 {
			 TL::foreach<list, ev>()((TL::Factory<list> *)0, &t);
			 return;
		 }

	 };

	template<class List, template<class>class T>struct Filt;
	template<class Head, class Tail, template<class>class T>struct Filt<Tlst<Head, Tail>, T>
	{
		typedef typename Filt<Tail, T>::Result Result;
	};
	template<class Head, class Tail, template<class>class T>struct Filt<Tlst<T<Head>, Tail>, T>
	{
		typedef Tlst<Head, typename Filt<Tail, T>::Result> Result;
	};
	template<template<class>class T>struct Filt<NullType, T>
	{
		typedef NullType Result;
	};

	template<class O, class P>struct __bits_0__
	{
		void operator()(O *o, P *p)
		{
			*p |= o->value;
		}
	};
	template<class O, class P>struct __bits_1__
	{
		void operator()(O *o, P *p)
		{
			((unsigned short *)p)[1] |= o->value;
		}
	};

	template<class List, class TList>struct __filtr__;
	template<class Head, class Tail, class TList>struct __filtr__<Tlst<Head, Tail>, TList>
	{
		typedef typename TL::_if<
			TL::TypeInList<TList, Head>::value
			, Tlst<Head, typename __filtr__<Tail, TList>::Result>
			, typename __filtr__<Tail, TList>::Result
		>::Result Result;
	};

	template<class TList>struct __filtr__<NullType, TList>
	{
		typedef NullType Result;
	};

	template<class List, template<class, class>class b>struct __sel_bits__
	{
		template<class O, class P>void operator()(O *o, P *p)
		{
			TL::foreach<List, b>()(o, p);
		}
	};
	template<template<class, class>class b>struct __sel_bits__<NullType, b>
	{
		template<class O, class P>void operator()(O *o, P *p)
		{
		}
	};
	
	template<class List>struct SelectBits
	{
		void operator()(unsigned &bits)
		{
			bits = 0;
			__sel_bits__<typename __filtr__<List, InputsTable<0>::items_list>::Result, __bits_0__>()
				(&Singleton<InputsTable<0> >::Instance().items, &bits);

			__sel_bits__<typename __filtr__<List, InputsTable<1>::items_list>::Result, __bits_1__>()
				(&Singleton<InputsTable<1> >::Instance().items, &bits);
		}
	};
	template<>struct SelectBits<NullType>
	{
		void operator()(unsigned &bits){}
	};

	/// \brief проверка готовности модулей дефектоскопа
	struct ExceptionMissingSignalFromLift
	{
		static void Do(unsigned input_bits)
		{
			unsigned msk = 0;
			SelectBits<TL::MkTlst<WCROSS, WTHICK, WLINE>::Result>()(msk);
			if(msk != (input_bits & msk)) throw	ExceptionMissingSignalFromLift();
		}
	};


	template<class List>struct BitsOut
	{
		void operator()(unsigned &bits)
		{
			bits = 0;
			__sel_bits__<typename __filtr__<List, OutputsTable<0>::items_list>::Result, __bits_0__>()
				(&Singleton<OutputsTable<0> >::Instance().items, &bits);

			__sel_bits__<typename __filtr__<List, OutputsTable<1>::items_list>::Result, __bits_1__>()
				(&Singleton<OutputsTable<1> >::Instance().items, &bits);
		}
	};
	template<>struct BitsOut<NullType>
	{
		void operator()(unsigned &bits)
		{
		}
	};

	template<class O, class P>struct __default_do__
	{
		void operator()(O *, P *bits)
		{
			O::Do(*bits);
		}
	};

	template<class List>struct DefaultDo
	{
		void operator()(unsigned bits)
		{
			TL::foreach<List, __default_do__>()((TL::Factory<List> *)0, &bits);
		}
	};
	template<>struct DefaultDo<NullType>
	{
		void operator()(unsigned bits){}
	};

	template<class O, class P>struct __once_do__
	{
		void operator()(O *, P *)
		{
			O::Do();
		}
	};

	template<class List>struct OnceDo
	{
		void operator()()
		{
			TL::foreach<List, __once_do__>()((TL::Factory<List> *)0, (int *)0);
		}
	};
	template<>struct OnceDo<NullType>
	{
		void operator()(){}
	};

	

	template<class List>struct OR_Bits
	{
		unsigned operator()(unsigned delay = (unsigned)-1)
		{
			if((unsigned)-1 != delay) delay += GetTickCount();
			unsigned bitOn = 0, bitOff = 0, bitInv = 0;
			SelectBits<typename Filt<List, On>::Result>()(bitOn);
			SelectBits<typename Filt<List, Off>::Result>()(bitOff);
			SelectBits<typename Filt<List, Inv>::Result>()(bitInv);

			typedef TL::Append<typename Filt<List, Ex>::Result, ExceptionExitProc>::Result exeption_list;
			ArrEvents<exeption_list> arrEvents;
			
			while(true)
			{
				unsigned ev = WaitForMultipleObjects(dimention_of(arrEvents.h), arrEvents.h, FALSE, 5);
				unsigned res = device1730_0.Read();
				((unsigned short *)&res)[1] = device1730_1.Read();
				if(WAIT_TIMEOUT == ev)
				{
					if(bitOn || bitOff)
					{
						unsigned t = res ^ bitInv;
						if((t & bitOn) || (bitOff & (t ^ bitOff))) 
						{
								OnceDo<typename Filt<List, Once>::Result>()();
								return res;
						}
					}
					if((((unsigned short *)&res)[1]) & sycle_ts)
					{
						dprint("ExceptionStopProc  %x\n", sycle_ts);
						throw ExceptionStopProc();
					}
					DefaultDo<typename Filt<List, Proc>::Result>()(res);
					if(GetTickCount() >= delay) throw ExceptionTimeOutProc();
				}
				else
				{
					arrEvents.Throw(ev - WAIT_OBJECT_0);
				}
			}
		}
	};

	

	template<class List>struct AND_Bits
	{
		unsigned operator()(unsigned delay = (unsigned)-1)
		{
			if((unsigned)-1 != delay) delay += GetTickCount();
			unsigned bitOn = 0, bitOff = 0, bitInv = 0;
			SelectBits<typename Filt<List, On>::Result>()(bitOn);
			SelectBits<typename Filt<List, Off>::Result>()(bitOff);
			SelectBits<typename Filt<List, Inv>::Result>()(bitInv);

			typedef TL::Append<typename Filt<List, Ex>::Result, ExceptionExitProc>::Result exeption_list;
			ArrEvents<exeption_list> arrEvents;

			while(true)
			{
				unsigned ev = WaitForMultipleObjects(dimention_of(arrEvents.h), arrEvents.h, FALSE, 20);
				unsigned res = 0;
				((unsigned short *)&res)[0] = device1730_0.Read();
				((unsigned short *)&res)[1] = device1730_1.Read();
				if(WAIT_TIMEOUT == ev)
				{
					if(bitOn || bitOff)
					{						
						unsigned t = res ^ bitInv;
						if(bitOn == (t & (bitOn | bitOff))) 
						{
								OnceDo<typename Filt<List, Once>::Result>()();
								return res;
						}
					}
					if(Impl::block && !(res & (sycle_ts << 16)))
					{
						throw ExceptionStopProc();
					}
					DefaultDo<typename Filt<List, Proc>::Result>()(res);
					if(GetTickCount() >= delay) throw ExceptionTimeOutProc();
				}
				else
				{
					arrEvents.Throw(ev - WAIT_OBJECT_0);
					return res;
				}
			}
		}
	};
	template<class List>struct OUT_Bits
	{
		void operator()()
		{
			unsigned bitOn, bitOff;
			bitOn = bitOff = 0;
			BitsOut<typename Filt<List, On>::Result>()(bitOn);
			BitsOut<typename Filt<List, Off>::Result>()(bitOff);

			unsigned res = device1730_0.ReadOutput();
			((unsigned short *)&res)[1] = device1730_1.ReadOutput();

            res &= ~bitOff;
			res |= bitOn;

			device1730_0.Write(((unsigned short *)&res)[0]);
			device1730_1.Write(((unsigned short *)&res)[1]);	
		}
	};
	template<class List>struct SET_Bits
	{
		void operator()()
		{
			unsigned res =0;
			BitsOut<typename Filt<List, On>::Result>()(res);

			device1730_0.Write(((unsigned short *)&res)[0]);
			//device1730_1.Write(((unsigned short *)&res)[1]);	
		}
	};
};

#define AND_BITS(...) AND_Bits<TL::MkTlst<__VA_ARGS__>::Result>()
#define OR_BITS(...) OR_Bits<TL::MkTlst<__VA_ARGS__>::Result>()

#define OUT_BITS(...) OUT_Bits<TL::MkTlst<__VA_ARGS__>::Result>()()
#define SET_BITS(...) SET_Bits<TL::MkTlst<__VA_ARGS__>::Result>()()
namespace
{
	 bool &onTheJobLong = Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Long>>().value;
	 bool &onTheJobThickness = Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Thickness>>().value;
	 Lir &lir = Singleton<Lir>::Instance();
	 AnalogBoard &analogBoard = Singleton<AnalogBoard>::Instance();
}

template<class T>struct __cross_type__;
template<>struct __cross_type__<SpeedRL>{typedef RL Result;};
template<>struct __cross_type__<SpeedRM>{typedef RM Result;};
template<>struct __cross_type__<SpeedRH>{typedef RH Result;};

template<class O, class P>struct __cross_speed__
{
	typedef typename __cross_type__<O>::Result T;
	void operator()(O &o)
	{
		if(o.value)
		{
			Impl::OUT_Bits<TL::MkTlst<Impl::On<T>>::Result>()();
		}
		else
		{
		  Impl::OUT_Bits<TL::MkTlst<Impl::Off<STF>>::Result>()();
		}
	}
};

void Automat::RotationOn()
{
	//if(Singleton<SpeedTable>::Instance().items.get<SpeedRL>().value)
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::On<RL>>::Result>()();
	//}
	//else
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::Off<RL>>::Result>()();
	//}
	//if(Singleton<SpeedTable>::Instance().items.get<SpeedRM>().value)
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::On<RM>>::Result>()();
	//}
	//else
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::Off<RM>>::Result>()();
	//}
	//if(Singleton<SpeedTable>::Instance().items.get<SpeedRH>().value)
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::On<RH>>::Result>()();
	//}
	//else
	//{
	//	Impl::OUT_Bits<TL::MkTlst<Impl::Off<RH>>::Result>()();
	//}
	TL::foreach<TL::MkTlst<SpeedRL, SpeedRM, SpeedRH>::Result, __cross_speed__>()(Singleton<SpeedTable>::Instance().items);
	Impl::OUT_Bits<TL::MkTlst<Impl::On<POWPCH>, Impl::On<STF>>::Result>()();
}
void Automat::RotationOff()
{
	Impl::OUT_Bits<TL::MkTlst<Impl::On<POWPCH>, Impl::Off<STF>>::Result>()();
}

template<class T>struct TestOutput;
#define TEST_OUTPUT(n)template<>struct TestOutput<n>\
{\
	bool operator()()\
	{\
		return 0 !=(Singleton< OutputsTable<1>>::Instance().items.get<n>().value & device1730_1.ReadOutput());\
	}\
};
TEST_OUTPUT(RCROSS)
TEST_OUTPUT(RLINE)
TEST_OUTPUT(RTHICK)
#undef TEST_OUTPUT

template<class T>struct OutInputType;

template<>struct OutInputType<RCROSS>{typedef WCROSS Result;};
template<>struct OutInputType<RLINE>{typedef WLINE Result;};
template<>struct OutInputType<RTHICK>{typedef WTHICK Result;};

template<class T>struct PositionModule
{
	void operator()(bool workPosition)
	{		
		bool testOutput = TestOutput<T>()();
		if(workPosition)
		{
			if(!testOutput)
			{	
				//OUT_BITS(On<T>);
				Impl::OUT_Bits<TL::MkTlst<Impl::On<T>>::Result>()();
				Sleep(3000);
				//AND_BITS(On<typename OutInputType<T>::Result>, Ex<ExceptionStopProc>)();
				Impl::AND_Bits<TL::MkTlst<Impl::On<typename OutInputType<T>::Result>, Impl::Ex<Impl::ExceptionStopProc>>::Result>()();
			}
		}
		else
		{
			if(testOutput)
			{
				//OUT_BITS(Off<T>);
				Impl::OUT_Bits<TL::MkTlst<Impl::Off<T>>::Result>()();
				Sleep(3000);
				//AND_BITS(Off<typename OutInputType<T>::Result>, Ex<ExceptionStopProc>)();
				Impl::AND_Bits<TL::MkTlst<Impl::Off<typename OutInputType<T>::Result>, Impl::Ex<Impl::ExceptionStopProc>>::Result>()();
			}
		}
	}
};

void Impl::Do()
{
	Log::Mess<LogMess::ProgramOpen>(0);
	LogMessageToTopLabel logMessageToTopLabel;
#ifndef DEBUG_ITEMS
	device1730_0.Write(0);
#endif
	try
	{
		while(true)
		{
#ifdef DEBUG_ITEMS
			WaitForSingleObject(App::WaitThicknessEvent, 5 * 60 * 60 * 1000);
			Singleton<Compute>::Instance().Recalculation();
			continue;
#endif
			try
			{
				App::measurementOfRunning = false;	
				Impl::block = false;
				analogBoard.Stop();
				device1730_0.Write(0);
				OUT_BITS(Off<START>);			
				SET_BITS(On<POWPCH>);
				Sleep(3000);
				AND_BITS(Ex<ExceptionContinueProc>, Proc<ACh13>, Proc<ACh14>)();
				if(ACh13::Do(0) || ACh14::Do(0))
				{
					ResetEvent(App::ProgrammContinueEvent);
					continue;
				}

				AND_BITS(On<TPP_TS>, On<CYCLE_TS>, Ex<ExceptionStopProc>)();

				Log::Mess<LogMess::QueryNumberTube>();
				if(!Communication::QueryNumberTube2(
					Singleton<ResultViewerData>::Instance().numberTube
					))
				{
					dprint("Error Number TUBE\n");
					Log::Mess<LogMess::ErrorNumberTube>();
					throw ExceptionTimeOutProc();
				}

				if(!Singleton<Communication::FromASU>::Instance().tubeOk)
				{
					Log::Mess<LogMess::ExitBrak>();					
					PositionModule<RCROSS>()(false);
					PositionModule<RLINE>()(false);
					PositionModule<RTHICK>()(false);
					OUT_BITS(On<START>); //старт цикла
					AND_BITS(On<BASE_TS>, Proc<ExceptionMissingSignalFromLift>, Ex<ExceptionStopProc>)();//ожидание наезда на датчик базы, проверка положений модулей
					AND_BITS(Off<BASE_TS>, Proc<ExceptionMissingSignalFromLift>, Ex<ExceptionStopProc>)();//ожидание съезда с датчика базы, проверка положений модулей
					OUT_BITS(Off<START>);//стоп цикла
					continue;
				}

				//dprint("number tube %s     \n", Singleton<ResultViewerData>::Instance().numberTube);

#define NEW_TEST_POSITION_UNITS
#ifdef NEW_TEST_POSITION_UNITS
				Log::Mess<LogMess::PositionCrossUnit>();
				PositionModule<RCROSS>()(true);
				
				Log::Mess<LogMess::PositionLongUnit>();
				PositionModule<RLINE>()(onTheJobLong);
				
				Log::Mess<LogMess::PositionThicknessUnit>();
				PositionModule<RTHICK>()(onTheJobThickness);

				AND_BITS(On<WCROSS>, On<WTHICK>, On<WLINE>, Ex<ExceptionStopProc>)();
#else
				Log::Mess<LogMess::PositionCrossUnit>();
				OUT_BITS(On<RCROSS>);//готовность пореречника
				
				Log::Mess<LogMess::PositionLongUnit>();
				if(onTheJobLong)
				{
					OUT_BITS(On<RLINE>);//готовность продольника
				}
				else
				{
					OUT_BITS(Off<RLINE>);//
				}
				
				Log::Mess<LogMess::PositionThicknessUnit>();
				if(onTheJobThickness)
				{
					OUT_BITS(On<RTHICK>);//готовность толщиномера
				}
				else
				{
					OUT_BITS(Off<RTHICK>);//г
				}

				Sleep(3000);
				dprint("wait for CROSS position\n");
				Log::Mess<LogMess::WaitPositionCrossUnit>();
				AND_BITS(On<WCROSS>, Ex<ExceptionStopProc>)(360000);
				Sleep(1000);
				dprint("wait for THICKNESS position\n");
				Log::Mess<LogMess::WaitPositionThicknessUnit>();
				AND_BITS(On<WTHICK>, Ex<ExceptionStopProc>)(360000);
				Sleep(1000);
				dprint("wait for LONG position\n");
				Log::Mess<LogMess::WaitPositionLongUnit>();
				AND_BITS(On<WLINE>, Ex<ExceptionStopProc>)(360000);		
				Sleep(1000);
				AND_BITS(On<WCROSS>, On<WTHICK>, On<WLINE>, Ex<ExceptionStopProc>)(360000);
#endif

				App::measurementOfRunning = true;
				Log::Mess<LogMess::StartSycle>();


				AND_BITS(On<TPP_TS>, On<CYCLE_TS>, Ex<ExceptionStopProc>)();//ожидание цикла
				OUT_BITS(Off<RESULT>);

				dprint("Start Cycle  %x\n", sycle_ts);

				if(onTheJobLong)
				{
					automat.RotationOn();
					OUT_BITS(On<POWSU>);  
					Sleep(1000);
					AND_BITS(On<WLINE>, On<PCHA>, Off<PCHRUN>, Ex<ExceptionStopProc>);
				}				

				if(onTheJobThickness)
				{
					Sleep(1000);
					OUT_BITS(On<CYCLE>);
					Sleep(1000);
					Log::Mess<LogMess::WaitReadyFromThickness>();
					AND_BITS(On<WTHICK>, On<CONTROL>, Ex<ExceptionStopProc>)();
				}				

				dprint("Wait tube on Position\n");
				Log::Mess<LogMess::WaitTubeOnPosition>();
				Sleep(500);
				AND_BITS(On<WTHICK>, On<WCROSS>, On<WLINE>, On<TPP_TS>, On<CYCLE_TS>, Ex<ExceptionStopProc>)();
				Singleton<Compute>::Instance().Clear();
				Impl::block = true;
				dprint("Wait NumberTube\n");
/*				
				Log::Mess<LogMess::QueryNumberTube>();
				if(!Communication::QueryNumberTube2(
					Singleton<ResultViewerData>::Instance().numberTube
					))
				{
					dprint("Error Number TUBE\n");
					Log::Mess<LogMess::ErrorNumberTube>();
					throw ExceptionTimeOutProc();
				}

				if(!Singleton<FromASU>::Instance().tubeOk)
				{
					Log::Mess<LogMess::ExitBrak>();					
					PositionModule<RCROSS>()(false);
					PositionModule<RLINE>()(false);
					PositionModule<RTHICK>()(false);
					OUT_BITS(On<START>); //старт цикла
					AND_BITS(On<BASE_TS>, Proc<ExceptionMissingSignalFromLift>)();//ожидание наезда на датчик базы, проверка положений модулей
					AND_BITS(Off<BASE_TS>, Proc<ExceptionMissingSignalFromLift>)();//ожидание съезда с датчика базы, проверка положений модулей
					OUT_BITS(Off<START>);//стоп цикла
					continue;
				}

				dprint("number tube %s     \n", Singleton<ResultViewerData>::Instance().numberTube);
				*/
				Log::Mess<LogMess::SetSignalStart>();
				OUT_BITS(On<START>); //старт цикла

				lir.Clear();
				AND_BITS(On<SQfirst>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(360000);
				//-------------------------------------------------------------------------------------------------------------

				if(onTheJobLong) OUT_BITS(On<POWSU>);

				
				//Singleton<Compute>::Instance().Clear();

				analogBoard.Start();

				AND_BITS(On<SQcrossIN>, Proc<Lir>, Once<CrossSQ0on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
				dprint("AND_BITS(On<SQcrossIN>, Proc<Lir>, Once<CrossSQ0on>)(10000)\n");
				Log::Mess<LogMess::InCrossModule>();
				AND_BITS(On<SQcrossOUT>, Proc<Lir>, Once<CrossSQ1on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
				//Log::Mess<LogMess::InCrossModule>();
				lir.Start0();
				if(onTheJobThickness)
				{
					AND_BITS(On<SQthickIN>, Proc<Lir>, Once<ThicknessSQ0on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
					Log::Mess<LogMess::InThickModule>();
					AND_BITS(On<SQthickOUT>, Proc<Lir>, Once<ThicknessSQ1on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
					//Log::Mess<LogMess::InThickModule>();
				}

				if(onTheJobLong)
				{
					AND_BITS(On<SQlongIN>, Proc<Lir>,  Once<LongSQ0on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
					Log::Mess<LogMess::InLongModule>();
					AND_BITS(On<SQlongOUT>, Proc<Lir>,  Once<LongSQ1on>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
					//Log::Mess<LogMess::InLongModule>();
				}

				AND_BITS(On<BASE_TS>, Proc<Lir>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(360000);	
				lir.Stop0();

				AND_BITS(Off<SQfirst>, Proc<Lir>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(360000);
				lir.SetTick1();

				AND_BITS(Off<SQcrossIN>, Proc<Lir>,  Once<CrossSQ0off>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
				dprint("AND_BITS(Off<SQcrossIN>, Proc<Lir>,  Once<CrossSQ0off>)(60000);\n");
				Log::Mess<LogMess::OutCrossModule>();
				AND_BITS(Off<SQcrossOUT>, Proc<Lir>,  Once<CrossSQ1off>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);
				lir.Start1();
				if(onTheJobThickness)
				{
					AND_BITS(Off<SQthickIN>, Proc<Lir>,  Once<ThicknessSQ0off>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(30000);
					Log::Mess<LogMess::OutThickModule>();
					AND_BITS(Off<SQthickOUT>, Proc<Lir>
						, Once<ThicknessSQ1off>
						, Once<TcpClientSetStrobe>
						, Ex<ExceptionStopProc>
						, Proc<ExceptionMissingSignalFromLift>
						)(10000);
				}

				if(onTheJobLong)
				{
					AND_BITS(Off<SQlongIN>, Proc<Lir>,  Once<LongSQ0off>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(30000);
					Log::Mess<LogMess::OutLongModule>();
					AND_BITS(Off<SQlongOUT>, Proc<Lir>,  Once<LongSQ1off>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(10000);

					OUT_BITS(Off<STF>, Off<RH>, Off<RM>, Off<RL>);
				}

				analogBoard.Stop();
				OUT_BITS(Off<CYCLE>, Off<POWSU>);				
				
				AND_BITS(Off<BASE_TS>, Ex<ExceptionStopProc>, Proc<ExceptionMissingSignalFromLift>)(360000);	
				lir.Stop1();
				lir.TestLir();

				if(onTheJobThickness)
				{
					Log::Mess<LogMess::SendStrobes>();
					WaitForSingleObject(App::WaitThicknessEvent, INFINITE);
					ResetEvent(App::WaitThicknessEvent);
				}

				Singleton<Compute>::Instance().Recalculation();

				ComputeDataAsu();

				ComputeDataTablo();

				StopAfterCycle();

				OUT_BITS(On<RESULT>);
				SendDataAsu();
				SendDataTablo();

				AND_BITS(Off<TPP_TS>);
				OUT_BITS(Off<START>);
			}
			catch(ExceptionStopProc)
			{
				ResetEvent(App::ProgrammContinueEvent);
				Log::Mess<LogMess::InfoUserStop>();
			}
			catch(ExceptionTimeOutProc)
			{
				ResetEvent(App::ProgrammContinueEvent);
				Log::Mess<LogMess::TimeoutPipe>();
			}
			catch(ExceptionMissingSignalFromLift)
			{
				ResetEvent(App::ProgrammContinueEvent);
				Log::Mess<LogMess::NonOperatingModule>();
			}
		}
	}
	catch(ExceptionExitProc)
	{
	}
	CloseHandle(hThread);
	Log::Mess<LogMess::ProgramClosed>(0);
	device1730_0.Write(0);
	analogBoard.Stop();
}

unsigned &Impl::sycle_ts = Singleton<InputsTable<1>>::Instance().items.get<CYCLE_TS>().value;
bool Impl::block ;

 Automat::Automat()
{}

void Automat::Init()
{
	Impl::Instance().Init();
}

#undef AND_BITS
#undef OR_BITS