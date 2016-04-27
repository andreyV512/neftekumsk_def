#include "stdafx.h"
#include "Compute.h"
#include "USPCData.h"
#include "Dialogs.h"
#include "MedianFiltre.h"
#include "DebugMess.h"
#include "AppBase.h"
#include "ResultData.h"
#include "SelectMessage.h"
#include "CuttingTube.h"
#include "MarkingDefectiveZones.hpp"
#include "LirItems.h"
#include "USPCData.h"
#include "App.h"
#include "Common.h"
#include "SendDataAsu.h"
#include "SendDataTablo.h"
#include "LabelMessage.h"

Compute::Compute()
{
}

namespace
{
#if 1
	struct FiltreOn
	{
		 MedianFiltre (&f)[App::total_count_sensors];
		FiltreOn( MedianFiltre (&f)[App::total_count_sensors])
			: f(f)
		{}
		inline double operator()(int i, double data)
		{
			MedianFiltre &ff = f[i];
			return ff.buf[ff.Add(data)];
		}
	};
	struct FiltreOff
	{
		FiltreOff( MedianFiltre (&f)[App::total_count_sensors])
		{}
		inline double operator()(int i, double data)
		{
			return data;
		}
	};

	template<class List, class T>struct CountItem;

	template<class Head, class Tail, class T>struct CountItem<Tlst<Head, Tail>, T>
	{
		static const int value = CountItem<Tail, T>::value;
	};	

	template<class Tail, template<class, int>class W, class T, int N>struct CountItem<Tlst<W<T, N>, Tail>, T>
	{
		static const int value = 1 + CountItem<Tail, T>::value;
	};

	template<class T>struct CountItem<NullType, T>
	{
		static const int value = 0;
	};

	template<class T>struct __sel_koeff_data__
	{
		typedef T list;
		double *data;
		__sel_koeff_data__(double *data): data(data){}
	};
	template<class O, class P>struct __sel_koeff__
	{
		void operator()(O *o, P *p)
		{
			p->data[TL::IndexOf<P::list, O>::value] = o->value;
		}
	};

    template<class T>void FirstDeathZone()
{
	int firstDeathZone = Singleton<DeadAreaTable>::Instance().items.get<DeadAreaMM0>().value;

	int fullZones = int((double)firstDeathZone / App::zone_length);

	double fractional = (firstDeathZone - (fullZones * App::zone_length)) / App::zone_length; 

	T &unit = Singleton<T>::Instance();

	//unit.firstDeathZoneSamples = unit.offsetsDataOfZone[fullZones] - unit.offsetsDataOfZone[0]
    //+int((double)(unit.offsetsDataOfZone[fullZones + 1] - unit.offsetsDataOfZone[fullZones]) * fractional);
	unit.firstDeathZoneSamples = fullZones;
}

	template<class T>void SecondDeathZone()
{
	int secondDeathZone = Singleton<DeadAreaTable>::Instance().items.get<DeadAreaMM1>().value;

	int fullZones = int((double)secondDeathZone / App::zone_length);

	double fractional = (secondDeathZone - (fullZones * App::zone_length)) / App::zone_length; 

	T &unit = Singleton<T>::Instance();
	int lastZone = unit.countZones - 1;
    
	int pred = lastZone - fullZones;



	//unit.lastDeathZoneSamples = unit.offsetsDataOfZone[lastZone] - unit.offsetsDataOfZone[pred]
    //- unsigned(((double)(unit.offsetsDataOfZone[pred] - unit.offsetsDataOfZone[pred - 1]) * (1.0 - fractional)));
	unit.lastDeathZoneSamples = unit.countZones - fullZones - 1; 
}
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

