#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"
#include "typelist.hpp"

PARAM_TITLE(FilterOnJob, L"Использовать")
PARAM_TITLE(FilterType, L"Тип фильтра")

template<template<class>class W>struct ParamTitle<W<Order> >{wchar_t *operator()(){return L"Порядок фильтра";}};
template<template<class>class W>struct ParamTitle<W<CutoffFrequency> >{wchar_t *operator()(){return L"Частота среза";}};
template<template<class>class W>struct ParamTitle<W<CenterFrequency> >{wchar_t *operator()(){return L"Центр фильтра";}};
template<template<class>class W>struct ParamTitle<W<WidthFrequency> >{wchar_t *operator()(){return L"Ширина фильтра";}};
template<template<class>class W>struct ParamTitle<W<RippleDb> >{wchar_t *operator()(){return L"Пульсация в полосе пропускания";}};
template<template<class>class W>struct ParamTitle<W<Type> >{wchar_t *operator()(){return L"Подтип фильтра";}};
template<template<class>class W>struct ParamTitle<W<Rolloff> >{wchar_t *operator()(){return L"Пульсации в полосе подавления";}};

template<template<class>class W>struct DlgSubItems<W<Order>, int >: UpDownSubItem<W<Order>, 1, 10, 140>{};
template<>struct DlgSubItems<FilterType, int >: ComboBoxSubItem<FilterType>{};

template<>struct FillComboboxList<FilterType>
{
	void operator()(HWND h, FilterType &t)
	{
		ComboBox_AddString(h, L"Чебышева");
		ComboBox_AddString(h, L"Баттерворта");
		ComboBox_AddString(h, L"Еллиптический");
	}
};

template<>struct CurrentValue<FilterType>
{
	void operator()(HWND h, FilterType &t)
	{
		ComboBox_SetCurSel(h, t.value);
		zprint(" current value %d\n", t.value);
	}
};

template<>struct __handler_data_widget__<DlgItem<FilterType>, int>
{
	int operator()(HWND h)
	{
		return ComboBox_GetCurSel(h);
	}
};

template<template<class>class W>struct DlgSubItems<W<Type>, int >: ComboBoxSubItem<W<Type>>{};
template<template<class>class W>struct FillComboboxList<W<Type>>
{
	void operator()(HWND h, W<Type> &t)
	{
		ComboBox_AddString(h, L"Низких частот");
		ComboBox_AddString(h, L"Высоких частот");
		ComboBox_AddString(h, L"Полосовой");
		ComboBox_AddString(h, L"Заграждающий");
	}
};
template<template<class>class W>struct CurrentValue<W<Type>>
{
	void operator()(HWND h, W<Type> &t)
	{
		ComboBox_SetCurSel(h, t.value);
	}
};

DO_NOT_CHECK(FilterType)
DO_NOT_CHECK(ChebyshevIParam<Type>)

MIN_EQUAL_VALUE(ChebyshevIParam<Order>, 1)
MAX_EQUAL_VALUE(ChebyshevIParam<Order>, 10)

DO_NOT_CHECK(ButterworthParam<Type>)

MIN_EQUAL_VALUE(ChebyshevIParam<CutoffFrequency>, 10)
MAX_EQUAL_VALUE(ChebyshevIParam<CutoffFrequency>, 1000)

MIN_EQUAL_VALUE(ButterworthParam<Order>, 10)
MAX_EQUAL_VALUE(ButterworthParam<Order>, 1000)

DO_NOT_CHECK(EllipticParam<Type>)

MIN_EQUAL_VALUE(EllipticParam<Order>, 1)
MAX_EQUAL_VALUE(EllipticParam<Order>, 10)

MIN_EQUAL_VALUE(ChebyshevIParam<CenterFrequency>, 10)
MAX_EQUAL_VALUE(ChebyshevIParam<CenterFrequency>, 1000)

MIN_EQUAL_VALUE(ButterworthParam<CutoffFrequency>, 10)
MAX_EQUAL_VALUE(ButterworthParam<CutoffFrequency>, 1000)

MIN_EQUAL_VALUE(ChebyshevIParam<WidthFrequency>, 10)
MAX_EQUAL_VALUE(ChebyshevIParam<WidthFrequency>, 1000)

