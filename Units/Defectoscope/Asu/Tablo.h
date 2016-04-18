#pragma once
#include <windows.h>
#include <typeinfo> 
struct TTabloMapData
{
	LONG head;
	LONG tail;
	wchar_t data[0xf][128];
};
class Tablo
{	
	HANDLE hMapFile;
    TTabloMapData *map;
public:
	Tablo();
	//Tablo &operator=(const Tablo &);
public:	
	void Destroy(void);
	void print(wchar_t *);
};

class ViewerTablo
{
	HANDLE hMapFile;
    TTabloMapData *map;
public:
	ViewerTablo(void);
public:
	~ViewerTablo(void);
	wchar_t *get();
};
//extern Tablo &tablo;

