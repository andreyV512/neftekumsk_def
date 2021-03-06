#pragma once
#include "SelectTypeSizeList.h"
#include <windows.h>
#include "message.h"
#include "TopLabelViewer.h"
#include "CheckBoxWidget.h"
#include "MainWindowToolBar.h"
#include <CommCtrl.h>
#include "ThicknessViewer.h"
#include "CrossViewer.h"
#include "LongViewer.h"
#include "ResultViewer.h"
#include "MessagesInterface.h"

/*
template<int N>class TestCheckBoxX
{
protected:
	void Command(TCommand &m, bool b)
	{
		MainWindow *o = (MainWindow *) GetWindowLongPtr(m.hwnd, GWLP_USERDATA);
		wchar_t text[128];
		wsprintf(text, L"������� %d   %s "
			, N
			, b ? L"�������"
			    : L"��������"
			);
		SendMessage(o->hStatusWindow, SB_SETTEXT, N, (LONG)text);
	}
	bool Init(HWND h)
	{
		bool b = true;
		HWND hParent = GetParent(GetParent(h));
		MainWindow *o = (MainWindow *) GetWindowLongPtr(hParent, GWLP_USERDATA);
		wchar_t text[128];
		wsprintf(text, L"������� %d   %s "
			, N
			, b ? L"�������"
			    : L"��������"
			);
		SendMessage(o->hStatusWindow, SB_SETTEXT, N, (LONG)text);
		return b;
	}
};
*/

template<class T, class Parent>struct OnTheJobCheckBox
{
protected:
	void Command(TCommand &m, bool b)
	{
		Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<T> >().value = b;
		Parent::CheckBoxStateStoreInBase();
	}
	bool Init(HWND h)
	{		
		return Singleton<OnTheJobTable>::Instance().items.get<OnTheJob<T> >().value;
	}
};
struct OnSycleCheckBox
{
protected:
	void Command(TCommand &m, bool b)
	{
		value = b;
	}
	bool Init(HWND h)
	{		
		return value = true;
	}
public:
	bool value;
};

class MainWindow
{
public:
	HWND hWnd;
	HWND hStatusWindow;
	MainWindowToolBar toolBar;
	//CheckBoxWidget<TestCheckBoxX<0> > testCheckBox0;
	//CheckBoxWidget<TestCheckBoxX<1> > testCheckBox1;
	//CheckBoxWidget<TestCheckBoxX<2> > testCheckBox2;
	//CheckBoxWidget<OnTheJobCheckBox<Cross    , MainWindow> > crossCheckBox;
	CheckBoxWidget<OnTheJobCheckBox<Long     , MainWindow> > longCheckBox;
	CheckBoxWidget<OnTheJobCheckBox<Thickness, MainWindow> > thicknessCheckBox;
	CheckBoxWidget<OnSycleCheckBox> sycleCheckBox;
	HWND hCommonTube, hBrakTube;
	TopLabelViewer topLabelViewer;
	SelectTypeSizeList select;
	typedef TL::MkTlst<
		CrossViewer
		, LongViewer
		, ThicknessViewer
		, ResultViewer
	>::Result viewers_list;
	TL::Factory<viewers_list> viewers;
	void operator()(TSize &);
	void operator()(TCommand &);
	void operator()(TGetMinMaxInfo &);
	unsigned operator()(TCreate &);
	void operator()(TDestroy &);
	void operator()(TMessage &);
	void operator()(TRButtonDown &);
	void operator()(TMouseWell &);
	static void CheckBoxStateStoreInBase();
};
