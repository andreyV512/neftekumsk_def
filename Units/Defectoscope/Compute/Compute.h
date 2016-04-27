#pragma once
#include "App.h"

template<class T>void StatusZoneDefect(double data, double &brakThreshold, double &klass2Threshold, char &status)
{
	 if(data > brakThreshold)
	 {
		 status = StatusId<Clr<BDefect<T>>>();
	 }
	 else  if(data > klass2Threshold)
	 {
		 status = StatusId<Clr<BKlass2<T>>>();
	 }
	 else
	 {
		status = StatusId<Clr<Nominal>>();
	 }
}


//void StatusZoneThickness(int offs, double data, int zone, double &brakThreshold)[App::zon
//    , double (&klass2Threshold)[App::zonesCount], double (&nominalTreshold)[App::zonesCount], char &status);

class Compute
{
public:
	Compute();
	void Recalculation();
	void Clear();
};



