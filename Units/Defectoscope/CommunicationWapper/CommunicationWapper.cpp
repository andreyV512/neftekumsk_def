#include "stdafx.h"
#include "CommunicationWapper.h"
#include "App.h"
#include "AppBase.h"
#include "TypeSize\TypeSizeProtocol.h"
#include "StopCycle\StopCycleProtocol.h"
#include "Strobes\StrobesProtocol.h"
#include "GetHostByName.h"


//struct IntToIPAddr
//{
//	wchar_t buf[16];
//	wchar_t *operator()(int addr)
//	{
//		wsprintf(buf, L"%d.%d.%d.%d"
//		, ((unsigned char *)&addr)[3]
//		, ((unsigned char *)&addr)[2]
//		, ((unsigned char *)&addr)[1]
//		, ((unsigned char *)&addr)[0]
//		);
//		return buf;
//	}
//};


void TcpClientTypeSize()
{
	wchar_t *x = Singleton<ParametersTable>::Instance().items.get<NameParam>().value;
	TypeSizeProtocol::Client::Do(
		//IntToIPAddr()(Singleton<IPAddressTable>::Instance().items.get<IPAddr>().value)
		GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
		,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
		, x
		);
}

void TcpClientStop()
{
	StopCycleProtocol::Client::Do(
		//IntToIPAddr()(Singleton<IPAddressTable>::Instance().items.get<IPAddr>().value)
		GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
		,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
		);
}
//DWORD WINAPI ListenDo(LPVOID self_)
//QueueUserWorkItem(ListenDo, NULL, WT_EXECUTELONGFUNCTION);
DWORD WINAPI  TcpClientSetStrobe_Do(LPVOID)
{
	//unsigned (&data)[App::zonesCount + 2] = Singleton<ThicknessLir>::Instance().times;
	StrobesProtocol::Client().Do(
		//IntToIPAddr()(Singleton<IPAddressTable>::Instance().items.get<IPAddr>().value)
		GetHostByName()(Singleton<IPAddressTable>::Instance().items.get<IPName>().value)
		,	Singleton<IPAddressTable>::Instance().items.get<IPPort>().value
		);
		//, data, dimention_of(data));
	return 0;
}

void TcpClientSetStrobe::Do()
{
	QueueUserWorkItem(TcpClientSetStrobe_Do, NULL, WT_EXECUTELONGFUNCTION);
}