#include "stdafx.h"
#include "Tablo.h"
#include <stdio.h>

namespace {
	wchar_t name[] = L"Parallel hatch in space tablo";
	wchar_t eventName[] = L"debug event 2015 12 16 08 29 tablo";
	HANDLE h;
}
Tablo::Tablo()
{
	h = CreateEvent(NULL, TRUE, FALSE, eventName);
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security 
		PAGE_READWRITE,          // read/write access
		0,                       // max. object size 
		sizeof(TTabloMapData),                // buffer size  
		name);                 // name of mapping object

    int res = GetLastError();
	map = (TTabloMapData *) MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,                   
		0,                   
		sizeof(TTabloMapData));           

	if (map == NULL) 
	{ 
		//d_mess("Could not map view of file (%d).\n", 
		//	GetLastError()); 
		return;
	}
	if(res = 0)
	{
	map->head = 0;
	map->tail = 0;
	}
}

void Tablo::Destroy(void)
{
	UnmapViewOfFile(map);
	CloseHandle(hMapFile);
}
#pragma warning(disable : 4996)
void Tablo::print(wchar_t *c)
{
	if(NULL != map)
	{
        LONG i = InterlockedIncrement(&map->head);
		--i;
		i &= 0xf;
		wchar_t *b = map->data[i];
		SetEvent(h);
	}
}
//---------------------------------------------------------------------------------------
ViewerTablo::ViewerTablo() : map(NULL)
{	
	h = CreateEvent(NULL, TRUE, FALSE, eventName);
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security 
		PAGE_READWRITE,          // read/write access
		0,                       // max. object size 
		sizeof(TTabloMapData),                // buffer size  
		name);                 // name of mapping object
	if (hMapFile == NULL) 
	{ 
		//d_mess("Could not open file mapping object (%d).\n", 
		//	GetLastError());
		return;
	} 

	map = (TTabloMapData *)MapViewOfFile(hMapFile,    // handle to mapping object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,                    
		0,                    
		sizeof(TTabloMapData));                   

	if (map == NULL) 
	{ 
		//d_mess("Could not map view of file (%d).\n", 
		//	GetLastError()); 
		return;
	}
}
//----------------------------------------------------------------------------
ViewerTablo::~ViewerTablo()
{
	UnmapViewOfFile(map);
	CloseHandle(hMapFile);
}
//----------------------------------------------------------------------------
wchar_t *ViewerTablo::get()
{
	WaitForSingleObject(h, INFINITE);
	while(map && map->tail != map->head)
	{
		if(map->head -  map->tail > 0xf) map->tail += 0xf - 1;
		return map->data[map->tail & 0xf];
	}
	ResetEvent(h);
	return NULL;
}
//-----------------------------------------------------------------------------

//class Tablo::Initialization
//{
//	Tablo debug;
//public:
//	static Tablo &Instance(){static Tablo x; return x.debug;}
//};
//Tablo &tablo = Tablo::Initialization::Instance();