MIN_EQUAL_VALUE(ButterworthParam<CenterFrequency>, 10)
MAX_EQUAL_VALUE(ButterworthParam<CenterFrequency>, 1000)

MIN_EQUAL_VALUE(EllipticParam<CutoffFrequency>, 10)
MAX_EQUAL_VALUE(EllipticParam<CutoffFrequency>, 1000)

MIN_EQUAL_VALUE(ChebyshevIParam<RippleDb>, 0)
MAX_EQUAL_VALUE(ChebyshevIParam<RippleDb>, 10)

MIN_EQUAL_VALUE(ButterworthParam<WidthFrequency>, 10)
MAX_EQUAL_VALUE(ButterworthParam<WidthFrequency>, 1000)

MIN_EQUAL_VALUE(EllipticParam<CenterFrequency>, 10)
MAX_EQUAL_VALUE(EllipticParam<CenterFrequency>, 1000)

MIN_EQUAL_VALUE(EllipticParam<WidthFrequency>, 10)
MAX_EQUAL_VALUE(EllipticParam<WidthFrequency>, 1000)

MIN_EQUAL_VALUE(EllipticParam<RippleDb>, 0)
MAX_EQUAL_VALUE(EllipticParam<RippleDb>, 10)

MIN_EQUAL_VALUE(EllipticParam<Rolloff>, 0)
MAX_EQUAL_VALUE(EllipticParam<Rolloff>, 10)

PARAM_TITLE(CrossDefect<FilterType>, L"Фильтр поперечных дефектов")
PARAM_TITLE(LongDefect<FilterType>, L"Фильтр продольных дефектов")


namespace
{
	template<class T>struct XXTable;

	template<>struct XXTable<ChebyshevIParamTable>
	{
		typedef TL::MultyListToList<TL::MkTlst<
			TL::MkTlst<FilterOnJob, FilterType>::Result 
			, ChebyshevIParamTable::items_list
			>::Result>::Result items_list;
		typedef TL::Factory<items_list> TItems;
		TItems items;
	};

	template<>struct XXTable<ButterworthParamTable>
	{
		typedef TL::MultyListToList<TL::MkTlst<
			TL::MkTlst<FilterOnJob, FilterType>::Result 
			, ButterworthParamTable::items_list
			>::Result>::Result items_list;
		typedef TL::Factory<items_list> TItems;
		TItems items;
	};

	template<>struct XXTable<EllipticParamTable>
	{
		typedef TL::MultyListToList<TL::MkTlst<
			TL::MkTlst<FilterOnJob, FilterType>::Result 
			, EllipticParamTable::items_list
			>::Result>::Result items_list;
		typedef TL::Factory<items_list> TItems;
		TItems items;
	};

	struct __sel_data__
		{
			int filtType;
			HWND h;
		};
//-----------------------------------------------------------------------------------------------------------
	template<class T>struct SelectTypeFiltre;
	template<class T>struct ChangeFilterType
		{
			static const int ID = 99;
			static const int width = 0;
			HWND hWnd;
			template<class Owner>void BtnHandler(Owner &owner, HWND h){}
			template<class P>bool SelChange(P *p)
			{
				if((unsigned)hWnd != p->id) return true;

				int type = (int)SendMessage(hWnd, CB_GETCURSEL, 0, 0);

				EndDialog(GetParent(hWnd), FALSE);

				__sel_data__ data = {
					type
					, GetParent(GetParent(hWnd))
				};
				SelectTypeFiltre<T>::Do(data);
				return false;
			}
		};

		template<class P, class T>struct __make_btn__<ChangeFilterType<T>, P>
		{
			typedef ChangeFilterType<T> O;
			void operator()(O *o, P *p)
			{
				O &x = p->owner->buttons.get<O>();
				x.hWnd = p->owner->items.get<DlgItem<FilterType>>().hWnd;
			}
		};

	  
	

