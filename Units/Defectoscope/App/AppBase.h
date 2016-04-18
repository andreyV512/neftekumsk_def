#pragma once
#include "tables.hpp"
#include "TablesDefine.h"
#include "App.h"
#include "DigitalBoard.h"
//-------------------------------------------------------------------------------------------
void TrimTypeList(wchar_t *, wchar_t *);
//-------------------------------------------------------------------------------------------
DEFINE_PARAM(CurrentID, int, 1)

struct CurrentParametersTable
{
	typedef TL::MkTlst<
		CurrentID
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"CurrentParametersTable";}
};
//------------------------------------------------------------------------------------------
template<class>struct BKlass2;
template<class>struct BDefect;

template<class>struct BNominal;

DEFINE_PARAM_WAPPER(BKlass2, Long,       double, 20)
DEFINE_PARAM_WAPPER(BDefect, Long,       double, 30)
DEFINE_PARAM_WAPPER(BKlass2, Cross     , double, 40)
DEFINE_PARAM_WAPPER(BDefect, Cross     , double, 60)

DEFINE_PARAM_WAPPER(BKlass2  , Thickness, double, 4.8)
DEFINE_PARAM_WAPPER(BDefect  , Thickness, double, 5.2)
DEFINE_PARAM_WAPPER(BNominal, Thickness, double, 6.0)

DEFINE_PARAM(MimimumTubeLength, unsigned, 30)

struct ThresholdsTable
{
	typedef TL::MkTlst<
		BKlass2<Long>
		, BDefect<Long>
		, BKlass2<Cross>
		, BDefect<Cross>
		, BKlass2  <Thickness>
		, BDefect  <Thickness>
	    , BNominal<Thickness>
		, MimimumTubeLength
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ThresholdsTable";}
};

//----------------------------------------------------------------------------------------
DEFINE_PARAM(CommunicationRemoveUnit, int, 0)
DEFINE_PARAM(CounterTubesStored, int, 0)

struct DifferentOptionsTable
{
	typedef TL::MkTlst<
		CommunicationRemoveUnit
		, CounterTubesStored
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"DifferentOptionsTable";}
};
DEFINE_PARAM(OffsetAxesX, int, 100)
DEFINE_PARAM(FrameWidth, int, 400)
DEFINE_PARAM(MaxAxesY, double, 8191)
DEFINE_PARAM(MinAxesY, double, -8192)
struct GraphicSignalOptionsTable
{
	typedef TL::MkTlst<
		OffsetAxesX
		, FrameWidth
		, MaxAxesY
		, MinAxesY
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"GraphicSignalOptionsTable";}
};
struct PointsOptionsTable
{
	typedef TL::MkTlst<
		MaxAxesY
		, MinAxesY
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"PointsOptionsTable";}
};
//----------------------------------------------------------------------------------
template<class _0=NullType, class _1=NullType, class _2=NullType, class _3=NullType>struct Clr;

template<class T>struct GetItemsList;

template<template<class, class, class, class>class W, class _0, class _1, class _2, class _3>struct	GetItemsList<W<_0, _1, _2, _3>>
{
	typedef typename TL::MkTlst<_0, _1, _2, _3>::Result Result;
};

struct Undefined{};
struct Nominal{};
struct DeathZone{typedef NullType items_list;};

DEFINE_WAPPER(Clr<Undefined>, int, 0xff555555)
DEFINE_WAPPER(Clr<Nominal  >, int, 0xff00ff00)
DEFINE_WAPPER(Clr<DeathZone>, int, 0xff333333) 

DEFINE_WAPPER(Clr<BKlass2<Long>      >, int, 0xffffff00)
DEFINE_WAPPER(Clr<BKlass2<Thickness>  >, int, 0xffffff00)
DEFINE_WAPPER(Clr<BDefect<Thickness>  >, int, 0xffff0000)
DEFINE_WAPPER(Clr<BDefect<Long>      >, int, 0xffff0000)
DEFINE_WAPPER(Clr<BKlass2<Cross>     >, int, 0xffffff00)
DEFINE_WAPPER(Clr<BDefect<Cross>     >, int, 0xffff0000)

#define	JOIN2(a, b) a##,##b
#define	JOIN3(a, b, c) a##,##b##,##c
#define	JOIN4(a, b, c, d) a##,##b##,##c,##d

