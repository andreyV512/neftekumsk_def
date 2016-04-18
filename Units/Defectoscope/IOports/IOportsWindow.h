#pragma once

#include <windows.h>
#include "message.h"
#include "IOportsViewer.h"
class IOportsWindow
{
public:
	static const int width = 430;
	static const int height = 380;
	Gdiplus::Bitmap *backScreen;
	IOportsViewer viewer;
public:
	HWND hWnd;
	IOportsWindow();
	void operator()(TSize &);
	void operator()(TCommand &);
	void operator()(TGetMinMaxInfo &);
	unsigned operator()(TCreate &);
	void operator()(TDestroy &);
	void operator()(TPaint &);
	void operator()(TLButtonDown &);
	static IOportsWindow &Instance();
};

class IOportsWindow1
{
public:
	static const int width = 430;
	static const int height = 200;
	Gdiplus::Bitmap *backScreen;
	IOportsViewer1 viewer;
public:
	HWND hWnd;
	IOportsWindow1();
	void operator()(TSize &);
	void operator()(TCommand &);
	void operator()(TGetMinMaxInfo &);
	unsigned operator()(TCreate &);
	void operator()(TDestroy &);
	void operator()(TPaint &);
	void operator()(TLButtonDown &);
	static IOportsWindow1 &Instance();
};

