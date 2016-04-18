#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"
#include "MainWindow.h"

namespace
{
	struct AddOkBtn
	{
		static const int width = 120;
		static const int height = 30;
		static const int ID = IDOK;
		wchar_t *Title(){return L"Применить";}
		template<class Owner>void BtnHandler(Owner &owner, HWND h)
		{
			if(TestPassword<Owner::Table>()(h))
			{
				wchar_t name[128];
				GetWindowText(owner.items.get<DlgItem<NameParam> >().hWnd, name, dimention_of(name));
				if(0 == name[0] || 0 == wcscmp(L"NONAME", name))
				{
					MessageBox(h, L"Введите название типоразмера", L"Ошибка!!!", MB_ICONERROR);
					return;
				}
				wchar_t diameter[16];
				wchar_t buf[128];
				GetWindowText(owner.items.get<DlgItem<TubeDiameter> >().hWnd, diameter, dimention_of(diameter));
				wsprintf(buf, L"%s %s", diameter, name);
				CBase base(ParametersBase().name());
				if(base.IsOpen())
				{
					owner.table.items.get<NameParam>().value = buf;
					int id = Select<Owner::Table>(base).eq<NameParam>(owner.table.items.get<NameParam>().value).Execute();
					if(0 != id)
					{
						MessageBox(h, L"Название типоразмера есть в базе данных", L"Предупреждение!!!", MB_ICONEXCLAMATION);
						return;
					}
					else
					{
						Insert_Into<Owner::Table>(owner.table, base).Execute<Owner::Table::items_list>();
						id = Select<Owner::Table>(base).eq<NameParam>(owner.table.items.get<NameParam>().value).Execute();				   
					}
					CurrentParametersTable curr = Singleton<CurrentParametersTable>::Instance();
					curr.items.get<CurrentID>().value = id;
					UpdateWhere<CurrentParametersTable>(curr, base).ID(1).Execute();
					HWND hMain = GetParent(h);
					MainWindow *o = (MainWindow *)GetWindowLongPtr(hMain, GWLP_USERDATA);
					o->select.AddMenuItem(buf);
				}
				EndDialog(h, TRUE);
			}
		}
	};

	template<class T, class D>struct  __more_than_one__
	{
		bool operator()(T &t, D &d)
		{
			++d;
			return d > 1;
		}
	};

	struct DelOkBtn
	{
		static const int width = 120;
		static const int height = 30;
		static const int ID = IDOK;
		wchar_t *Title(){return L"Применить";}
		template<class Owner>void BtnHandler(Owner &owner, HWND h)
		{
			if(TestPassword<Owner::Table>()(h))
			{
				wchar_t buf[128];
				GetWindowText(owner.items.get<DlgItem<NameParam> >().hWnd, buf, dimention_of(buf));
				if(0 == buf[0])
				{
					MessageBox(h, L"Введите название типоразмера", L"Ошибка!!!", MB_ICONERROR);
					return;
				}
				CBase base(ParametersBase().name());
				if(base.IsOpen())
				{
					int countItems = 0;
					Select<Owner::Table>(base).ExecuteLoop<__more_than_one__>(countItems);
					if(countItems < 2)
					{
						MessageBox(h, L"В базе должно быть больше одного типоразмера", L"Предупреждение!!!", MB_ICONEXCLAMATION);
						return;
					}					
					wchar_t buf2[128];
					wcsncpy_s(buf2, buf, wcslen(buf));

					HWND hMain = GetParent(h);
					MainWindow *o = (MainWindow *)GetWindowLongPtr(hMain, GWLP_USERDATA);
					o->select.DelMenuItem(buf);

					if(buf[0] != 0)
					{
						NameParam n;
						n.value = buf2;
						Delete<Owner::Table>(base).eq<NameParam>(n.value).Execute();
						n.value = buf;
						int id = Select<Owner::Table>(base).eq<NameParam>(n.value).Execute();
						if(id)
						{
							Update<CurrentParametersTable>(base).set<CurrentID>(id).Where().ID(1).Execute();
							AppBase::InitTypeSizeTables(base);
						}
					}
				}
				EndDialog(h, TRUE);
			}
		}
	};
}

DO_NOT_CHECK(NameParam)
PARAM_TITLE(NameParam, L"")

DO_NOT_CHECK(TubeDiameter)
PARAM_TITLE(TubeDiameter, L"Диаметр трубы")

const wchar_t *TubeDiameterTypeSize[] ={L"48", L"60", L"73", L"89"};

template<>struct FillComboboxList<TubeDiameter>
{
	void operator()(HWND h, TubeDiameter &)
	{
		for(int i = 0; i < dimention_of(TubeDiameterTypeSize); ++i)
		{
			ComboBox_AddString(h, TubeDiameterTypeSize[i]);
		}
	}
};
template<>struct CurrentValue<TubeDiameter>
{
	void operator()(HWND h, TubeDiameter &)
	{
		const int diameter = Singleton<ParametersTable>::Instance().items.get<TubeDiameter>().value;
		wchar_t buf[4];
		_itow(diameter, buf, 10);
		
		for(int i = 0; i < dimention_of(TubeDiameterTypeSize); ++i)
		{
			if(0 == wcscmp(buf, TubeDiameterTypeSize[i]))ComboBox_SetCurSel(h, i);
		}
	}
};
template<>struct DlgSubItems<TubeDiameter, int >: ComboBoxSubItem<TubeDiameter>{};


template<int N>struct DlgSubItems<NameParam, Holder<N> >: EditItems<NameParam, 420>{};

NO_USED_MENU_ITEM(ID<ThresholdsTable>)
NO_USED_MENU_ITEM(ID<DeadAreaTable>)
NO_USED_MENU_ITEM(ID<AxesTable>)
NO_USED_MENU_ITEM(ID<MedianFiltreTable>)

NO_USED_MENU_ITEM(ID<CrossDefect<ChebyshevIParamTable>>)
NO_USED_MENU_ITEM(ID<CrossDefect<ButterworthParamTable>>)
NO_USED_MENU_ITEM(ID<CrossDefect<EllipticParamTable	 >>)

NO_USED_MENU_ITEM(ID<LongDefect<ChebyshevIParamTable>>)
NO_USED_MENU_ITEM(ID<LongDefect<ButterworthParamTable>>)
NO_USED_MENU_ITEM(ID<LongDefect<EllipticParamTable	 >>)

NO_USED_MENU_ITEM(ID<FiltersTable		 >)
NO_USED_MENU_ITEM(ID<LirParamTable		 >)
NO_USED_MENU_ITEM(ID<SpeedTable>)
NO_USED_MENU_ITEM(ID<CorecSignalTable>)
NO_USED_MENU_ITEM(ID<ColorTable>)

void AddTypeSizeDlg::Do(HWND h)
{
	ParametersTable t;
	if(TemplDialog<
		ParametersTable
		, TL::MkTlst<AddOkBtn, CancelBtn>::Result
	   >(t).Do(h, L"Добавить типоразмер")
	   )
	{
	}
}

void DelTypeSizeDlg::Do(HWND h)
{
	//ParametersTable t;
	//t.items.get<NameParam>().value = Singleton<ParametersTable>::Instance().items.get<NameParam>().value;
	if(TemplDialogList<
		ParametersTable
		, TL::MkTlst<NameParam>::Result
		, TL::MkTlst<DelOkBtn, CancelBtn>::Result
	   >(Singleton<ParametersTable>::Instance()).Do(h, L"Удалить типоразмер")
	   )
	{
	}
}