DEFINE_WAPPER(JOIN2(Clr<BDefect<Thickness>, BKlass2<Thickness>>											), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Cross>   , BKlass2<Thickness>>											), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Cross>   , BDefect<Thickness>>											), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Cross>   , BDefect<Thickness>, BKlass2<Thickness>>					), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Long>    , BKlass2<Thickness>>												), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Long>    , BDefect<Thickness>>												), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Long>    , BDefect<Thickness>, BKlass2<Thickness>>						), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Cross>   , BDefect<Long> >												), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Cross>   , BDefect<Long>, BKlass2<Thickness>>   						), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Cross>   , BDefect<Long>, BDefect<Thickness>> 						), int, 0xffff0000)
DEFINE_WAPPER(JOIN4(Clr<BDefect<Cross>   , BDefect<Long>, BDefect<Thickness>, BKlass2<Thickness>>), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BKlass2<Cross>   , BKlass2<Thickness>>											), int, 0xffffff00)

DEFINE_WAPPER(JOIN2(Clr<BDefect<Thickness>, BKlass2<Cross>>											), int, 0xffff0000)

DEFINE_WAPPER(JOIN3(Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Thickness>>					), int, 0xffff0000)

DEFINE_WAPPER(JOIN2(Clr<BKlass2<Long>, BKlass2<Thickness>>												), int, 0xffffff00)

DEFINE_WAPPER(JOIN2(Clr<BDefect<Thickness>, BKlass2<Long>>												), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Thickness>, BKlass2<Long>, BKlass2<Thickness>>						), int, 0xffff0000)

DEFINE_WAPPER(JOIN2(Clr<BKlass2<Cross>, BKlass2<Long> >												), int, 0xffffff00)

DEFINE_WAPPER(JOIN3(Clr<BKlass2<Cross>, BKlass2<Long>, BKlass2<Thickness>>   						), int, 0xffffff00)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Long>> 						), int, 0xffff0000)
DEFINE_WAPPER(JOIN4(Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Long>, BKlass2<Thickness>>), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Cross>, BKlass2<Long> >												), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Cross>, BKlass2<Long>, BKlass2<Thickness>>						), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Cross>, BKlass2<Long>, BDefect<Thickness>>    					), int, 0xffff0000)
DEFINE_WAPPER(JOIN4(Clr<BDefect<Cross>, BKlass2<Long>, BDefect<Thickness>, BKlass2<Thickness>>), int, 0xffff0000)
DEFINE_WAPPER(JOIN2(Clr<BDefect<Long>, BKlass2<Cross> >												), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Long>, BKlass2<Cross>, BKlass2<Thickness>>   						), int, 0xffff0000)
DEFINE_WAPPER(JOIN3(Clr<BDefect<Long>, BKlass2<Cross>, BDefect<Thickness>>      					), int, 0xffff0000)
DEFINE_WAPPER(JOIN4(Clr<BDefect<Long>, BKlass2<Cross>, BDefect<Thickness>, BKlass2<Thickness>>), int, 0xffff0000) 