	template<class T>void ComputeData(double &brakThreshold, double &klass2Threshold)
	{
		RowData &rowData = Singleton<RowData>::Instance();
		static const int startIndex = TL::IndexOf<ASignalTable::items_list, ASignal<T, 0>>::value;
		
		static const int buf_size = CountItem<ASignalTable::items_list, T>::value;
		short *data[buf_size];
		double koeff[buf_size];
		typedef Common::__select_type_sensors__<ASignalTable::items_list, ASignal, T>::Result sub_list;
		typedef TL::TypeToTypeLst<sub_list, Corec>::Result koeff_list;

		TL::foreach<koeff_list, __sel_koeff__>()
			(
			&Singleton<CorecSignalTable>::Instance().items
			, &__sel_koeff_data__<koeff_list>(koeff)
			);


		short (&raw)[App::total_count_sensors][App::count_frames] = Singleton<RowData>::Instance().data;

		for(int i = 0; i < buf_size; ++i)
		{
             data[i] = raw[startIndex + i];
		}

		MedianFiltre filte[buf_size];

		int filtrWidth = Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreWidth<T>>().value;

		bool filtrOn = Singleton<MedianFiltreTable>::Instance().items.get<MedianFiltreOn<T>>().value;

		typedef typename ABoard<T>::Type Unit;

		FirstDeathZone<Unit>();
		SecondDeathZone<Unit>();

		Unit &unit = Singleton<Unit>::Instance();

		ItemData<T> &item = Singleton<ItemData<T>>::Instance();

		if(filtrOn)
		{
			for(int i = 0; i < buf_size; ++i)
			{
				filte[i].Clear(filtrWidth);
			}

			for(int i = 0; i < buf_size; ++i)
			{
				short *ch = data[i];
				for(unsigned j = 1; j < unit.countZones && j < App::zonesCount; ++j)
				{
					double d = 0;
					char status = StatusId<Clr<Undefined>>(); 				
					//for(unsigned k = unit.offsetsDataOfZone[j - 1]; k < unit.offsetsDataOfZone[j]; ++k)
					unsigned start, stop;
					OffsetSensors<Unit>()(unit, i, j, start, stop);
					for(unsigned k = start; k < stop; ++k)
					{
						double z = ch[k];
						if(z < 0) z = -z;
						z /= App::MAX_VAL_791;	
						z *= koeff[i];
						double t = filte[i].buf[filte[i].Add(z)];
						if(d < t) d = t;

						if(j <= unit.firstDeathZoneSamples)
						{
							status = StatusId<Clr<DeathZone>>();
						}
						else if(j >= unit.lastDeathZoneSamples)
						{
							status = StatusId<Clr<DeathZone>>();
						}
						else 
							if(d > brakThreshold)
						{
							status = StatusId<Clr<BDefect<T>>>();
						}
						else  if(d > klass2Threshold)
						{
							status = StatusId<Clr<BKlass2<T>>>();
						}
						else
						{
							status = StatusId<Clr<Nominal>>();
						}
					}
					item.buffer[i][j - 1] = d;
					item.status[i][j - 1] = status;
					item.currentOffsetZones = j - 1;
				}
			}
		}
		else
		{
			for(int i = 0; i < buf_size; ++i)
			{
				short *ch = data[i];
				for(unsigned j = 1; j < unit.counterTickTime; ++j)
				{
					double d = 0;
					char status = StatusId<Clr<Undefined>>(); 
					//for(unsigned k = unit.offsetsDataOfZone[j - 1]; k < unit.offsetsDataOfZone[j]; ++k)
					unsigned start, stop;
					OffsetSensors<Unit>()(unit, i, j, start, stop);
					for(unsigned k = start; k < stop; ++k)
					{
						double z = ch[k];
						if(z < 0) z = -z;
						z /= App::MAX_VAL_791;	
						z *= koeff[i];
						if(d < z) d = z;
						if(d > brakThreshold)
						{
							status = StatusId<Clr<BDefect<T>>>();
						}
						else  if(d > klass2Threshold)
						{
							status = StatusId<Clr<BKlass2<T>>>();
						}
						else
						{
							status = StatusId<Clr<Nominal>>();
						}
					}
					item.buffer[i][j - 1] = d;
					item.status[i][j - 1] = status;
					item.currentOffsetZones = j - 1;
				}
		}

		/*
		USPC7100_ASCANDATAHEADER *b = d.ascanBuffer;
		T filtre(f);
		for(int i = 0; i < d.currentOffsetZones; ++i)
		{
			for(int j = 0; j < dimention_of(d.buffer); ++j)
			{
				d.buffer[j][i] = -1;
				d.status[j][i] = StatusId<Clr<Undefined>>();
			}
			for(int j = d.offsets[i], last = d.offsets[i + 1]; j < last; ++j)
			{
				WORD channel = b[j].Channel;
				if(channel < App::count_sensors)
				{
					double t = filtre(channel, b[j].hdr.G1Amp);
					if(t > d.buffer[channel][i])
					{
						d.buffer[channel][i] = t;						
						StatusZoneDefect<Data>(j, t, i, brakThreshold, klass2Threshold, d.status[channel][i]);
					}
				}				
			}
		}
		int buf[ App::count_sensors + 1];
		buf[App::count_sensors] = -1;
		for(int i = 0; i < d.currentOffsetZones; ++i)
		{
			for(int j = 0; j < App::count_sensors; ++j)
			{
				buf[j] = d.status[j][i];
			}
			int t = 0;
		    SelectMessage(buf, t);
			d.commonStatus[i] = t;
		}
		*/
	}
	}
	template<class T>void UndefinedItem(T &x)
	{
		//ZeroMemory(x.status, sizeof(x.status));
		//ZeroMemory(x.buffer, sizeof(x.buffer));
		x.currentOffsetZones = 0;
	}
 
