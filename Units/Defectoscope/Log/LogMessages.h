﻿#pragma once

#define __double_1 " %.1f" 
#define __double_2 " %.2f"
#define __int " %d"
#define __void ""
#define __bool " %s"
#define __const_char_ptr " %s"
#define _cat(a, b) a##b

#define MESS(name, tpe, txt, bc, tc) template<>struct Row<name>\
{\
	typedef tpe type;\
	static const unsigned backColor = bc;\
    static const unsigned textColor = tc;\
	static const char *mess(){return _cat(txt, __##tpe);}\
};
#define MESS1(name, tpe, txt, bc, tc) template<>struct Row<name>\
{\
	typedef tpe type;\
	static const unsigned backColor = bc;\
    static const unsigned textColor = tc;\
	static const char *mess(){return _cat(txt, __##tpe##_1);}\
};
#define MESS2(name, tpe, txt, bc, tc) template<>struct Row<name>\
{\
	typedef tpe type;\
	static const unsigned backColor = bc;\
    static const unsigned textColor = tc;\
	static const char *mess(){return _cat(txt, __##tpe##_2);}\
};

namespace LogMess
{
	enum ID
	{
		StartSycle
		, StopSycle
		, OverheadTemperature
		, ProgramOpen

		, TimeoutPipe
		, AutomatMode
		, SingleMode

		, NonOperatingModule

		, ProgramClosed
		, ErrStop
		, AlarmExitTubeInUnit
		, AlarmExitDirectionChainOn
		, AlarmExitInverterFaulty

		, AlarmExitRunBitIn			 
		, AlarmExitControlCircuitBitIn 
		, AlarmExitWorkBitIn			 
		, AlarmExitSycleBitIn		  

		, InfoOnWorkBitIn 
		, InfoOffWorkBitIn
		, InfoDataReceive
		, InfoOnResultBitOut
		, InfoReadyBitOut	            
		, InfoOnSycleBitIn  
		, InfoRotationalSpeedSensorsStart
		, InfoOnRunBitIn                 
		, InfoControlBitOut              
		, InfoOnSQ1BitIn	                
		, InfoPowerScannerBitOut         
		, InfoOnSQ3BitIn	                
		, InfoOffSQ1BitIn                
		, InfoOffPowerScannerBitOut         
		, InfoOffSQ3BitIn 
		, InfoUserStop
		, InfoDataCollectionComplete
		//, Info

		, SQ1BitIn           
		, SQ3BitIn           
		, StateBBitIn        
		, StateABitIn        
		, RunBitIn           
		, ControlCircuitBitIn
		, WorkBitIn          
		, SycleBitIn         
		, BaseBitIn 
		, PowerInverterBitOut
		, SpeedRLBitOut      
		, SpeedRMBitOut      
		, SpeedRHBitOut      
		, STFBitOut          
		, PowerScannerBitOut
		, ReadyBitOut        
		, ControlBitOut      
		, ResultBitOut   

		, PositionCrossUnit
		, PositionLongUnit
		, PositionThicknessUnit

		, WaitPositionCrossUnit
		, WaitPositionLongUnit
		, WaitPositionThicknessUnit

		, WaitTubeOnPosition

		, QueryNumberTube
		, ErrorNumberTube

		, TestComPortOk
		, TestComPortError
		, TestComPort

		, SetSignalStart

		, InCrossModule
		, InThickModule
		, InLongModule

		, OutCrossModule
		, OutThickModule
		, OutLongModule

		, WaitReadyFromThickness
		, ContinueCycle

		, TemperatureOverheadedSolenoid0
		, TemperatureOverheadedSolenoid1

		, HighVoltageOn
		, HighVoltageOff

		, SendStrobes

		, max_row
	};

	//typedef const char * const_char_ptr;

	static const int green = 0xff00;
	static const int blue  = 0xff0000;
	static const int black = 0x0;
	static const int white = 0xffffff;
	static const int red = 0xff;
	static const int yellow = 0xffff;

	template<int >struct Row;
	///\brief сопоставление числу сообщениея
	///\param число из перечисления ID(см. выше)
	///\param тип дополнительного параметра
	///\param сообщение
	///\param цвет фона
	///\param цвет шрифта
	MESS(StartSycle			          , void  , "Цикл старт"                     , green, black)
    MESS(StopSycle			          , void  , "Цикл стоп"				        , blue , white)
	MESS1(OverheadTemperature         , double, "Температура превышена"	        , red  , yellow)
	MESS(ProgramOpen		          , void  , "Программа открыта"              , black, white)
							          
	MESS(TimeoutPipe		          , void  , "Превышенно время ожидания", red  , yellow)
							          
	MESS(AutomatMode		          , void  , "Режим \"Автоматический\""		, blue , white)
	MESS(SingleMode			          , void  , "Режим \"Одиночное измерение\""	, blue , white)

	MESS(PositionCrossUnit         , void , "Готовность поперечного модуля", green, black)
    MESS(PositionThicknessUnit	  , void  , "Готовность модуля толщины", green, black)
	MESS(PositionLongUnit         , void  , "Готовность продольного модуля", green, black)

	MESS(NonOperatingModule         , void  , "Модули дефектоскопа в нерабочем положении", red  , yellow)

	MESS(WaitPositionCrossUnit         , void , "Ожидание позиционирования поперечного модуля", green, yellow)
    MESS(WaitPositionThicknessUnit	  , void  , "Ожидание позиционирования модуля толщины", green, yellow)
	MESS(WaitPositionLongUnit         , void  , "Ожидание позиционирования продольного модуля", green, yellow)
	MESS(WaitReadyFromThickness, void, "Ожидание готовности толщиномера", blue, red)

	MESS(TestComPortOk   , void, "Тестирование ком-порта прошло успешно", green, blue)
	MESS(TestComPortError, void, "Произошла ошибка при тестировании ком-порта", red, yellow)
	MESS(TestComPort, void, "Тестирование ком-порта", blue, white);

	MESS(WaitTubeOnPosition           , void ,  "Ожидание трубы перед позицией", blue, white)

	MESS(QueryNumberTube             , void, "Запрос номера трубы", blue, white)
	MESS(ErrorNumberTube             , void, "АСУ на запрос номера трубы не отвечает", red, blue)
	MESS(SetSignalStart, void, "Установлен сигнал \"Пуск\"", green, blue)

	MESS(ContinueCycle, void, "Для продолжения нажмите кнопку \"Цикл\"", red, blue)

	MESS(InCrossModule , void, "Труба вошла в модуль поперечного контроля", green, white)
	MESS(InThickModule , void, "Труба вошла в модуль толщенометрии"       , green, white)
	MESS(InLongModule  , void, "Труба вошла в модуль продольного контроля", green, white)
    MESS(OutCrossModule, void, "Труба вышла из модуля поперечного контроля", blue, white)
	MESS(OutThickModule, void, "Труба вышла из модуля толщенометрии"       , blue, white)
	MESS(OutLongModule , void, "Труба вышла из модуля продольного контроля", blue, white)
							          
	MESS(ProgramClosed		          , void  , "Программа закрыта"	, red  , yellow)
							          
	MESS(ErrStop                      , void  , "Прерывание цикла измерения", red, yellow)

	MESS(AlarmExitTubeInUnit          , void, "Труба в модуле, выполните выгон", red  , yellow)
	MESS(AlarmExitDirectionChainOn    , void, "Включите цепи управления", red  , yellow)
	MESS(AlarmExitInverterFaulty      , void, "Частотный преодразователь не включён", red  , yellow)

	MESS(AlarmExitRunBitIn			  , void, "Ошибка частотного преобразователя\"", red  , yellow)
	MESS(AlarmExitControlCircuitBitIn , void, "Нет сигнала \"Цепи управления\""	   , red  , yellow)
	MESS(AlarmExitWorkBitIn			  , void, "Нет сигнала \"Работа\""			   , red  , yellow)
	MESS(AlarmExitSycleBitIn		  , void, "Нет сигнала \"Цикл\""			   , red  , yellow)


	MESS(InfoOnWorkBitIn                , void, "Ожидание сигнала \"Работа\""					  , blue , white)
	MESS(InfoOffWorkBitIn				, void, "Ожидание снятия сигнала \"Работа\""			  , green, blue)
	MESS(InfoDataReceive				, void, "Данные с дефектоскопа приняты"                   , blue, yellow)
	MESS(InfoReadyBitOut	            , void, "Выставлен сигнал \"Готовность\""				  , blue , white)
	MESS(InfoOnResultBitOut             , void, "Выставлен сигнал \"Результат\""                 , blue , white)
	MESS(InfoOnSycleBitIn               , void, "Ожидание сигнала \"Цикл\""					  , blue , white)
	MESS(InfoRotationalSpeedSensorsStart, void, "Включение вращения модуля датчиков сканирования", blue , white)
	MESS(InfoOnRunBitIn                 , void, "Ожидание раскрутки модуля датчиков сканирования", blue , white)
	MESS(InfoControlBitOut              , void, "Выставлен сигнал \"Контроль\""				  , blue , white)
	MESS(InfoOnSQ1BitIn	                , void, "Ожидание трубы на датчике SQ1"				  , blue , white)
	MESS(InfoPowerScannerBitOut         , void, "Включение сканирующего устройства"			  , blue , white)
	MESS(InfoOnSQ3BitIn	                , void, "Ожидание трубы на датчике SQ3"				  , blue , white)
	MESS(InfoOffSQ1BitIn                , void, "Ожидание съезда трубы с датчика SQ1"			  , blue , white)
	MESS(InfoOffPowerScannerBitOut      , void, "Отключение сканирующего устройства"		      , blue , white)
	MESS(InfoOffSQ3BitIn                , void, "Ожидание съезда трубы с датчика SQ3"			  , blue , white)
	MESS(InfoUserStop					, void, "Оператор вышел из цикла сбора данных"			  , red  , yellow)

	MESS(InfoDataCollectionComplete		, void, "Сбор данных закончен"                           , green, white);

	MESS(SQ1BitIn             , bool, "SQ1BitIn            ", white, black)
	MESS(SQ3BitIn             , bool, "SQ3BitIn            ", white, black)
	MESS(StateBBitIn          , bool, "StateBBitIn         ", white, black)
	MESS(StateABitIn          , bool, "StateABitIn         ", white, black)
	MESS(RunBitIn             , bool, "RunBitIn            ", white, black)
	MESS(ControlCircuitBitIn  , bool, "ControlCircuitBitIn ", white, black)
	MESS(WorkBitIn            , bool, "WorkBitIn           ", white, black)
	MESS(SycleBitIn           , bool, "SycleBitIn          ", white, black)
	MESS(BaseBitIn 			  , bool, "BaseBitIn 		   ", white, black)
	MESS(PowerInverterBitOut  , bool, "PowerInverterBitOut ", white, black)
	MESS(SpeedRLBitOut        , bool, "SpeedRLBitOut       ", white, black)
	MESS(SpeedRMBitOut        , bool, "SpeedRMBitOut       ", white, black)
	MESS(SpeedRHBitOut        , bool, "SpeedRHBitOut       ", white, black)
	MESS(STFBitOut            , bool, "STFBitOut           ", white, black)
	MESS(PowerScannerBitOut	  , bool, "PowerScannerBitOut  ", white, black)
	MESS(ReadyBitOut          , bool, "ReadyBitOut         ", white, black)
	MESS(ControlBitOut        , bool, "ControlBitOut       ", white, black)
	MESS(ResultBitOut   	  , bool, "ResultBitOut   	 "  , white, black)

	MESS(TemperatureOverheadedSolenoid0, void, "Превышена температура на соленоиде 1", red, yellow)
	MESS(TemperatureOverheadedSolenoid1, void, "Превышена температура на соленоиде 2", red, yellow)

	MESS(HighVoltageOn , void, "Включено высокое напряжение", red, yellow)
	MESS(HighVoltageOff, void, "Высокое напряжение отключено", white, blue)

	MESS(SendStrobes, void, "Ожидание результата от толщиномера",  blue, yellow)

	class FactoryMessages
	{
		struct Inner;
		Inner &inner;
		FactoryMessages();
	public:
		void StartTime();
		bool Color(int i, unsigned &backColor, unsigned &textColor);
		bool Text(int i, char *buf, double val);
		static FactoryMessages &Instance();
	};
}
#undef MESS
#undef MESS1
#undef MESS2
#undef __double_1 
#undef __double_2 
#undef __int 
#undef __void 
#undef _cat