struct ColorTable
{
	typedef TL::MkTlst<	
//--------------------------------------------------------------------------------------------------------
/*0*/Clr<Undefined>
/*1*/, Clr<Nominal  >
/*2*/, Clr<DeathZone>
/*3*/, Clr<BKlass2<Long>      >
/*4*/, Clr<BKlass2<Thickness>  >
/*5*/, Clr<BDefect<Thickness>  >
/*6*/, Clr<BDefect<Long>      >
/*7*/, Clr<BKlass2<Cross>     >
/*8*/, Clr<BDefect<Cross>     >
									
/*10*/, Clr<BDefect<Cross>   , BKlass2<Thickness>>										
/*11*/, Clr<BDefect<Cross>   , BDefect<Thickness>>										
					
/*12*/, Clr<BDefect<Long>    , BKlass2<Thickness>>										
/*13*/, Clr<BDefect<Long>    , BDefect<Thickness>>										
				
/*14*/, Clr<BDefect<Cross>   , BDefect<Long> >											
/*15*/, Clr<BDefect<Cross>   , BDefect<Long>, BKlass2<Thickness>>   					
/*16*/, Clr<BDefect<Cross>   , BDefect<Long>, BDefect<Thickness>> 						
 
/*17*/, Clr<BKlass2<Cross>   , BKlass2<Thickness>>										
/*18*/, Clr<BDefect<Thickness>, BKlass2<Cross>>											
					
/*19*/, Clr<BKlass2<Long>, BKlass2<Thickness>>											
/*20*/, Clr<BDefect<Thickness>, BKlass2<Long>>											
					
/*21*/, Clr<BKlass2<Cross>, BKlass2<Long> >												
/*22*/, Clr<BKlass2<Cross>, BKlass2<Long>, BKlass2<Thickness>>   						
/*23*/, Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Long>> 						

/*24*/, Clr<BDefect<Cross>, BKlass2<Long> >												
/*25*/, Clr<BDefect<Cross>, BKlass2<Long>, BKlass2<Thickness>>						
/*26*/, Clr<BDefect<Cross>, BKlass2<Long>, BDefect<Thickness>>    					

/*27*/, Clr<BDefect<Long>, BKlass2<Cross> >												
/*28*/, Clr<BDefect<Long>, BKlass2<Cross>, BKlass2<Thickness>>   						
/*29*/, Clr<BDefect<Long>, BKlass2<Cross>, BDefect<Thickness>>   


//------------------------------------------------------------------------------
///**/, Clr<BDefect<Cross>, BKlass2<Long>, BDefect<Thickness>, BKlass2<Thickness>>
///**/, Clr<BDefect<Long>, BKlass2<Cross>, BDefect<Thickness>, BKlass2<Thickness>>
///**/, Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Long>, BKlass2<Thickness>>
///**/, Clr<BDefect<Thickness>, BKlass2<Long>, BKlass2<Thickness>>	
///**/, Clr<BDefect<Thickness>, BKlass2<Cross>, BKlass2<Thickness>>
///**/, Clr<BDefect<Cross>   , BDefect<Long>, BDefect<Thickness>, BKlass2<Thickness>>
///*13*/, Clr<BDefect<Cross>   , BDefect<Thickness>, BKlass2<Thickness>>
///**/, Clr<BDefect<Long>    , BDefect<Thickness>, BKlass2<Thickness>>	
///*10*/, Clr<BDefect<Thickness>, BKlass2<Thickness>>	
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ColorTable";}
};

template<class T>inline int StatusId()
{
	return TL::IndexOf<ColorTable::items_list, T>::value;
}

template<class T>struct Stat
{
	static const unsigned value = TL::IndexOf<ColorTable::items_list, T>::value;
};
//-------------------------------------------------------------------------------------- 
DEFINE_PARAM(SupplySensorDelay, int, 150)
DEFINE_PARAM(RemoveSensorDelay, int,  150)
DEFINE_PARAM(FrequencyFrames, int,  100)

DEFINE_PARAM(ReferenceOffset1, unsigned, 1750)
DEFINE_PARAM(ReferenceOffset2, unsigned, 4600)

DEFINE_PARAM(ReferenceOffset3, unsigned, 1260)
DEFINE_PARAM(ReferenceOffset4, unsigned, 3030)
struct AdditionalSettingsTable
{
	typedef TL::MkTlst<	
		ReferenceOffset1
		, ReferenceOffset2
		, ReferenceOffset3
		, ReferenceOffset4
		, SupplySensorDelay
		, RemoveSensorDelay
		, FrequencyFrames
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"AdditionalSettingsTable";}
};
//--------------------------------------------------------------------------------------
DEFINE_PARAM(ACFBorderLeft, int, 80)
DEFINE_PARAM(ACFBorderRight, int, 160)
struct ACFBorderTable
{
	typedef TL::MkTlst<
		ACFBorderLeft
		, ACFBorderRight
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ACFBorderTable";}
};
//-----------------------------------------------------------------------------------------------------
 DEFINE_PARAM(DeadAreaMM0, int, 200)
 DEFINE_PARAM(DeadAreaMM1, int, 200)
 struct DeadAreaTable
 {
	typedef TL::MkTlst<
		DeadAreaMM0
		, DeadAreaMM1
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"DeadAreaTable";}
 };
