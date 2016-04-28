#include "stdafx.h"
#include "MainWindowToolBar.h"
#include "Config.h"
#include "DebugMess.h"
#include "../Resource.h"
#include "InitToolBar.hpp"
#include "message.h"
#include "Emptywindow.h"
#include "MainWindow.h"
#include "USPCWindow.h"
#include "Common.h"
#include "App.h"
#include "..\CommunicationWapper\CommunicationWapper.h"
#include "LogBuffer.h"
#include "Communication.h"
#include "Automat.h"
#include "Device1730.h"
#include "SendDataAsu.h"
#include "CountingTube.h"
#include "SendDataTablo.h"

namespace 
{
void SycleMeashurement(HWND);//обработчик для кнопки "Циклическое измерение"

void StopMeashurement(HWND);//обработчик для кнопки "Остановка измерения"

void TresholdsViewBtn(HWND);

void TestBtn(HWND);

void SendAsuBrakBtn(HWND);

#define TOOL_LIP_TEXT(name, text)struct name{static wchar_t *Text(){return text;}};

TOOL_LIP_TEXT(ToolLipCycleBtn     , L"Цикл")
TOOL_LIP_TEXT(ToolLipReset  	  , L"Стоп")
TOOL_LIP_TEXT(ToolTresholdsViewBtn  , L"Вращение")
TOOL_LIP_TEXT(ToolTestBtn  , L"Тест Ком-порт")
TOOL_LIP_TEXT(SendAsuBrakBtnTubeBtn  , L"Брак")

  
#undef TOOL_LIP_TEXT

typedef TL::MkTlst<
  SeparatorToolbar<0>
  , ButtonToolbar<IDB_CycleBtn, SycleMeashurement, ToolLipCycleBtn>  
  , ButtonToolbar<IDB_Reset, StopMeashurement    , ToolLipReset>  
   , ButtonToolbar<IDB_TrashCanFull, SendAsuBrakBtn    , SendAsuBrakBtnTubeBtn> 
  , ButtonToolbar<IDB_QueryBtn, TestBtn             , ToolTestBtn>  
  , ButtonToolbar<IDB_SensorsUnit, TresholdsViewBtn  , ToolTresholdsViewBtn>
  , SeparatorToolbar<1>
>::Result tool_button_list;
//----------------------------------------------------------------------------------
void SycleMeashurement(HWND h)
{
  if(
	  !App::measurementOfRunning
	  && Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Thickness> >().value
	  )
  {
	  TcpClientTypeSize();
	 zprint("\n");	  
  }
  else
  {
	  SetEvent(App::ProgrammContinueEvent);	 
  }
}
//-------------------------------------------------------------------------------
bool rotationLong = true;
void TresholdsViewBtn(HWND h)
{
	if(rotationLong)Automat::RotationOn();
	else Automat::RotationOff();
	rotationLong ^= true;
}
//-----------------------------------------------------------------------------
void TestBtn(HWND)
{
	Log::Mess<LogMess::TestComPort>();
	if(Communication::TestCommunication1())
	{
		Log::Mess<LogMess::TestComPortOk>();
	}
	else
	{
		Log::Mess<LogMess::TestComPortError>();
	}
}
//----------------------------------------------------------------------------
void StopMeashurement(HWND h)
{
	zprint("");
	
	if(Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Thickness> >().value)
	{
		TcpClientStop();
	}
	SetEvent(App::ProgrammStopEvent);
}
void SendAsuBrakBtn(HWND h)
{
	if(SendAsuBrak())
	{
		ComputeDataTablo();
		MessageBox(h, L"Данные переданы", L"Сообщение!!!", MB_ICONINFORMATION);
	}
#ifdef DEBUG_ITEMS
	TcpClientSetStrobe::Do();
#endif
}
}
//--------------------------------------------------------------------------------------------
HWND MainWindowToolBar::Init(HWND h)
{
	 return hWnd = InitToolbar<tool_button_list>()(h);
}
//-------------------------------------------------------------------
void MainWindowToolBar::Size()
{
	MoveWindow(hWnd, 0, 0, 0, 0, false);
}
//----------------------------------------------------------------------------
const int MainWindowToolBar::Width()
{
	return __tool_bar_width__<tool_button_list>::value;
}
//------------------------------------------------------------------------



