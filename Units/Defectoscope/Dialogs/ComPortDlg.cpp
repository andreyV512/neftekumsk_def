#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"
#include "AnalogBoard.h"

namespace
{
template<int N>struct BaudRateX;
#define BAUDRATE(n)template<>struct BaudRateX<n>\
{\
	static const int value = CBR_##n;\
	wchar_t *Name(){return L#n;}\
};

BAUDRATE(110	  )
BAUDRATE(300	  )
BAUDRATE(600	  )
BAUDRATE(1200  )
BAUDRATE(2400  )
BAUDRATE(4800  )
BAUDRATE(9600  )
BAUDRATE(14400 )
BAUDRATE(19200 )
BAUDRATE(38400 )
BAUDRATE(57600 )
BAUDRATE(115200)
BAUDRATE(128000)
BAUDRATE(256000)

typedef TL::MkTlst<
BaudRateX<110	>
, BaudRateX<300	>
, BaudRateX<600	>
, BaudRateX<1200  >
, BaudRateX<2400  >
, BaudRateX<4800  >
, BaudRateX<9600  >
, BaudRateX<14400 >
, BaudRateX<19200 >
, BaudRateX<38400 >
, BaudRateX<57600 >
, BaudRateX<115200>
, BaudRateX<128000>
, BaudRateX<256000>
>::Result baud_rate_list;

template<int >struct ParityX;
#define PARITY(n)template<>struct ParityX<n>\
{\
	static const int value = n;\
	wchar_t *Name(){return L#n;}\
};

PARITY(EVENPARITY )
PARITY(MARKPARITY )
PARITY(NOPARITY	  )
PARITY(ODDPARITY  )
PARITY(SPACEPARITY)

typedef TL::MkTlst<
ParityX<EVENPARITY 	 >
, ParityX<MARKPARITY >
, ParityX<NOPARITY	 > 
, ParityX<ODDPARITY  >
, ParityX<SPACEPARITY>
>::Result baud_parity_list;

template<int >struct StopBitsX;
#define STOPBITS(n)template<>struct StopBitsX<n>\
{\
	static const int value = n;\
	wchar_t *Name(){return L#n;}\
};

STOPBITS(ONESTOPBIT	 )
STOPBITS(ONE5STOPBITS)
STOPBITS(TWOSTOPBITS )

typedef TL::MkTlst<
StopBitsX<ONESTOPBIT	> 
, StopBitsX<ONE5STOPBITS	>
, StopBitsX<TWOSTOPBITS 	>
>::Result baud_stop_bits_list;

template<class O, class P>struct __set_param__
{
	void operator()(O *, P *p)
	{
		ComboBox_AddString(*p, O().Name());
	}
};

template<class List>struct __data__
{
	typedef List list;
	int id;
};

template<class O, class P>struct __get_param__
{
	bool operator()(O *, P *p)
	{
		if(TL::IndexOf<P::list, O>::value == p->id)
		{
			p->id = O::value;
			return false;
		}
		return true;
	}
};

template<>struct FillComboboxList<BaudRate>
{
	void operator()(HWND h, BaudRate &)
	{
		TL::foreach<baud_rate_list, __set_param__>()((TL::Factory<baud_rate_list> *)0, &h);
	}
};

template<>struct FillComboboxList<Parity>
{
	void operator()(HWND h, Parity &)
	{
		TL::foreach<baud_parity_list, __set_param__>()((TL::Factory<baud_parity_list> *)0, &h);
	}
};

template<>struct FillComboboxList<StopBits>
{
	void operator()(HWND h, StopBits &)
	{
		TL::foreach<baud_stop_bits_list, __set_param__>()((TL::Factory<baud_stop_bits_list> *)0, &h);
	}
};

template<>struct __handler_data_widget__<DlgItem<BaudRate>, int>
{
	int operator()(HWND h)
	{
		__data__<baud_rate_list> data;
		data.id =  ComboBox_GetCurSel(h);
		TL::find<baud_rate_list, __get_param__>()((TL::Factory<baud_rate_list> *)0, &data);
		return data.id;
	}
};

template<>struct __handler_data_widget__<DlgItem<Parity>, int>
{
	int operator()(HWND h)
	{
		__data__<baud_parity_list> data;
		data.id =  ComboBox_GetCurSel(h);
		TL::find<baud_parity_list, __get_param__>()((TL::Factory<baud_parity_list> *)0, &data);
		return data.id;
	}
};

template<>struct __handler_data_widget__<DlgItem<StopBits>, int>
{
	int operator()(HWND h)
	{
		__data__<baud_stop_bits_list> data;
		data.id =  ComboBox_GetCurSel(h);
		TL::find<baud_stop_bits_list, __get_param__>()((TL::Factory<baud_stop_bits_list> *)0, &data);
		return data.id;
	}
};

template<class O, class P>struct __current_value__
{
	bool operator()(O *, P *p)
	{
		if(O::value == p->id)
		 {
			 p->id = TL::IndexOf<P::list, O>::value;
			 return false;
		 }
		 return true;
	}
};

template<>struct CurrentValue<BaudRate>
{
	void operator()(HWND h, BaudRate &)
	{
		__data__<baud_rate_list> data;
		data.id = Singleton<ComPortTable>::Instance().items.get<BaudRate>().value;
		TL::find<baud_rate_list, __current_value__>()((TL::Factory<baud_rate_list> *)0, &data);
		ComboBox_SetCurSel(h, data.id);
	}
};

template<>struct CurrentValue<Parity>
{
	void operator()(HWND h, Parity &)
	{
		__data__<baud_parity_list> data;
		data.id = Singleton<ComPortTable>::Instance().items.get<Parity>().value;
		TL::find<baud_parity_list, __current_value__>()((TL::Factory<baud_parity_list> *)0, &data);
		ComboBox_SetCurSel(h, data.id);
	}
};

template<>struct CurrentValue<StopBits>
{
	void operator()(HWND h, StopBits &)
	{
		__data__<baud_stop_bits_list> data;
		data.id = Singleton<ComPortTable>::Instance().items.get<StopBits>().value;
		TL::find<baud_stop_bits_list, __current_value__>()((TL::Factory<baud_stop_bits_list> *)0, &data);
		ComboBox_SetCurSel(h, data.id);
	}
};

PARAM_TITLE(ComPortAddr, L"Адрес ком-порта")
PARAM_TITLE(BaudRate, L"Скорость")
PARAM_TITLE(Parity, L"Чётность")
PARAM_TITLE(StopBits, L"Количество бит стоп")

DO_NOT_CHECK(ComPortAddr)
DO_NOT_CHECK(BaudRate)
DO_NOT_CHECK(Parity)
DO_NOT_CHECK(StopBits)

template<>struct DlgSubItems<ComPortAddr, int>: UpDownSubItem<ComPortAddr>{};
template<>struct DlgSubItems<BaudRate, int>: ComboBoxSubItem<BaudRate>{};
template<>struct DlgSubItems<Parity, int>: ComboBoxSubItem<Parity>{};
template<>struct DlgSubItems<StopBits, int>: ComboBoxSubItem<StopBits>{};

}

void ComPortDlg::Do(HWND h)
{
	if(TemplDialog<ComPortTable>(Singleton<ComPortTable>::Instance()).Do(h, L"Настройки ком-порта"))
	{
#pragma message("Переинициализировать КОМ ПОРТ")
	}
}