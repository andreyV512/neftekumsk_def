#pragma once

//#include <Windows.h>
#include <winsock2.h>
 struct Server
 {
	 typedef void (CALLBACK *Proc)(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);
	 static Proc Handler(unsigned indexProc);
 };
