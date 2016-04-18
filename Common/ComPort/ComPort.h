#pragma once
#include <Windows.h>

class ComPort
{
public:
    void(*ptrStopProc)(ComPort&, unsigned char(&)[1024], int);
	HANDLE hCom, hThread, hEvent, hComEvent;
	OVERLAPPED inputOverlapped, outputOverlapped;
	static DWORD WINAPI Run(LPVOID);
	unsigned char input[1024], output[1024];
public:
	ComPort();
	~ComPort();
	bool Open(int numberComPort, int speed, int parity = NOPARITY, int stopBits = ONESTOPBIT);
	void Close();
	bool IsOpen();
	void Write(unsigned char *, int, void(*)(ComPort &, unsigned char(&)[1024], int));
	void Write(unsigned char *, int);
	void SetReceiveHandler(void(*)(ComPort &, unsigned char(&)[1024], int));
	void Do();
};