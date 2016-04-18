#pragma once
#include "App.h"
#include "AppBase.h"

struct CommonItemData
{
	//int currentOffsetFrames;
	int currentOffsetZones;
	int offsets[App::zonesCount + 2];
};

template<class T>struct ItemData;

template<>struct ItemData<Cross>: CommonItemData
{
	double buffer[App::cross_count_sensors][App::zonesCount];	///<Вычисленные данные разбитые по датчикам и зонам
	char status[App::cross_count_sensors][App::zonesCount];	///< статус данных по датчикам и зонам	
};

template<>struct ItemData<Long>: CommonItemData
{
	double buffer[App::long_count_sensors][App::zonesCount];	///<Вычисленные данные разбитые по датчикам и зонам
	char status[App::long_count_sensors][App::zonesCount];	///< статус данных по датчикам и зонам	
};

template<>struct ItemData<Thickness>//: CommonItemData 
{
	int currentOffsetZones;
	double buffer[2][App::zonesCount];	///<Вычисленные данные разбитые по датчикам и зонам
	char status[App::zonesCount];	///< статус данных по датчикам и зонам	
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct RowData
{
	int currentOffset;//счётчик данных
	int currentFrames;//счётчик времени кадров
	unsigned timeFrames[1024 * 4];//время
	int offsets[1024 * 4];//смещения данных
	short data[App::total_count_sensors][App::count_frames];
	void Clear();
	void SetData(ULONG *d, int count);
};