	template<class O, class P>struct __recalculation__
	{
		void operator()(O *, P *)
		{			
			if(Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<O> >().value)
			{
				ComputeData<O>(
					Singleton<ThresholdsTable>::Instance().items.get<BDefect<O> >().value
					, Singleton<ThresholdsTable>::Instance().items.get<BKlass2<O> >().value
					);
			}
			else
			{
				UndefinedItem(Singleton<ItemData<O>>::Instance());
			}			
		}
	};

	template<class P>struct __recalculation__<Cross, P>
	{
		typedef Cross O;
		void operator()(O *, P *)
		{			
			ComputeData<O>(
				Singleton<ThresholdsTable>::Instance().items.get<BDefect<O> >().value
				, Singleton<ThresholdsTable>::Instance().items.get<BKlass2<O> >().value
				);
		}
	};

	bool TestCuttingZone(char status)
	{
		return false;
	}

	void CommonStatus()
	{
		int countCrossSensor = App::cross_count_sensors;
		if(60 == Singleton<ParametersTable>::Instance().items.get<TubeDiameter>().value)
		{
			countCrossSensor -= 2;
		}
		bool longOnJob      = Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Long> >().value;
		bool thicknessOnJob = Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<Thickness> >().value;

		char (&crossStatus)[App::cross_count_sensors][App::zonesCount] = Singleton<ItemData<Cross> >::Instance().status;
		char (&longStatus)[App::long_count_sensors][App::zonesCount] = Singleton<ItemData<Long> >::Instance().status;
		char (&thicknessStatus)[App::zonesCount] = Singleton<ItemData<Thickness>>::Instance().status;

		ResultViewerData &resultViewerData = Singleton<ResultViewerData>::Instance();
		char (&resultStatus)[App::zonesCount] = Singleton<ResultViewerData>::Instance().commonStatus;
		int &currentOffset = Singleton<ResultViewerData>::Instance().currentOffset;

		ZeroMemory(resultStatus, sizeof(currentOffset));

		currentOffset = 0;

		if(currentOffset < Singleton<ItemData<Cross> >::Instance().currentOffsetZones) currentOffset = Singleton<ItemData<Cross> >::Instance().currentOffsetZones;
		if(longOnJob) if(currentOffset < Singleton<ItemData<Long> >::Instance().currentOffsetZones) currentOffset = Singleton<ItemData<Long> >::Instance().currentOffsetZones;

		int buf[App::total_count_sensors + 2];

		for(int i = 0; i < currentOffset; ++i)
		{
			int k = 0;
			memset(buf, -1, sizeof(buf));

		    for(int j = 0; j < countCrossSensor; ++j)buf[k++] = crossStatus[j][i];
			if(longOnJob     ) for(int j = 0; j < App::long_count_sensors; ++j) buf[k++] = longStatus[j][i];
			if(thicknessOnJob) buf[k++] = thicknessStatus[i];
			
			int t = 0;

			SelectMessage(buf, t);

			resultStatus[i] = t;
		}
		//for(int i = currentOffset; currentOffset < countCrossSensor; ++i)
		//{
		//	resultStatus[i] = __status_label__<Clr<Undefined>>::ID;
		//}
		resultViewerData.cutting0 = 0;
		resultViewerData.cutting1 = 0;
	   resultViewerData.lengthTube = CuttingTube(
		   resultStatus
		   ,  resultViewerData.cutting0
		   ,  resultViewerData.cutting1
		   , currentOffset
		   , MarkingDefectiveZones::Do
		   );

	   dprint("cutting zones %d, %d length %d\n"
		   , resultViewerData.cutting0
		   , resultViewerData.cutting1
		   , resultViewerData.lengthTube
		   );

	   //resultViewerData.brak = resultViewerData.lengthTube > (int)thesholds.get<MimimumTubeLength>().value;

	}
#endif
   template<class O, class P>struct __clear__
	{
		void operator()(O *, P *)
		{
			UndefinedItem(Singleton<ItemData<O>>::Instance());
		}
   };
   template<class P>struct __clear__<ResultViewerData, P>
	{
		void operator()(ResultViewerData *, P *)
		{
			Singleton<ResultViewerData>::Instance().currentOffset = 0;
		}
   };
}

void Compute::Recalculation()
{	
	typedef TL::MkTlst<Cross, Long/*, Thickness*/>::Result list;
	Singleton<CrossLir>::Instance().CorrectionOffset();
	TL::foreach<list, __recalculation__>()((TL::Factory<list> *)0, (int *)0);

	CommonStatus();

	app.MainWindowUpdate();
}

void Compute::Clear()
{	
	typedef TL::MkTlst<Cross, Long, Thickness, ResultViewerData>::Result list;
	TL::foreach<list, __clear__>()((TL::Factory<list> *)0, (int *)0);

//	CommonStatus();

	app.MainWindowUpdate();
}


void RecalculationDlg::Do(HWND)
{
	Singleton<Compute>::Instance().Recalculation();
	ComputeDataAsu();
	SendDataTablo();
}