//----------------------------------------------------------------------------------------------------
 template<class>struct MedianFiltreWidth;
 template<class>struct MedianFiltreOn;

 DEFINE_PARAM_WAPPER(MedianFiltreWidth, Cross, int, 5)
 DEFINE_PARAM_WAPPER(MedianFiltreOn, Cross, bool, true)

 DEFINE_PARAM_WAPPER(MedianFiltreWidth, Long, int, 5)
 DEFINE_PARAM_WAPPER(MedianFiltreOn, Long, bool, true)

 DEFINE_PARAM_WAPPER(MedianFiltreWidth, Thickness, int, 5)
 DEFINE_PARAM_WAPPER(MedianFiltreOn, Thickness, bool, true)
 
 struct MedianFiltreTable
 {
	 typedef TL::MkTlst<
		 MedianFiltreWidth<Cross>
		 , MedianFiltreOn<Cross> 
		 , MedianFiltreWidth<Long>
		 , MedianFiltreOn<Long> 
		 , MedianFiltreWidth<Thickness>
		 , MedianFiltreOn<Thickness> 
	 >::Result items_list;
	 typedef TL::Factory<items_list> TItems;
	 TItems items;
	 const wchar_t *name(){return L"MedianFiltreTable";}
 };
 //---------------------------------------------------------------------------------------------------------
 DEFINE_PARAM(NamePlate1730, int, 3)
 struct NamePlate1730ParametersTable
 {
	 typedef TL::MkTlst<
		 NamePlate1730
	 >::Result items_list;
	 typedef TL::Factory<items_list> TItems;
	 TItems items;
	 const wchar_t *name(){return L"NamePlate1730ParametersTable";}
 };
//-------------------------------------------------------------------------------------------------------
struct AxesTable;
struct ChebyshevIParamTable	;
struct ButterworthParamTable;
struct EllipticParamTable	;
struct FiltersTable;
struct LirParamTable;
struct SpeedTable;
struct CorecSignalTable;

template<class T>struct LongDefect	; 
template<class T>struct CrossDefect	  ;
struct ColorTable;


DEFINE_PARAM_ID(ThresholdsTable            , int, 1)
DEFINE_PARAM_ID(DeadAreaTable			   , int, 1)
DEFINE_PARAM_ID(AxesTable	   , int, 1)
DEFINE_PARAM_ID(MedianFiltreTable, int, 1)
DEFINE_PARAM_ID(LirParamTable, int, 1)
DEFINE_PARAM_ID(SpeedTable, int, 1)
DEFINE_PARAM_ID(CorecSignalTable, int, 1)
DEFINE_PARAM_ID(ColorTable, int, 1)


DEFINE_PARAM_WAPPER_ID(CrossDefect, ChebyshevIParamTable, int, 1)
DEFINE_PARAM_WAPPER_ID(CrossDefect, ButterworthParamTable, int, 1)
DEFINE_PARAM_WAPPER_ID(CrossDefect, EllipticParamTable	, int, 1)
DEFINE_PARAM_WAPPER_ID(LongDefect, ChebyshevIParamTable, int, 1)
DEFINE_PARAM_WAPPER_ID(LongDefect, ButterworthParamTable, int, 1)
DEFINE_PARAM_WAPPER_ID(LongDefect, EllipticParamTable	, int, 1)

DEFINE_PARAM_ID(FiltersTable, int, 1)


STR_PARAM(NameParam, 128, L"NONAME")
DEFINE_PARAM(TubeDiameter, int, 73)
 struct ParametersTable
 {
	typedef TL::MkTlst<
		ID<ThresholdsTable>
		, ID<DeadAreaTable			   	>
		, ID<AxesTable	   	>
		, ID<MedianFiltreTable>
		, ID<CrossDefect<ChebyshevIParamTable >>
		, ID<CrossDefect<ButterworthParamTable>>
		, ID<CrossDefect<EllipticParamTable	  >>

		, ID<LongDefect<ChebyshevIParamTable >>
		, ID<LongDefect<ButterworthParamTable>>
		, ID<LongDefect<EllipticParamTable	  >>
		, ID<FiltersTable		  >
		, ID<LirParamTable>
		, ID<SpeedTable>
		, ID<CorecSignalTable>
		, ID<ColorTable>
		, NameParam
		, TubeDiameter
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ParametersTable";}
 };
//--------------------------------------------------------------------------------------------------------
DEFINE_PARAM(Descriptor1730_0, unsigned, 1)
DEFINE_PARAM(Descriptor1730_1, unsigned, 2)
struct Descriptor1730Table
 {
	typedef TL::MkTlst<
		Descriptor1730_0
		, Descriptor1730_1
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Descriptor1730Table";}
 };
 //--------------------------------------------------------------------------------------------------------
