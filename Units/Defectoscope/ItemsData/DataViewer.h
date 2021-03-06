#pragma once
#include "App.h"
#include "LirItems.h"
#include "DebugMess.h"
#include "Compute.h"

struct DefectData
{
	double data[8 * 1024];
	char status[8 * 1024];
	int count;
	int zone;
	int &medianFiltreWidth;
	bool &medianFiltreOn;
	double &brackThreshold;
	double &klass2Threshold;
	DefectData(int &, bool &, double &, double &);
	void Set(int zone, unsigned start, unsigned stop, int channel, short *d, void(*)(double, double &, double &, char &), double );
};

template<class T, int channel>struct DataViewer: DefectData
{
	DataViewer()
		: DefectData(
		   Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreWidth<T> >().value
		   , Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreOn<T> >().value
		   , Singleton<ThresholdsTable>::Instance().items.get<BDefect<T> >().value
		   , Singleton<ThresholdsTable>::Instance().items.get<BKlass2<T> >().value
		)
	{}
	void Do(int zone)
	{		
	}
};

template<class T>struct OffsetSensors
	{
		void operator()(T &t, int channel, int index, unsigned &start, unsigned &stop)
		{
			 start = t.offsetsDataOfZone[index - 1];
			 stop = t.offsetsDataOfZone[index];
		}
	};

	template<>struct OffsetSensors<ABoard<Cross>::Type>
	{
		typedef ABoard<Cross>::Type T;
		void operator()(T &t, int channel, int index, unsigned &start, unsigned &stop)
		{
			if(0 == (channel & 1))
			{
			 start = t.offsetsDataOfZone[index - 1];
			 stop = t.offsetsDataOfZone[index];
			}
			else
			{
				start = t.offsetsDataOfZone2[index - 1];
			    stop = t.offsetsDataOfZone2[index];
			}
		}
	};

template<class T, int channel>struct DataViewerXXXX: DefectData
{
	DataViewerXXXX()
		: DefectData(
		   Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreWidth<T> >().value
		   , Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreOn<T> >().value
		   , Singleton<ThresholdsTable>::Instance().items.get<BDefect<T> >().value
		   , Singleton<ThresholdsTable>::Instance().items.get<BKlass2<T> >().value
		)
	{}
	void Do(int zone)
	{
		ABoard<T>::Type &item = Singleton<ABoard<T>::Type>::Instance();
        RowData &row = Singleton<RowData>::Instance();
		int startIndex = TL::IndexOf<ASignalTable::items_list, ASignal<T, channel>>::value;
		short *d = row.data[startIndex];
		double koeff = Singleton<CorecSignalTable>::Instance().items.get<Corec<ASignal<T, channel>>>().value;
		unsigned start, stop;

		OffsetSensors<ABoard<T>::Type>()(item, channel, zone + 1, start, stop);
		Set(zone, start, stop, channel, d, StatusZoneDefect<T>, koeff);
	}
};

template<int channel>struct DataViewer<Cross, channel>: DataViewerXXXX<Cross, channel>{};
template<int channel>struct DataViewer<Long, channel>: DataViewerXXXX<Long, channel>{};

