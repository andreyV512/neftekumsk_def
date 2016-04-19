#include "stdafx.h"
#include "SendDataAsu.h"
#include "Communication.h"
#include "AppBase.h"
#include "USPCData.h"
#include "ResultData.h"
#include "DebugMess.h"
#include "CountingTube.h"

static const int cross_offs = 0;
static const int long_offs = 2;
static const int thick_offs = 4;
static const int common_offs = 6;

template<class T>struct Offs;
template<>struct Offs<Cross>{static const int value = 0;};
template<>struct Offs<Long>{static const int value = 2;};
template<>struct Offs<Thickness>{static const int value = 4;};

template<class O, class P>struct __status__;
template<class X, class P>struct __status__<BKlass2<X>, P>
{
	typedef BKlass2<X> O;
	void operator()(O *, P *p)
	{
		//p->res &= ~(Asu::brak << Offs<X>::value);
		p->res |= Asu::klass2 << Offs<X>::value;
	}
};
template<class X, class P>struct __status__<BDefect<X>, P>
{
	typedef BDefect<X> O;
	void operator()(O *, P *p)
	{
		//p->res &= ~(Asu::brak << Offs<X>::value);
		p->res |= Asu::brak << Offs<X>::value;
	}
};
template<class P>struct __status__<Undefined, P>
{
	typedef Undefined O;
	void operator()(O *, P *p)
	{
		//p->res = 0;
	}
};
template<class P>struct __status__<DeathZone, P>
{
	typedef DeathZone O;
	void operator()(O *, P *p)
	{
		p->res = 0;
	}
};
template<class P>struct __status__<Nominal, P>
{
	typedef Nominal O;
	void operator()(O *, P *p)
	{
	}
};
template<class P>struct __status__<BNominal<Thickness>, P>
{
	typedef BNominal<Thickness> O;
	void operator()(O *, P *p)
	{
	}
};

template<class O, class P>struct __wapp__
{
	bool operator()(O *, P *p)
	{
		if(TL::IndexOf<ColorTable::items_list, O>::value == p->inp)
		{
			typedef GetItemsList<O>::Result list;
			TL::foreach<list, __status__>()((TL::Factory<list> *)0, p);
			return false;
		}
		return true;
	}
};

struct __conv__
{
	unsigned char inp, res;
};

void ForAsu(unsigned length, unsigned cut0, unsigned cut1, unsigned char *zones, char *inp)
{
	zones[0] = 0;           // ................................................................
	zones[length - 1] = 0;
	for(unsigned i = 1; i < length - 1; ++i)
	{
		//zones[i] = (Asu::ok << 0) | (Asu::ok << 2) | (Asu::ok << 4);
		__conv__ xxxx = {inp[i], 0};
		TL::find<ColorTable::items_list, __wapp__>()((TL::Factory<ColorTable::items_list> *)0, &xxxx);
		zones[i] = xxxx.res;
		//for(int j = 0; j < 3; ++j)
		//{
		//	int t = zones[i] & (Asu::brak << (j * 2));
		//	if((Asu::klass2 << (j * 2)) == t) zones[i] |= Asu::klass2 << 6;
		//	if((Asu::brak << (j * 2)) == t) 
		//	{
		//		zones[i] |= Asu::brak << 6;
		//		break;
		//	}
		//}

	}
}

unsigned ResultTube(unsigned start, unsigned stop, unsigned char *zones)
{
	for(unsigned i = start; i < stop; ++i)
	{
		//if((Asu::klass2 << 6) == (zones[i] & (Asu::brak << 6))) return Asu::klass2;
		if( 0 != (zones[i] & ((Asu::klass2 << 0)|(Asu::klass2 << 2)|(Asu::klass2 << 4))))
			return Asu::klass2;
	}
	return Asu::ok;
}

bool SendDataAsu()
{
	ResultViewerData &resData = Singleton<ResultViewerData>::Instance();
	if(Communication::TransferControlResul3(
		resData.numberTube

		, resData.lengthTube

		, resData.cutting0
		, resData.cutting1

		, resData.klass

		, resData.zonesAsu

		)
		)
	{
		dprint("sent to com-port\n");
		if(strncmp(resData.numberTube, "000", 3) != 0)
		{
			if(resData.counting)
			{
				if(!resData.brak)CountingTube().AddCommon();
				else CountingTube().AddBrak();
				resData.counting = false;
			}
		}
		return true;
	}
	dprint("com-port ERROR++++++++++++++++++++\n");
	return false;
}

void ComputeDataAsu()
{
	ResultViewerData &resData = Singleton<ResultViewerData>::Instance();
	resData.sendData = true;
	resData.brak = false;
	resData.counting = true;
	ThresholdsTable::TItems &thesholds = Singleton<ThresholdsTable>::Instance().items;
	unsigned char (&zones)[65] = resData.zonesAsu;
	ForAsu(
		 resData.currentOffset
		, 0
		, resData.currentOffset
		, zones, resData.commonStatus);

	int cut1 = resData.cutting1 ? resData.cutting1 : resData.currentOffset;
	resData.klass = ResultTube(resData.cutting0,  cut1, zones);
	if(
		resData.lengthTube < (int)thesholds.get<MimimumTubeLength>().value
		)
	{
		resData.klass = Asu::brak;
		resData.brak = true;
	}
/*
	if(0 == cuttingLen && 0 == resData.cutting0 && 0 == resData.cutting1)
	{
			cuttingLen = length;
			result = ResultTube(0,  resData.currentOffset, zones);
	}
	else if(cuttingLen < 0)
	{
		cuttingLen = length - resData.cutting0;
		result = ResultTube(resData.cutting0 + 1, length, zones);		
	}
	else
	{
		result = ResultTube(resData.cutting0 + 1, resData.cutting1 - 1, zones);
	}

	if(
		cuttingLen < (int)thesholds.get<MimimumTubeLength>().value
		)
	{
		result = Asu::brak;
		resData.brak = true;
	}
   //*/ 
}

bool SendAsuBrak()
{	
   ResultViewerData &resData = Singleton<ResultViewerData>::Instance();
   bool b = false;
   if(resData.sendData)
   {
	   resData.klass = Asu::brak;
	   resData.cutting0 = 0;
	   resData.cutting1 = 0;
	   resData.brak = true;
	   b = SendDataAsu();
	   resData.sendData = false;
   }
   return b;
}