#include "stdafx.h"
#include "USPCData.h"
#include "ConstData.h"
#include "AppBase.h"
#include <math.h>
#include "DebugMess.h"
#include <Mmsystem.h>
#define _USE_MATH_DEFINES
#include <cmath>

#pragma comment(lib, "Winmm.lib")


void RowData::Clear()
{
	currentOffset = 0;
	currentFrames = 0;
	//dprint("Clear rOwData\n");
}

void RowData::SetData(ULONG *d, int count)
{
	//dprint("count %d\n", count);
	count /= App::total_count_sensors;
	if(count + currentOffset < App::count_frames)
	{
		for(int i = 0; i < count; ++i)
		{
			for(int j = 0; j < App::total_count_sensors; ++j)
			{
				int k = i * App::total_count_sensors;
			   data[j][currentOffset + i] = (short)d[k + j];
			   //dprint("%d %d\n", j, (short)d[k + j]);
			}
		}
		currentOffset += count;
		offsets[currentFrames] = currentOffset;
		timeFrames[currentFrames] = timeGetTime();
		++currentFrames;
	}
}

