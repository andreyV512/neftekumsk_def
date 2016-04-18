#include "stdafx.h"
#include "Lcard791.h"
#include "Config.h"

#define INITGUID

#include <guiddef.h>
#include "include\ioctl.h"
#include "include\ifc_ldev.h"
#include "include\create.h"
#include "include\791cmd.h"
#include "DebugMess.h"

ULONG SetAmplChannel(unsigned ampl, unsigned channel)
{
	channel &= 0x1f;
	ampl    &= 0x07;
	ULONG ret = channel;
	ret |= (1 << 5);
	ret |= (ampl << 6);
	return ret;
}
#ifndef L791OFF
int Lcard791::SubInit(ULONG num)
{
	LUnknown *pIUnknown = ((CREATEFUNCPTR)createInstance)((ULONG)num);
	if(NULL == pIUnknown) return 2;
	IDaqLDevice *pI;// = (IDaqLDevice *)pI_void;
	HRESULT hr = pIUnknown->QueryInterface(IID_ILDEV, (void **)&pI); 
	pIUnknown->Release();
	if(!SUCCEEDED(hr)) return 3;
	if(INVALID_HANDLE_VALUE == pI->OpenLDevice()) return 4;
	SLOT_PAR s1;
	if(L_SUCCESS != pI->GetSlotParam(&s1)) return 5;
	if(L791 != s1.BoardType) return 6;
	PLATA_DESCR_L791 pd;
	if(L_SUCCESS != pI->ReadPlataDescr(&pd)) return 7;
	pI_void = pI;
	return 0;
}

int Lcard791::Init()
{
	hComponent = LoadLibraryA("lcomp.dll");
	int ret = 0;
	if(hComponent)
	{
		createInstance = (CREATEFUNCPTR)GetProcAddress(hComponent, "CreateInstance");
		if(NULL == createInstance) return 1;						
		for(ULONG i = 0; i < 10; ++i)
		{
			ret = SubInit(i);
			if(0 == ret) break;
		}
	}
	return ret;
}

bool Lcard791::InitChannel(int (&channels)[App::total_count_sensors], int (&amplification)[App::total_count_sensors], int rate, ULONG sizeBufADC)
{
	ADC_PAR ap = {};
	ap.t2.s_Type = L_ADC_PARAM;
	ap.t2.AutoInit = 1;
	ap.t2.dRate = 0.001 * rate;
	ap.t2.dKadr = 0;
	ap.t2.SynchroType = 0;
	ap.t2.SynchroSrc = 0;
	ap.t2.NCh = App::total_count_sensors;

	ap.t2.FIFO = FIFO;
	ap.t2.IrqStep = IrqStep;
	ap.t2.Pages = pages;
	ap.t2.IrqEna = 0;
	ap.t2.AdcEna = 1;

	//ap.t2.Chn[0] = SetAmplChannel(amplification[0], channels[0]);
	//ap.t2.Chn[1] = SetAmplChannel(amplification[1], channels[1]);
	for(int i = 0; i < App::total_count_sensors; ++i)
	{
		ap.t2.Chn[i] = SetAmplChannel(amplification[i], channels[i]);
	}

	IDaqLDevice *pI = (IDaqLDevice *)pI_void;
	int res = pI->FillDAQparameters(&ap.t2);
	sizeBufADC *= 2;
	if(res == L_SUCCESS)res = pI->RequestBufferStream(&sizeBufADC, L_STREAM_ADC);
	if(res == L_SUCCESS)res = pI->SetParametersStream(&ap.t2, &sizeBufADC, (void **)&data, (void **)&sync, L_STREAM_ADC);
	halfBuffer = sizeBufADC / 2;
	return res != L_SUCCESS;
}

void Lcard791::Destroy()
{
	((IDaqLDevice *)pI_void)->CloseLDevice(); // завершение работы
	((IDaqLDevice *)pI_void)->Release();
	FreeLibrary(hComponent);
}

bool Lcard791::Start()
{
	if(L_ERROR == ((IDaqLDevice *)pI_void)->InitStartLDevice())return false;
	if(L_ERROR == ((IDaqLDevice *)pI_void)->StartLDevice())return false;
	ready = sync[I_ADC_PCI_COUNT_L791] < halfBuffer;
	return true;
}

void Lcard791::Stop()
{
	((IDaqLDevice *)pI_void)->StopLDevice();
}

int Lcard791::Read(ULONG *&buf)
{
	bool bb = sync[I_ADC_PCI_COUNT_L791] < halfBuffer; 
	if(bb != ready)
	{
		if(bb)
		{
			buf = &data[halfBuffer];
		}
		else
		{
			buf = data;
		}
		ready = bb;
		return halfBuffer;
	}
	return 0;
}

double Lcard791::ReadAsunc(int ch)
{
	IDaqLDevice* pI=(IDaqLDevice*)pI_void;
	pI->InitStartLDevice();
	ASYNC_PAR pp;
	pp.s_Type=L_ASYNC_ADC_INP;
	pp.Chn[0]=SetAmplChannel(0, ch);//SetChn(1,Ch);
	PLATA_DESCR_L791 pd;
	if(L_SUCCESS == pI->IoAsync(&pp) && L_SUCCESS == pI->ReadPlataDescr(&pd))
	{
		double V =short(pp.Data[0]&0xFFFF);
		V += pd.KoefADC[0];
		V *= pd.KoefADC[8];
		V*=10;
		V/=8192;
		return V;
	}
	return 5;//если не сработал 
}
#else
int Lcard791::SubInit(ULONG )
{	
	return 0;
}

int Lcard791::Init()
{	
	return 0;
}

bool Lcard791::InitChannel(int (&channels)[App::total_count_sensors], int (&amplification)[App::total_count_sensors], int rate, ULONG sizeBufADC)
{	
	return 0;
}

void Lcard791::Destroy()
{	
}

bool Lcard791::Start()
{	
	return true;
}

void Lcard791::Stop()
{	
}

int Lcard791::Read(ULONG *&buf)
{
	return 0;
}
#endif