///\brief Смещение измерительных датчиков
template<class T, int N>struct Offset;
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 0, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 1, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 2, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 3, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 4, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 5, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 6, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Long, 7, int, 0)

DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 0, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 1, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 2, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 3, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 4, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 5, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 6, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Cross, 7, int, 0)

DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 0, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 1, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 2, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 3, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 4, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 5, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 6, int, 0)
DEFINE_PARAM_WAPPER_NUM(Offset, Thickness, 7, int, 0)

struct OffsetsTable
{
	typedef TL::MultyListToList<TL::MkTlst<
		TL::CreateWapperNumList<Offset, Long, 0, 7>::Result
		, TL::CreateWapperNumList<Offset, Cross, 0, 7>::Result
		, TL::CreateWapperNumList<Offset, Thickness, 0, 7>::Result
	>::Result>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"OffsetsTable";}
};
//-----------------------------------------------------------------------------------------------------------
template<class T>struct AxesYMin;
template<class T>struct AxesYMax;
DEFINE_PARAM_WAPPER(AxesYMin, Long, double, 0)
DEFINE_PARAM_WAPPER(AxesYMax, Long, double, 100)
DEFINE_PARAM_WAPPER(AxesYMin, Cross, double, 0)
DEFINE_PARAM_WAPPER(AxesYMax, Cross, double, 100)
DEFINE_PARAM_WAPPER(AxesYMin, Thickness, double, 0)
DEFINE_PARAM_WAPPER(AxesYMax, Thickness, double, 15)

struct AxesTable
{
	typedef TL::MkTlst<
		AxesYMin<Long>
		, AxesYMax<Long>
		, AxesYMin<Cross>
		, AxesYMax<Cross>
		, AxesYMin<Thickness>
		, AxesYMax<Thickness>
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"AxesTable";}
};
//-----------------------------------------------------------------------------------------------------------
template<class T>struct OnTheJob;
//DEFINE_PARAM_WAPPER(OnTheJob, Cross    , bool, true)
DEFINE_PARAM_WAPPER(OnTheJob, Long     , bool, true)
DEFINE_PARAM_WAPPER(OnTheJob, Thickness, bool, true)

struct OnTheJobTable
{
	typedef TL::MkTlst<
		 OnTheJob<Long     >
		, OnTheJob<Thickness>
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"OnTheJobTable";}
};
//-----------------------------------------------------------------------------------------------------------
template<class T>struct ChebyshevIParam;
template<class T>struct ButterworthParam;
template<class T>struct EllipticParam;

struct Order			{}; 
struct CutoffFrequency	{};
struct CenterFrequency	{};
struct WidthFrequency	{};
struct RippleDb		 	{};
struct Type			 	{};
struct Rolloff{};

typedef TL::MkTlst<
	ChebyshevIParam<Order>
	, ButterworthParam<Order>
	, EllipticParam	  <Order>
>::Result type_filters_list;

struct LowPass	{};
struct HighPass	{};
struct BandPass	{};
struct BandStop	{};

typedef TL::MkTlst<
LowPass, HighPass, BandPass, BandStop
>::Result sub_type_filter_list;

DEFINE_PARAM_WAPPER(ChebyshevIParam, Order			,    int, 2)
DEFINE_PARAM_WAPPER(ChebyshevIParam, CutoffFrequency, double, 120)
DEFINE_PARAM_WAPPER(ChebyshevIParam, CenterFrequency, double, 80)
DEFINE_PARAM_WAPPER(ChebyshevIParam, WidthFrequency	, double, 50)
DEFINE_PARAM_WAPPER(ChebyshevIParam, RippleDb		, double, 0.3)
DEFINE_PARAM_WAPPER(ChebyshevIParam, Type			,    int, 0)

struct ChebyshevIParamTable
{
	typedef TL::MkTlst<
		ChebyshevIParam<Type			 >
		, ChebyshevIParam  <Order			 >
		, ChebyshevIParam<CutoffFrequency>
		, ChebyshevIParam<CenterFrequency>
		, ChebyshevIParam<WidthFrequency>	
		, ChebyshevIParam<RippleDb		 >		
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	//const wchar_t *name(){return L"CrossDefectChebyshevIParamTable";}
};
template<>struct CrossDefect<ChebyshevIParamTable>: ChebyshevIParamTable
{
	const wchar_t *name(){return L"CrossDefectChebyshevIParamTable";}
};
template<>struct LongDefect<ChebyshevIParamTable>: ChebyshevIParamTable
{	
	const wchar_t *name(){return L"LongDefectChebyshevIParamTable";}
};


