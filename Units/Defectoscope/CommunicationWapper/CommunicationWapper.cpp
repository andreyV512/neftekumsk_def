#include "stdafx.h"
#include "CommunicationWapper.h"
#include "App.h"
#include "AppBase.h"
#include "TypeSize\TypeSizeProtocol.h"
#include "StopCycle\StopCycleProtocol.h"
#include "Strobes\StrobesProtocol.h"
#include "GetHostByName.h"

void TcpClientTypeSize()
{
	wchar_t *x = Singleton<ParametersTable>::Instance().items.get<NameParam>().value;
	for(int i = 0; i < 5; ++i)
	{
		if(TypeSizeProtocol::Client::Do(
			GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
			,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
			, x
			)) break;
		Sleep(500);
	}
}

void TcpClientStop()
{
	StopCycleProtocol::Client::Do(		
		GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
		,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
		);
}
DWORD WINAPI  TcpClientSetStrobe_Do(LPVOID)
{
	StrobesProtocol::Client().Do(		
		GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
		,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
		);		
	return 0;
}

void TcpClientSetStrobe::Do()
{
	QueueUserWorkItem(TcpClientSetStrobe_Do, NULL, WT_EXECUTELONGFUNCTION);
}