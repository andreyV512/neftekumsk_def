#include "stdafx.h"
#include "Compute.h"
#include "AnalogBoard.h"
#include "Config.h"
#include "AppBase.h"
#include "DebugMess.h"
namespace
{
	template<class List, class T>struct __items__;
	template<class Head, class Tail, class T>struct __items__<Tlst<Head, Tail>, T>
	{
		typedef typename __items__<Tail, T>::Result Result;
	};
	template<class Tail, template<class, int>class W, int N, class T>struct __items__<Tlst<W<T, N>, Tail>, T>
	{
		typedef Tlst<W<T, N>, typename __items__<Tail, T>::Result> Result;
	};
	template<class T>struct __items__<NullType, T>
	{
		typedef NullType Result;
	};

	typedef TL::MultyListToList<TL::MkTlst<
		__items__<ASignalTable::items_list, Cross>::Result
		, __items__<ASignalTable::items_list, Long>::Result
	>::Result>::Result __analog_number_port__list__;

	typedef TL::TypeToTypeLst<__analog_number_port__list__, Gain>::Result __analog_gain__list__;

	template<class List>struct __data__
	{
		typedef List list;
	};

	template<class O, class P>struct __init__
	{
		void operator()(O *o, P *p)
		{
			((int *)p)[TL::IndexOf<P::list, O>::value] = o->value;
			//dprint("port num %d\n", o->value);
		}
	};
}

int AnalogBoard::SetupParams()
{
	static const int count_channels = TL::Length<__analog_number_port__list__>::value;
	int f_channels[count_channels];
	int f_ch_ranges[count_channels];

	TL::foreach<__analog_number_port__list__, __init__>()(&Singleton<ASignalTable>::Instance().items, (__data__<__analog_number_port__list__> *)f_channels);
	TL::foreach<__analog_gain__list__, __init__>()(&Singleton<GainSignalTable>::Instance().items, (__data__<__analog_gain__list__> *)f_ch_ranges);
	//int f_channels[] = {
	//	Singleton<ADCInputsParametersTable>::Instance().items.get<ReferenceSignal>().value
	//	, Singleton<ADCInputsParametersTable>::Instance().items.get<InputSignal>().value
	//};
	//int f_ch_ranges[] = {
	//	Singleton<SolenoidParametersTable>::Instance().items.get<RangeReferenceSignal>().value
	//	, Singleton<SolenoidParametersTable>::Instance().items.get<InputRangeSignal>().value
	//    };
	//for(int i = 0; i < dimention_of(f_channels); ++i)
	//{
	//	dprint("%d  cross ch %d\n", i, f_channels[i]);
	//}
	int frequency = 10000 * count_channels;
	return InitChannel(
		f_channels
		, f_ch_ranges
		, frequency
		, count_channels * frequency / 10
		);
}

