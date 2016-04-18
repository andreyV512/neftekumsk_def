#pragma once
#include "typelist.hpp"
//#include "ParamDlg.hpp"

#define DEFINE_Bits(z, def_val, txt) struct z\
{\
	typedef unsigned type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#z;}\
	z() : value(def_val), default_value(def_val) {}\
};

DEFINE_Bits(BASE_TS	 	,1 << 4	,L"Сигнал Базы"                                      )
DEFINE_Bits(CONTROL	 	,1 << 13	,L"Контроль из толщиномера"							)
DEFINE_Bits(PCHA	 	,1 << 9	,L"Сигнал А с частотника продольного контроля"		)
DEFINE_Bits(PCHB	 	,1 << 8	,L"Сигнал B с частотника продольного контроля"		)
DEFINE_Bits(PCHRUN	 	,1 << 10	,L"Сигнал RUN с частотника продольного контроля"		)
DEFINE_Bits(READY	 	,1 << 12	,L"Готовность из толщиномера"						)

DEFINE_Bits(SQfirst	 	, 1 << 7	,L"Датчик на первом лире")

DEFINE_Bits(SQcrossIN	 	,1 << 0	,L"Датчик на входе модуля поперечного контроля"		)
DEFINE_Bits(SQcrossOUT	 	,1 << 1	,L"Датчик на выходе модуля поперечного контроля"		)

DEFINE_Bits(SQthickIN	 	,1 << 5	,L"Датчик на входе толщиномера"		)
DEFINE_Bits(SQthickOUT	 	,1 << 6	,L"Датчик на выходе толщиномера"		)

DEFINE_Bits(SQlongIN	 	,1 << 2	,L"Датчик на входе в модуль продольного контроля"	)
DEFINE_Bits(SQlongOUT	 	,1 << 3	,L"Датчик на выходе модуля продольного контроля"		)
DEFINE_Bits(ZU	     	,1 << 11	,L"Цепи управления"									)
template<int>struct InputsTable;
template<int>struct OutputsTable;
template<>struct InputsTable<0>
{
	typedef TL::MkTlst<	
		BASE_TS
		, CONTROL
		, PCHA	
		, PCHB	
		, PCHRUN	
		, READY	
		, SQcrossIN	
		, SQcrossOUT
		, SQthickIN
		, SQthickOUT
		, SQlongIN	
		, SQlongOUT	
		, SQfirst
		, ZU	   		
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Inputs0Table";}
};

DEFINE_Bits(CYCLE	 	,1 << 8	,L"Сигнал ЦИКЛ в толщиномер"							)
DEFINE_Bits(POWPCH	 	,1 << 0	,L"Включение питания частотника продольного контроля")
DEFINE_Bits(POWSU	 	,1 << 5	,L"Питание СУ продольного контроля"					)
DEFINE_Bits(RH	     	,1 << 3	,L"Старший бит скорости продольного контроля"		)
DEFINE_Bits(RL	     	,1 << 1	,L"Младший бит скорости продольного контроля"		)
DEFINE_Bits(RM	     	,1 << 2	,L"Средний бит скорости продольного контроля"		)
DEFINE_Bits(STF	     	,1 << 4	,L"Пуск вращения продольного контроля"				)

template<>struct OutputsTable<0>
{
	typedef TL::MkTlst<	
		CYCLE
		, POWPCH
		, POWSU
		, RH	  
		, RL	  
		, RM	  
		, STF	  
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Outputs0Table";}
};

DEFINE_Bits(CYCLE_TS 	,1 << 0	,L"ТС в режиме автомат"								)
DEFINE_Bits(TPP_TS	 	,1 << 4	,L"ТПП из ТС"										)
DEFINE_Bits(WCROSS	 	,1 << 1	,L"РП Поперечного из ТС"								)
DEFINE_Bits(WLINE	 	,1 << 3	,L"РП Продольного из ТС"								)
DEFINE_Bits(WTHICK	 	,1 << 2	,L"РП Толщиномера из ТС"								)

template<>struct InputsTable<1>
{
	typedef TL::MkTlst<	
		CYCLE_TS 
		, TPP_TS	 
		, WCROSS	 
		, WLINE	 
		, WTHICK	 
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Inputs1Table";}
};

DEFINE_Bits(RCROSS	 	,1 << 8	,L"Готовность Поперечного в ТС"						)
DEFINE_Bits(RESULT	 	,1 << 13	,L"Результат"										)
DEFINE_Bits(REVERSE  	,1 << 12	,L"Реверс"											)
DEFINE_Bits(RLINE	 	,1 << 10	,L"Готовность Продольного в ТС"						)
DEFINE_Bits(RTHICK	 	,1 << 9	,L"Готовность Толщиномера в ТС"						)
DEFINE_Bits(START	 	,1 << 11	,L"Пуск"												)

template<>struct OutputsTable<1>
{
	typedef TL::MkTlst<	
		RCROSS	
		, RESULT	
		, REVERSE 
		, RLINE	
		, RTHICK	
		, START	
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Outputs1Table";}
};

#undef DEFINE_Bits

