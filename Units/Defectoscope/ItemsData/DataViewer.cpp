#include "stdafx.h"
#include "DataViewer.h"
#include "typelist.hpp"
#include "MedianFiltre.h"
#include "AppBase.h"
//#include "Compute.h"
#include "App.h"

namespace
{
	static const int count_buffer = 3000;
	struct PTR
	{
		//USPC7100_ASCANDATAHEADER *data[count_buffer];
	};
	struct Data
	{
		double data[count_buffer];
	};
}

DefectData::DefectData(int &filterWidth, bool &filterOn, double &brak, double &klass2)
	: medianFiltreWidth(filterWidth)
	, medianFiltreOn(filterOn)
	, brackThreshold(brak) 
	, klass2Threshold(klass2)
{}

void DefectData::Set(int zone_, unsigned start, unsigned stop, int channel, short *d, void(*ptrStatus)(double, double &, double &, char &), double koeff)
{
	zone = zone_;
	count = stop - start;
	if(count > dimention_of(status)) count = dimention_of(status);
	if(!medianFiltreOn)
	{
		for(unsigned i = start, j = 0; i < stop && j < dimention_of(status); ++i, ++j)
		{
			double t = d[i];
			if(t < 0) t = -t;
			t /= App::MAX_VAL_791;
			t *= koeff;
			data[j] = t;
			(*ptrStatus)(t, brackThreshold, klass2Threshold, status[j]);
		}
	}
	else
	{
		MedianFiltre f;
		int offs = start - medianFiltreWidth;
		if(offs < 0) offs = 0;
		double x[dimention_of(f.buf)];
		for(unsigned i = offs; i < start; ++i)
		{
			x[i - offs] = koeff * abs(d[i]) / App::MAX_VAL_791;
		}
		f.Init(medianFiltreWidth, x);

		for(unsigned i = start, j = 0; i < stop && j < dimention_of(status); ++i, ++j)
		{
			double t = d[i];
			if(t < 0) t = -t;
			t /=  App::MAX_VAL_791;
			t *= koeff;
			t = f.buf[f.Add(t)];
			data[j] = t;
			(*ptrStatus)(t, brackThreshold, klass2Threshold, status[j]);
		}
	}	
}
