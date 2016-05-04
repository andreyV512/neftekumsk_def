#pragma once
#include "config.h"
#include "WindowsPosition.h"
#include "Dialogs.h"
#include "USPCWindow.h"

namespace MainWindowMenu
{
	struct MainFile{};
	MENU_TEXT(L"Файл", TopMenu<MainFile>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct LoadDateFile: LoadDataDlg{static void Do(HWND h){if(LoadDataDlg::Do(h))RecalculationDlg::Do(h);}};
	struct SaveDateFile: StoreDataDlg{};
	struct Compute     : RecalculationDlg{};//{static void Do(HWND h){zprint("");}};
	struct MainExit{static void Do(HWND h){DestroyWindow(h);}};
	struct ClearCounter : ClearCounterDlg{};

	MENU_ITEM(L"Загрузить данные", LoadDateFile)
	MENU_ITEM(L"Сохранить данные", SaveDateFile)
	MENU_ITEM(L"Перерасчёт", Compute)
	MENU_ITEM(L"Выход", MainExit)
	MENU_ITEM(L"Сброс счётчиков труб", ClearCounter)

	template<>struct TopMenu<MainFile>
	{
		typedef TL::MkTlst<
			MenuItem<LoadDateFile>
			, MenuItem<SaveDateFile>
			, Separator<0>
			, MenuItem<Compute>
			, MenuItem<ClearCounter>
			, Separator<2>
			, MenuItem<MainExit>
		>::Result list;
	};
	//------------------------------------------------------------------------
	struct MainOptionTypeSize{};
	MENU_TEXT(L"Типоразмер", TopMenu<MainOptionTypeSize>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
	struct ThicknessTreshold {};
	struct DeadZones         : DeadZonesDlg{};//{static void Do(HWND h){zprint("");}};
	//struct AllowableThickness{static void Do(HWND h){zprint("");}};
	struct RotationalSpeed   {static void Do(HWND h){zprint("");}};
							 						
	struct MainCreateTypesize: AddTypeSizeDlg{};//{static void Do(HWND h){zprint("");}};
	struct MainDeleteTypeSize: DelTypeSizeDlg{};//{static void Do(HWND h){zprint("");}};

	struct CrossThresholdWindow__:CrossThresholdsDlg{};// {static void Do(HWND h){zprint("");}};//Common::OpenWindow<CrossThresholdWindow>{};
	struct LongThresholdWindow__ : LongThresholdsDlg{};//{static void Do(HWND h){zprint("");}};//: Common::OpenWindow<LongThresholdWindow>{};
	//struct ThicknessThresholdWindow__{static void Do(HWND h){zprint("");}};//: Common::OpenWindow<ThicknessThresholdWindow>{};
	struct MinimumTubeLength     : MinimumTubeLengthDlg{};//     {static void Do(HWND h){zprint("");}};

	struct MedianFiltre           : MedianFiltreDlg{};//{static void Do(HWND h){zprint("");}};
	struct CrossDefectFiltre : CrossDefectFiltreDlg{};//{static void Do(HWND h){zprint("");}};
	struct LongDefectFiltre : LongDefectFiltreDlg{};
	struct OffsetsTube : OffsetsTubeDlg{};

	struct LirParam: LirParamDlg{};

	template<>struct SubMenu<ThicknessTreshold>
	{
		typedef TL::TypeToTypeLst<
			typename TL::MkTlst<
			CrossThresholdWindow__
			, LongThresholdWindow__
			//, ThicknessThresholdWindow__
			, MinimumTubeLength
			>::Result 
			, MenuItem
		>::Result list;
	};
	
   // MENU_ITEM(L"Пороги отбраковки", ThicknessTreshold)
	MENU_TEXT(L"Пороги отбраковки", SubMenu<ThicknessTreshold>)
	MENU_ITEM(L"Поперечные пороги", CrossThresholdWindow__)
	MENU_ITEM(L"Продольные пороги", LongThresholdWindow__)
//	MENU_ITEM(L"Настройка лиров" , LirParam)
	//MENU_ITEM(L"Пороги толщины", ThicknessThresholdWindow__)
	MENU_ITEM(L"Минимальная длина трубы(в зонах)", MinimumTubeLength)
	MENU_ITEM(L"Мёртвые зоны", DeadZones)
	//MENU_ITEM(L"Допустимая толщина", AllowableThickness)
	MENU_ITEM(L"Скорость вращения", RotationalSpeed)
	MENU_ITEM(L"Создать типоразмер", MainCreateTypesize)
	MENU_ITEM(L"Удалить типоразмер", MainDeleteTypeSize)

	
	MENU_ITEM(L"Медианный фильтр", MedianFiltre)
	MENU_ITEM(L"Фильтр продольных  дефектов", LongDefectFiltre  )
	MENU_ITEM(L"Фильтр пореречных дефектов", CrossDefectFiltre   )

	MENU_ITEM(L"Смещение измерений", OffsetsTube)

	struct FiltersItem{};
/*
	template<>struct SubMenu<FiltersItem>
	{
		typedef TL::TypeToTypeLst<
			typename TL::MkTlst<
			MedianFiltre
			, LongDefectFiltre
			, CrossDefectFiltre
			>::Result 
			, MenuItem
		>::Result list;
	};
	*/

	MENU_TEXT(L"Фильтры", SubMenu<FiltersItem>)

	template<>struct TopMenu<MainOptionTypeSize>
	{
		typedef TL::MkTlst<
		     SubMenu<ThicknessTreshold>
			, MenuItem<DeadZones>
			, MenuItem<OffsetsTube>
			, MenuItem<MedianFiltre>
			, Separator<0>
			, MenuItem<MainCreateTypesize>
			, MenuItem<MainDeleteTypeSize>
		>::Result list;
	 };
	//--------------------------------------------------------------------------------
	struct Options{};
	MENU_TEXT(L"Настройки", TopMenu<Options>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowPosition    : WindowPositionDlg<MainWindow>{};//{static void Do(HWND h){zprint("");}};
	struct IOportsView       : IOportsDlg{};
	struct IOportsView1       : IOports1Dlg{};

	MENU_ITEM(L"Сохранить координаты окна", WindowPosition)
    MENU_ITEM(L"Просмотр дискретных портов (плата 0)", IOportsView)
	MENU_ITEM(L"Просмотр дискретных портов (плата 1)", IOportsView1)

	template<>struct TopMenu<Options>
	{
		typedef TL::MkTlst<
			MenuItem<WindowPosition>
			, Separator<0>
			, MenuItem<IOportsView>
			, MenuItem<IOportsView1>
		>::Result list;		
	};
	//-------------------------------------------------------------------------------------------------------
	struct Setting{};
	MENU_TEXT(L"Установка", TopMenu<Setting>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct AnalogPlate            {static void Do(HWND h){zprint("");}};//: Common::OpenWindow<USPCWindow>{};//{static void Do(HWND h){zprint("");}};
	struct ASignalCross: ASignalCrossDlg{};
	struct ASignalLong : ASignalLongDlg{};
	struct GainCross : GainCrossDlg{};
	struct GainLong : GainLongDlg{};
	struct DiscretePlate	      {static void Do(HWND h){zprint("");}};
	struct DiscretePlateInputs0    : Inputs0Dlg{};//{static void Do(HWND h){zprint("");}};
	struct DiscretePlateOutputs0   : Outputs0Dlg{};//{static void Do(HWND h){zprint("");}};
	struct DiscretePlateInputs1   : Inputs1Dlg{};//{static void Do(HWND h){zprint("");}};
	struct DiscretePlateOutputs1   : Outputs1Dlg{};//{static void Do(HWND h){zprint("");}};

	struct AnalogBoard    : AnalogBoardDlg{};//{static void Do(HWND h){zprint("");}};

	struct ColorItems             : ColorItemsDlg{};//{static void Do(HWND h){zprint("");}};
	struct DiscretePlateDescriptor: Descriptor1730Dlg{};//{static void Do(HWND h){zprint("");}};
	//struct Coefficient            {static void Do(HWND h){zprint("");}};
	//struct MedianFiltre           : MedianFiltreDlg{};//{static void Do(HWND h){zprint("");}};
	///struct Signal                 {static void Do(HWND h){zprint("");}};
	//struct ACFBorder              {static void Do(HWND h){zprint("");}};
	struct ComPort : ComPortDlg{};
	struct Tcp : TcpDlg{};
	//struct BaseLir: BaseLirDlg{};// {static void Do(HWND h){zprint("");}};
	struct LirDescriptor: LirDescriptorDlg{};
	struct LirParameters: LirParamDlg{};

	struct ControlItemOffset   : ControlItemOffsetDlg{};
	struct ControlItemThreahold{static void Do(HWND h){zprint("");}};

	struct LirMenuItem {static void Do(HWND h){zprint("");}};
	//struct AdditionalChennel {static void Do(HWND h){zprint("");}};
	
	MENU_TEXT(L"Дискретная плата", SubMenu<DiscretePlate>)
	MENU_TEXT(L"Аналогоавя плата", SubMenu<AnalogPlate>)
	MENU_TEXT(L"Настройка датчиков ЛИР",  SubMenu<LirMenuItem>)

	MENU_ITEM(L"Входные поперечные порты аналоговой платы", ASignalCross)
	MENU_ITEM(L"Входные продольные порты аналоговой платы", ASignalLong)

	MENU_ITEM(L"Усиление входных поперечных портов аналоговой платы", GainCross)
	MENU_ITEM(L"Усиление входных продольных портов аналоговой платы", GainLong)

	MENU_ITEM(L"Дополнительные настройки аналоговой платы", AnalogBoard)

	MENU_ITEM(L"Входные порты платы 0", DiscretePlateInputs0)
	MENU_ITEM(L"Выодные порты платы 0", DiscretePlateOutputs0)
	MENU_ITEM(L"Входные порты платы 1", DiscretePlateInputs1)
	MENU_ITEM(L"Выодные порты платы 1", DiscretePlateOutputs1)
	MENU_ITEM(L"Дискриптор платы", DiscretePlateDescriptor)
	//MENU_ITEM(L"Коэффициенты пересчёта", Coefficient)
	
	MENU_ITEM(L"Аналоговая плата", AnalogPlate)
//	MENU_ITEM(L"Параметры сигнала", Signal)
//	MENU_ITEM(L"Границы АЧХ", ACFBorder)
	MENU_ITEM(L"Цвета", ColorItems)

	MENU_ITEM(L"Входные порты контроля", ControlItemOffset   )
	MENU_ITEM(L"Контролируемые пороги",  ControlItemThreahold)

//	MENU_TEXT(L"Настройки ЛИР", SubMenu<LirMenuItem>)
	//MENU_ITEM(L"Тестирование окна с закладками", TestTab)

	MENU_ITEM(L"Настроечные парраметры ком-порта", ComPort)
	MENU_ITEM(L"Настроечные парраметры TCP", Tcp)
	//MENU_ITEM(L"Базовое растояние для датчиков ЛИР", BaseLir)
	MENU_ITEM(L"Дескриптор платы 1784", LirDescriptor)
	MENU_ITEM(L"Настройка импульсов", LirParameters)
	
	template<>struct SubMenu<DiscretePlate>
	{
		typedef TL::TypeToTypeLst<
			typename TL::MkTlst<DiscretePlateDescriptor
			, DiscretePlateInputs0, DiscretePlateOutputs0
			, DiscretePlateInputs1, DiscretePlateOutputs1
			>::Result 
			, MenuItem
		>::Result list;
	};
	
	template<>struct SubMenu<LirMenuItem>
	{
		typedef TL::MkTlst<
			MenuItem<LirDescriptor>
			, Separator<0>
			, MenuItem<LirParameters>
		>::Result list;
	};

	template<>struct SubMenu<AnalogPlate>
	{
		typedef TL::MkTlst<
			MenuItem<ASignalCross>
			, MenuItem<ASignalLong>
			, Separator<0>
			, MenuItem<GainCross>
			, MenuItem<GainLong>
			, Separator<1>
			, MenuItem<ControlItemOffset   >
			, MenuItem<ControlItemThreahold>
			, Separator<2>
			, MenuItem<AnalogBoard>
		>::Result list;		
	};

	template<>struct TopMenu<Setting>
	{
		typedef TL::MkTlst<
			SubMenu<AnalogPlate>
			, SubMenu<DiscretePlate>	
			, MenuItem<ComPort>
			, MenuItem<Tcp>
		//	, MenuItem<Coefficient>
			, MenuItem<MedianFiltre>
		//	, MenuItem<Signal>
			//, MenuItem<ACFBorder>				
			, SubMenu<LirMenuItem>
			, MenuItem<ColorItems>		
		>::Result list;		
	};
	// ----------------------------------------------------------------------------------------------------
	struct MainAbout : AboutWindowDlg{};//{static void Do(HWND h){zprint("");}};
	MENU_TEXT(L"О программе", TopMenu<MainAbout>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	MENU_ITEM(L"О программе", MainAbout)

	template<>struct TopMenu<MainAbout>
	{
		typedef TL::MkTlst<
			MenuItem<MainAbout>
		>::Result list;
	};
	// --------------------------------------------------------------------------------------------------------- 
	/// \brief	Добавить меню пример использования
	//struct TestMenu{};
	//MENU_TEXT(L"TestMenu", TopMenu<TestMenu>)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//struct TestSubMenu0{};
	//struct TestSubMenu1{static void Do(HWND){zprint("");}};
	//struct TestSubMenu2{static void Do(HWND){zprint("");}};
	//struct TestSubMenu3{static void Do(HWND){zprint("");}};
	//struct TestSubMenu4{static void Do(HWND){zprint("");}};
	//
	//MENU_ITEM(L"TestSubMenu0", TestSubMenu0)
	//MENU_ITEM(L"TestSubMenu1", TestSubMenu1)
	//MENU_ITEM(L"TestSubMenu2", TestSubMenu2)
	//MENU_ITEM(L"TestSubMenu3", TestSubMenu3)
	//MENU_ITEM(L"TestSubMenu4", TestSubMenu4)
	//
	//template<>struct TopMenu<TestMenu>
	//{
	//	typedef TL::MkTlst<
	//		MenuItem<TestSubMenu0>
	//		, MenuItem<TestSubMenu1>
	//		, MenuItem<TestSubMenu2>
	//		, MenuItem<TestSubMenu3>
	//		, MenuItem<TestSubMenu4>
	//	>::Result list;
	//};
	//---------------------------------------------------------------------------------------------------------------
	typedef TL::MkTlst<
		TopMenu<MainFile>
		, TopMenu<MainOptionTypeSize>
		, TopMenu<Options>
		, TopMenu<Setting>
		, TopMenu<MainAbout>
	>::Result MainMenu;	
	}
