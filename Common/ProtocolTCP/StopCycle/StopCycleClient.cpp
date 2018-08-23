#include "stdafx.h"
#include "StopCycleProtocol.h"
#include "ServerHandler.h"
#include "Frame.h"
#include "NetClient.h"
#include "typelist.hpp"
#include "IPprotocolProcedureList.hpp"
#include "DebugMess.h"

namespace StopCycleProtocol
{
	struct Stored: public CommonClient
	{
		Frame *f;
		Stored(Frame *f)
			: f(f)
		{
			f->data.id = TL::IndexOf<__ip_protocol_procedure_list__, StopCycleProtocol::Server>::value;
			wchar_t *data = L"Stop";
			int len = 1 + wcslen(data);
			wcscpy_s((wchar_t *)f->data.buf, len, data);
			f->length = 2 * len;
			f->proc = Recv<Stored>;
		}

		bool Do()
		{
			if(0 == wcscmp(L"Ok", (wchar_t *)f->data.buf))
			{
				app.MainWindowTopLabel(L"<ff00>���������� ����������");
			}

			f->proc = Stop;
			return true;
		}

		static void *operator new(size_t size, void *ptr)
		{
			return ptr;
		}
		static void operator delete(void *, void *){}
	};		
	bool Client::Do(wchar_t *addr, int port)
	{
		Frame *f = Frame::Get();
		new(Frame::AdditionalData<Stored>(f)) Stored(f);
		return NetClient::Connect(addr, port, f);
	}

}