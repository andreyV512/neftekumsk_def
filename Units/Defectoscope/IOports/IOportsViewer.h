#pragma once
#include <GdiPlus.h>
#include "message.h"
class IOportsViewer
{
	HANDLE hTimer;	
public:
	HWND &hWnd;
	Gdiplus::Bitmap *&backScreen;
	bool lastTitle;
public:
	IOportsViewer(HWND &, Gdiplus::Bitmap *&);
	void Size(Gdiplus::Graphics &, int, int);
	void Start();
	void Stop();
	void MouseLDown(TLButtonDown &);
};

class IOportsViewer1
{
	HANDLE hTimer;	
public:
	HWND &hWnd;
	Gdiplus::Bitmap *&backScreen;
	bool lastTitle;
public:
	IOportsViewer1(HWND &, Gdiplus::Bitmap *&);
	void Size(Gdiplus::Graphics &, int, int);
	void Start();
	void Stop();
	void MouseLDown(TLButtonDown &);
};