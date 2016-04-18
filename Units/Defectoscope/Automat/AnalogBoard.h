#pragma once
#include "Config.h"
#include "Lir.h"

#if defined(L502OFF)&& defined(L791OFF)
class AnalogBoard
{
public:
	AnalogBoard(){}
	bool Init(){return false;}
	void Destroy(){}
	int SetupParams();
	int Start(){return 0;}
	int Stop(){return 0;}
	int Read(ULONG *&){return 0;}
	double ReadAsunc(int){return 0;};
	int InitChannel(int(&)[App::total_count_sensors], int(&)[App::total_count_sensors], int, int){return 0;}
	static void Do(Lir::Data &){}
};
#elif !defined(L502OFF)
#include "L502Unit.h"
class SolidGroup : public L502Unit{};
#elif !defined(L791OFF)
//#include "..\..\..\Common\Lcard791\Lcard791.h"
//E:\Work\Defectoscope9000\Common\\Lcard791.h
//E:\Work\Defectoscope9000\Units\Defectoscope\Automat\AnalogBoard.h
#include "Lcard791.h"
class AnalogBoard : public Lcard791
{
public:
	int SetupParams();
};
#endif