	template<template<class >class Filtre, class T>struct SelectTypeFiltre<Filtre<T> >
	{

		typedef TL::MkTlst<
			XXTable<ChebyshevIParamTable>
			, XXTable<ButterworthParamTable>
			, XXTable<EllipticParamTable>
		>::Result __type_filters_list__;

		template<class O, class P>struct __ok_btn__
		{
			void operator()(O *o, P *p)
			{
				o->value.value =  __data_from_widget__<O, typename TL::Inner<O>::Result::type_value>()(*o);
			}
		};

		template<class O, class P>struct __update__
		{
			void operator()(O *o, P *p)
			{
				p->update.set<O>(o->value);
			}
		};

		template<class Table>struct __store_table__
		{
			template<class T>void operator()(T &t, CBase &base)
			{
				int id = CurrentId<::ID<Table> >();	
				__update_data__<Table> _data(base);			
				TL::foreach<Table::items_list, __update__>()(&t.items, &_data);
				if(1 == CountId<::ID<Table> >(base, id))
				{
					_data.update.Where().ID(CurrentId<::ID<Table> >()).Execute();
				}
				else
				{
					Insert_Into<Table>(t, base).Execute();
					int id = Select<Table>(base).eq_all<Table::items_list>(&t.items).Execute();
					UpdateId<::ID<Table> >(base, id);
				}
			}
		};

		template<class O, class P>struct __sel_header_;
		template<class X, class P, template<class>class W>struct __sel_header_<W<X>, P>
		{
			void operator()(W<X> *o, P *p)
			{
				o->value = p->get<DlgItem<X> >().value.value;
			}
		};

		template<class O, class P>struct __sel__
		{
			void operator()(O *o, P *p)
			{
				o->value = p->get<DlgItem<O> >().value.value;
			}
		};

		struct FilterOkBtn
		{
			static const int width = 120;
			static const int height = 30;
			static const int ID = IDOK;
			wchar_t *Title(){return L"Применить";}
			template<class Owner>void BtnHandler(Owner &owner, HWND h)
			{
				typedef Filtre<TL::Inner<Owner::Table>::Result> Table;
				if(TestPassword<Table>()(h))
				{
					if(!TL::find<typename Owner::list, __test__>()(&owner.items, &h))return;
					CBase base(ParametersBase().name());
					if(base.IsOpen())
					{
						TL::foreach<typename Owner::list, __ok_btn__>()(&owner.items, (int *)0);

						FiltersTable &ft = Singleton<FiltersTable>::Instance();
						typedef typename TL::SelectWapper<FiltersTable::items_list, Filtre>::Result list;
						TL::foreach<list, __sel_header_>()(&ft.items, &owner.items);
						__store_table__<FiltersTable>()(ft, base);

						Table &tt = Singleton<Table>::Instance();
						TL::foreach<Table::items_list, __sel__>()(&tt.items, &owner.items);
						__store_table__<Table>()(tt, base);
					}
					EndDialog(h, TRUE);
				}
			}
		};

		template<class O, class P>struct __set_table__
		{
			void operator()(O *o, P *p)
			{
				o->value = p->get<O>().value;
			}
		};

		template<class O, class P>struct filtreDlg
		{
			bool operator()(O *, P *p)
			{
				if(TL::IndexOf<__type_filters_list__, O>::value == p->filtType)
				{
					O t;
					t.items.get<FilterOnJob>().value = Singleton<FiltersTable>::Instance().items.get<Filtre<FilterOnJob>>().value;
					t.items.get<FilterType>().value = p->filtType;

					typedef Filtre<TL::Inner<O>::Result> Table;

					Table &tt = Singleton<Table>::Instance();
					TL::foreach<Table::items_list, __set_table__>()(&t.items, &tt.items);

					if(TemplDialog<O, TL::MkTlst<FilterOkBtn, CancelBtn, ChangeFilterType<Filtre<T>>>::Result>(t).Do(p->h, ParamTitle<Filtre<T>>()()))
					{
					}
					return false;
				}
				return true;
			}
		};

		static void Do(__sel_data__ &data)
		{
			TL::find<__type_filters_list__, filtreDlg>()((TL::Factory<__type_filters_list__> *)0, &data);
		}

	};
}

void CrossDefectFiltreDlg::Do(HWND h)
{
	__sel_data__ data = {
		Singleton<FiltersTable>::Instance().items.get<CrossDefect<FilterType>>().value
		, h
	};
	SelectTypeFiltre<CrossDefect<FilterType>>::Do(data);
}

void LongDefectFiltreDlg::Do(HWND h)
{
	__sel_data__ data = {
		Singleton<FiltersTable>::Instance().items.get<LongDefect<FilterType>>().value
		, h
	};
	SelectTypeFiltre<LongDefect<FilterType>>::Do(data);
}