DEFINE_PARAM_WAPPER(ButterworthParam, Order,		  int   , 2)
DEFINE_PARAM_WAPPER(ButterworthParam, CutoffFrequency,double, 120)
DEFINE_PARAM_WAPPER(ButterworthParam, CenterFrequency,double, 80)
DEFINE_PARAM_WAPPER(ButterworthParam, WidthFrequency, double, 50)
DEFINE_PARAM_WAPPER(ButterworthParam, Type			, int   , 0)

struct ButterworthParamTable
{
	typedef TL::MkTlst<
	   ButterworthParam<Type			  >
	   , ButterworthParam  <Order		  >
	   , ButterworthParam<CutoffFrequency>
	   , ButterworthParam<CenterFrequency>
	   , ButterworthParam<WidthFrequency >	   
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	//const wchar_t *name(){return L"CrossDefectButterworthParamTable";}
};

template<>struct CrossDefect<ButterworthParamTable>: ButterworthParamTable
{
	const wchar_t *name(){return L"CrossDefectButterworthParamTable";}
};

template<>struct LongDefect<ButterworthParamTable>: ButterworthParamTable
{
	const wchar_t *name(){return L"LongDefectButterworthParamTable";}
};

DEFINE_PARAM_WAPPER(EllipticParam, Order,		  int   , 2)
DEFINE_PARAM_WAPPER(EllipticParam, CutoffFrequency,double, 120)
DEFINE_PARAM_WAPPER(EllipticParam, CenterFrequency,double, 80)
DEFINE_PARAM_WAPPER(EllipticParam, WidthFrequency, double, 50)
DEFINE_PARAM_WAPPER(EllipticParam, RippleDb,		  double, 0.3)
DEFINE_PARAM_WAPPER(EllipticParam, Rolloff,		  double, 0.3)
DEFINE_PARAM_WAPPER(EllipticParam, Type,			  int   , 0)

struct EllipticParamTable
{
	typedef TL::MkTlst<
		EllipticParam<Type			 >
		, EllipticParam<Order		 	 >
		, EllipticParam<CutoffFrequency>
		, EllipticParam<CenterFrequency>
		, EllipticParam<WidthFrequency >
		, EllipticParam<RippleDb		 >
		, EllipticParam<Rolloff		 >		
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	//const wchar_t *name(){return L"CrossDefectEllipticParamTable";}
};

template<>struct CrossDefect<EllipticParamTable>: EllipticParamTable
{
	const wchar_t *name(){return L"CrossDefectEllipticParamTable";}
};

template<>struct LongDefect<EllipticParamTable>: EllipticParamTable
{
	const wchar_t *name(){return L"LongDefectEllipticParamTable";}
};

DEFINE_PARAM(FilterOnJob, bool, true)
DEFINE_PARAM(FilterType, int, 1)



DEFINE_PARAM_WAPPER(LongDefect, FilterOnJob  , bool, true)
DEFINE_PARAM_WAPPER(LongDefect, FilterType   , int, 1)

DEFINE_PARAM_WAPPER(CrossDefect, FilterOnJob   , bool, true)
DEFINE_PARAM_WAPPER(CrossDefect, FilterType	   , int, 1)

struct FiltersTable
{
	typedef TL::MkTlst<	
	  LongDefect<FilterOnJob>  
	 , LongDefect<FilterType >  
	 , CrossDefect<FilterOnJob >  
	 , CrossDefect<FilterType	 >  
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"FiltersTable";}
};
//------------------------------------------------------------------------------------------------------------
template<class, int>struct ASignal;
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  0, int,  0)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  1, int,  1)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  2, int,  2)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  3, int,  3)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  4, int,  4)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  5, int,  5)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  6, int,  6)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  7, int,  9)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  8, int,  10)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross,  9, int,  11)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross, 10, int,  7)
DEFINE_PARAM_WAPPER_NUM(ASignal, Cross, 11, int,  8)
						
DEFINE_PARAM_WAPPER_NUM(ASignal, Long,   0, int,  16)
DEFINE_PARAM_WAPPER_NUM(ASignal, Long,   1, int,  17)
DEFINE_PARAM_WAPPER_NUM(ASignal, Long,   2, int,  18)
DEFINE_PARAM_WAPPER_NUM(ASignal, Long,   3, int,  19)

