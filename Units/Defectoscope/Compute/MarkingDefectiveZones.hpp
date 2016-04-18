#pragma once
#include "AppBase.h"
#include "typelist.hpp"

class MarkingDefectiveZones
{
	template<class T>struct IsBrak
	{
		static const bool value = false;
	};

	template<class _0, class _1, class _2, class _3>struct IsBrak<Clr<BDefect<_0>, _1, _2, _3>>
	{
		static const bool value = true;
	};

	struct __test_data__
	{
		char status;
		bool brak;
	};

	template<class O, class P>struct __test__
	{
		bool operator()(O *, P *p)
		{
			if(TL::IndexOf<ColorTable::items_list, O>::value == p->status)
			{
				p->brak = IsBrak<O>::value;
				return false;
			}
			return true;
		}
	};
public:
	static bool Do(char status)
	{
		__test_data__ data = {status, false};
		TL::find<ColorTable::items_list, __test__>()((TL::Factory<ColorTable::items_list> *)0, &data);
		return data.brak;
	}
};