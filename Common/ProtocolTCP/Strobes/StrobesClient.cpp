#include "stdafx.h"
#include "ServerHandler.h"
#include "Frame.h"
#include "NetClient.h"
#include "typelist.hpp"
#include "CommonTCP.h"
#include "IPprotocolProcedureList.hpp"
#include "DebugMess.h"
#include "USPCData.h"
#include "LirItems.h"

struct StrobesData
{
	int count;
	unsigned times[60];
};

namespace StrobesProtocol
{
	struct Stored: public CommonClient
	{
		Frame *f;
		Stored(Frame *f)
			: f(f)
		{
			Singleton<ItemData<Thickness>>::Instance().Clear();
			ThicknessLir &lir = Singleton<ThicknessLir>::Instance();
			f->data.id = TL::IndexOf<__ip_protocol_procedure_list__, StrobesProtocol::Server>::value;
			StrobesData *x = (StrobesData *)&f->data.buf;
			x->count = lir.countZones - 1;
			if(x->count < 0) x->count = 0;
			for(int i = 0; i < x->count; ++i)
			{
				x->times[i] = lir.times[i];
			//	dprint("time offs %d %d\n", i, x->times[i]);
				//Sleep(10);
			}
			dprint("count %d\n", x->count);
			f->length = sizeof(StrobesData);
			f->proc = Recv<Stored>;
		}

		bool Do()
		{
			if(0 == wcscmp(L"Ok", (wchar_t *)f->data.buf))
			{
#pragma message("������ ������� �������� �������� �������������")
				zprint("Data Ok\n");
			}
			return false;
		}

		static void *operator new(size_t size, void *ptr)
		{
			return ptr;
		}
		static void operator delete(void *, void *){}
	};		
	bool Client::Do(wchar_t *addr, int port)
	{
		unsigned (&data)[App::zonesCount + 2] = Singleton<ThicknessLir>::Instance().times;
		Frame *f = Frame::Get();

		new(Frame::AdditionalData<Stored>(f)) Stored(f);
		return NetClient::Connect(addr, port, f);
	}

}