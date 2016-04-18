#pragma once

class Lcard791
{
	static const int FIFO = 1024;
	static const int IrqStep = 1024;
	static const int pages = 128;
	ULONG halfBuffer;
	HINSTANCE hComponent;
	void *createInstance;
	void *pI_void;
	ULONG *data, *sync;	
	bool ready;
	int SubInit(ULONG num);
public:
	int Init();	
	void Destroy();
	bool InitChannel(int (&channels)[App::total_count_sensors], int (&amplification)[App::total_count_sensors], int rate, ULONG bufSize);
	bool Start();
	void Stop();
	int Read(ULONG *&);
	double ReadAsunc(int);
};