struct ASignalTable
{
	typedef TL::MultyListToList<TL::MkTlst<	
		TL::CreateWapperNumList<ASignal, Cross, 0, 11>::Result
		, TL::CreateWapperNumList<ASignal, Long, 0, 3>::Result
	>::Result>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ASignalTable";}
};

template<class T>struct Gain;

DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  0, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  1, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  2, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  3, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  4, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  5, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  6, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  7, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  8, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross,  9, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross, 10, int,  2)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Cross, 11, int,  2)
				
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Long,   0, int,  1)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Long,   1, int,  1)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Long,   2, int,  1)
DEFINE_PARAM_WAPPER_2_NUM(Gain, ASignal, Long,   3, int,  1)

struct GainSignalTable
{
	typedef TL::ListToWapperList<ASignalTable::items_list, Gain>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"GainSignalTable";}
};

template<class T>struct Corec;

DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  0, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  1, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  2, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  3, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  4, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  5, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  6, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  7, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  8, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross,  9, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross, 10, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Cross, 11, double,  1)
													
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Long,   0, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Long,   1, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Long,   2, double,  1)
DEFINE_PARAM_WAPPER_2_NUM(Corec, ASignal, Long,   3, double,  1)

struct CorecSignalTable
{
	typedef TL::ListToWapperList<ASignalTable::items_list, Corec>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"CorecSignalTable";}
};

DEFINE_PARAM(PerChannelFrequency, int, 10000)
struct AnalogBoardTable
{
	typedef TL::MkTlst<PerChannelFrequency>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"AnalogBoardTable";}
};
//--------------------------------------------------------------------------------------
DEFINE_PARAM(ComPortAddr, int, 1)
DEFINE_PARAM(BaudRate, int, 9600)
DEFINE_PARAM(Parity, int, NOPARITY)
DEFINE_PARAM(StopBits, int, ONESTOPBIT)
struct ComPortTable
{
	typedef TL::MkTlst<
		ComPortAddr
		, BaudRate
		, Parity
		, StopBits
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"ComPortTable";}
};
//------------------------------------------------------------------------------------------------------------
DEFINE_PARAM(IPPort, int, 8888)
//#define ip_address() ((192 << 24) | (168 << 16) | (0 << 8) | (1 << 0))
//DEFINE_PARAM(IPAddr, int, ip_address())
STR_PARAM(IPName, 64, L"A2")
//#undef ip_address
struct IPAddressTable
{
	typedef TL::MkTlst<	
		IPPort
		, IPName
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"IPAddressTable";}
};
//..-------------
DEFINE_PARAM(TickPerZoneLir0, int, 106)
DEFINE_PARAM(TickPerZoneLir1, int, 106)
DEFINE_PARAM(DescriptorLir, int, 3)
struct LirParamTable
{
	typedef TL::MkTlst<	
		TickPerZoneLir0
		, TickPerZoneLir1
		, DescriptorLir
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"LirParamTable";}
};
//--------------------------------------------
DEFINE_PARAM(SpeedRL, bool, true)
DEFINE_PARAM(SpeedRM, bool, false)
DEFINE_PARAM(SpeedRH, bool, false)

