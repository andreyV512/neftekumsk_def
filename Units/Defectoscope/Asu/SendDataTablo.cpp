#include "stdafx.h"
#include "SendDataTablo.h"
#include <stdio.h>
#include "ResultData.h"
#include "Tablo.h"
#include "App.h"
#include "DebugMess.h"
#include "SendDataAsu.h"

namespace
{
	char buf[128];
}

#pragma warning(disable : 4996)
void  ComputeDataTablo()
{
	ResultViewerData r = Singleton<ResultViewerData>::Instance();
	char cut0[16];
	sprintf_s(cut0, "%d",  r.cutting0);
	char cut1[16];
	sprintf_s(cut1, "%d",  r.cutting1);
	
	char numberTube[6];
	strncpy_s(numberTube, r.numberTube, 5);

	char *klass = Asu::klass3 == r.klass ? "3 klass" :  Asu::klass2 == r.klass ? "2 klass" : "1 klass";

	if(r.brak)
	{
		sprintf_s(buf, "%s  Brak"
			, numberTube
			);
	}
	else if(r.cutting0 > 0 && r.cutting1 > 0)
	{	
	sprintf_s(
		buf, "%s %s %s %s"
		, numberTube
		, klass
		, cut0
		, cut1
		);
	}
	else if(r.cutting0 == 0 && r.cutting1 == 0)
	{
		sprintf_s(
		buf, "%s %s"
		, numberTube	
		, klass
		);
	}
	else if(r.cutting0 == 0 && r.cutting1 > 0)
	{
		sprintf_s(
		buf, "%s %s %s"
		, numberTube	
		, klass
		, cut1
		);
	}
	else if(r.cutting0 > 0 && r.cutting1 == 0)
	{
		sprintf_s(
		buf, "%s %s %s"
		, numberTube
		, klass
		, cut0
		);
	}
	wchar_t wbuf[sizeof(buf)];
	mbstowcs(wbuf, buf, sizeof(buf));

	app.MainWindowBottomLabel(App::status_tablo, wbuf);//в строку статуса глав.окна	
}

void SendDataTablo()
{
	FILE *f;
    if(0 == fopen_s(&f, ".\\Stroka.txt", "w"))
	{
		if(EOF == fputs(buf, f))
		{
			zprint("    error\n");
		}
		fclose(f);
	}
}