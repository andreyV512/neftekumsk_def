#include "stdafx.h"
#include "Communication.h"
#include <stdio.h>
#include <Windows.h>
#include "ComPort.h"
#include "Crc.h"
#include "App.h"
#include "DebugMess.h"

namespace Communication
{
	static const int numberAbonent = 1;
	volatile bool result;
	HANDLE hEvent;
	ComPort &port = Singleton<ComPort>::Instance();
	void Init()
	{
		result = false;
		hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	void Destroy()
	{
		CloseHandle(hEvent);
	}
	struct TestComm
	{
		static void Receive(ComPort &p, unsigned char(&b)[1024], int len)
		{
			dprint("number com port  %d  %d\n", b[1], b[2]);
			 result = 1 == b[1] && 0 == Crc16(b, b[0]);
			 SetEvent(hEvent);
			 dprint("TestCom::Receive Rvent\n");
		}
		static void TestReceive(ComPort &p, unsigned char(&b)[1024], int len)
		{
			p.Write(b, len);
		}
	};
	


bool TestCommunication1()
{
	unsigned char query[] = {5, 1, 1, 0, 0};
	static const int len = sizeof(query);

	*(short *)&query[len - 2] = Crc16(query, len - 2);
	result = false;

	for(int i = 0; i < 5 && !result; ++i) 
	{
		port.Write(query, len, &TestComm::Receive);
		WaitForSingleObject(hEvent, 3000);
	}

	port.SetReceiveHandler(TestComm::TestReceive);

	return result;
}

#pragma pack(1)
struct NumberTubeReply
{
	unsigned char size;
	unsigned char numAbonent;
	unsigned char codeFunc;
	 
	char numberTube[8];
	short signTube;
	short reserve;
	
	unsigned short crc;
};

bool QueryNumberTube2(char (&numberTube)[5])
{
	unsigned char query[] = {5, 1, 2, 0, 0};
	static const int len = sizeof(query);

	*(short *)&query[len - 2] = Crc16(query, len - 2);
	result = false;

	for(int i = 0; i < 5 && !result; ++i) 
	{
		port.Write(query, len, &TestComm::Receive);
		WaitForSingleObject(hEvent, 3000);
	}

	bool b = result;
	if(b)
	{
		NumberTubeReply &reply = *(NumberTubeReply *)port.input;
		if(1 == reply.numAbonent)
		{
			char *c = (char *)&port.input[3];
			memmove(numberTube, c, 5);

			char buf[6];					   //вывод в строку 
			memmove(buf, numberTube, 5);	   //статуса
			buf[5] = 0;						   //главного окна
			wchar_t wbuf[64];				   //номера трубы
			wsprintf(wbuf, L"%S", buf);		   //
			app.MainWindowBottomLabel(App::status_number_tube, wbuf);//
			app.MainWindowBottomLabel(App::status_tablo, L"");//
		}
	}

	port.SetReceiveHandler(TestComm::TestReceive);

	return b;
}
#pragma warning(disable : 4996)
#pragma pack(1)
struct ControlResulQuery
{
	unsigned char size;
	unsigned char numAbonent;
	unsigned char codeFunc;
	 
	char numberTube[5];

	unsigned char result;
	unsigned char solidMuf;
	unsigned char solidTube;
	unsigned char cut0;
	unsigned char stateCut0;
	unsigned char cut1;
	unsigned char stateCut1;
	unsigned char length;
};

bool TransferControlResul3(
		char (&numberTube)[5]

		, int length

		, int cuttingArea1
		, int cuttingArea2

		, int resultControlCommon

		, unsigned char *zones
		)
{
	unsigned char p[1024];
	p[0]=3+5+8+length+2;
	p[1]=1;
	p[2]=3;
	strncpy((char *)p+3, numberTube, 5);
	p[8]=resultControlCommon;
	p[9]=2;
	p[10]=2;
	p[11]=cuttingArea1;
	p[12]=0;
	p[13]=cuttingArea2;
	p[14]=0;
	p[15]=length;
	for (int i=0; i<length;i++)
		p[16+i]=zones[i];
	
	*(short *)&p[3+5+8+length] = Crc16(p, 3+5+8+length);

#if 0
    FILE *f = fopen(".\\comPort.txt", "w");
	if(NULL != f)
	{
		for(int i = 0; i < 200; ++i)
		{
			char xxx[128];
			sprintf(xxx, "%d\n", buf[i]);
			int len = strlen(xxx);
			fwrite(xxx, 1, len, f);
		}
		fclose(f);
	}
	
	f = fopen(".\\comPortBin.bin", "wb");
	if(NULL != f)
	{
			fwrite(buf, 1, 200, f);
		fclose(f);
	}
#endif
   
	result = false;
	for(int i = 0; i < 5 && !result; ++i) 
	{
		dprint("Sent to ComPort %d\n", i);
		port.Write(p, 3+5+8+length + 2, &TestComm::Receive);
		WaitForSingleObject(hEvent, 3000);
	}
	port.SetReceiveHandler(TestComm::TestReceive);

	return result;
}

void AsuTestCommunication1()
{
	port.SetReceiveHandler(TestComm::TestReceive);
}
void AsuQueryResultControl2(ComPort &p){}
void AsuTransferControlParameters4(ComPort &p){}
///-------------------------------------------------------
}
