// TestTCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProtocolTCP\AsyncServer.h"
#include "ProtocolTCP\InitTCP.h"

int _tmain(int argc, _TCHAR* argv[])
{
	InitTcp initTcp;
	app.Init();
	AsyncServer::Create(5555);
	getchar();
	return 0;
}