struct SpeedTable
{
	typedef TL::MkTlst<	
		SpeedRL
		, SpeedRM
		, SpeedRH
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"SpeedTable";}
};
//--------------------------------------------
DEFINE_PARAM(Solenoid0U, double, 9.0)
DEFINE_PARAM(Solenoid1U, double, 9.0)
DEFINE_PARAM(MagneticFieldTurnedOn, int, 4000)
struct UnitControlsTable
{
	typedef TL::MkTlst<	
		Solenoid0U
		, Solenoid1U
	//	, MagneticFieldTurnedOn
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"UnitControlsTable";}
};
DEFINE_PARAM_WAPPER_NUM(ASignal, Solenoid0U, 0, int, 13)
DEFINE_PARAM_WAPPER_NUM(ASignal, Solenoid1U, 0, int, 14)
DEFINE_PARAM_WAPPER_NUM(ASignal, MagneticFieldTurnedOn, 0, int, 15)
struct UnitControlsOffsetTable
{
	typedef TL::MkTlst<	
		ASignal<Solenoid0U, 0>
		, ASignal<Solenoid1U, 0>
		, ASignal<MagneticFieldTurnedOn, 0>
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"UnitControlsOffsetTable";}
};
//----------------------------------------------
 struct ParametersBase
 {
	 typedef TL::MkTlst<
		  NamePlate1730ParametersTable	  		
		 , PointsOptionsTable			
		 , GraphicSignalOptionsTable	   
		 , AdditionalSettingsTable		
		 , ACFBorderTable
		 , InputsTable<0>
		 , InputsTable<1>
		 , OutputsTable<0>
		 , OutputsTable<1>
		 , Descriptor1730Table
		 , OffsetsTable
		 , OnTheJobTable
		 , ASignalTable
		 , GainSignalTable
		 , ComPortTable
		 , AnalogBoardTable
		 , IPAddressTable
		 , UnitControlsTable
		 , UnitControlsOffsetTable
	 >::Result one_row_table_list;

	 typedef TL::MkTlst<
		  CurrentParametersTable		 
		 , ParametersTable			   
		 , ThresholdsTable			  
		 , DeadAreaTable	
		 , MedianFiltreTable
		 , AxesTable
		 , LongDefect<ChebyshevIParamTable >
		 , LongDefect<ButterworthParamTable>
		 , LongDefect<EllipticParamTable   >
		 , CrossDefect<ChebyshevIParamTable >
		 , CrossDefect<ButterworthParamTable>
		 , CrossDefect<EllipticParamTable   >
		 , FiltersTable
		 , LirParamTable
		 , SpeedTable
		 , CorecSignalTable
		 , ColorTable
	 >::Result multy_row_table_list;

	 typedef TL::MkTlst<
		  multy_row_table_list
		 , one_row_table_list
	 >::Result multy_type_list; 

	 typedef TL::MultyListToList<multy_type_list>::Result type_list;
	 typedef TL::Factory<type_list> TTables;
	 TTables tables;
	 wchar_t path[512];
	 const wchar_t *name();
 };

struct AppBase
{
	void Init();
	static void InitTypeSizeTables(CBase &);
};

template<class T>int CurrentId()
{
	 // CurrentParametersTable &current = Singleton<CurrentParametersTable>::Instance();
	 // Select<CurrentParametersTable>(base).ID(1).Execute(current);
	 // ParametersTable param;
	 // Select<ParametersTable>(base).ID(current.items.get<CurrentID>().value).Execute(param);
	  return Singleton<ParametersTable>::Instance().items.get<T>().value;
}

/*
template<class T>int CountId(CBase &base, int num)
{
	wchar_t buf[128];
	wsprintf(buf, L"SELECT COUNT(*) FROM ParametersTable WHERE %s=%d", T().name(), num);
	int t = base.ConnectionSQL(buf);
	return t;
}
*/
template<class T>void UpdateId(CBase &base, int num)
{
   CurrentParametersTable &current = Singleton<CurrentParametersTable>::Instance();
   Select<CurrentParametersTable>(base).ID(1).Execute(current);
   ParametersTable &t = Singleton<ParametersTable>::Instance();
   t.items.get<T>().value = num;
   UpdateWhere<ParametersTable>(t, base).ID(current.items.get<CurrentID>().value).Execute();
}
/*
template<class T>int CurrentId(CBase &base)
{
	  CurrentParametersTable &current = Singleton<CurrentParametersTable>::Instance();
	  Select<CurrentParametersTable>(base).ID(1).Execute(current);
	  ParametersTable param;
	  Select<ParametersTable>(base).ID(current.items.get<CurrentID>().value).Execute(param);
	  return param.items.get<T>().value;
}
*/
template<class T>int CountId(CBase &base, int num)
{
	ADODB::_RecordsetPtr rec;
	Select<ParametersTable>(base).eq<T>(num).Execute(rec);
	int i = 0;
	while (!rec->EndOfFile) 
	{			
		++i;
		rec->MoveNext(); 
	}
	return i;
}
/*
template<class T>void UpdateId(CBase &base, int num)
{
   CurrentParametersTable &current = Singleton<CurrentParametersTable>::Instance();
   Select<CurrentParametersTable>(base).ID(1).Execute(current);
   Update<ParametersTable>(base).set<T>(num).Where().ID(current.items.get<CurrentID>().value).Execute();
}
*/







