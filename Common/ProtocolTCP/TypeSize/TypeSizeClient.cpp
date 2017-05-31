#include "stdafx.h"
#include "ServerHandler.h"
#include "Frame.h"
#include "NetClient.h"
#include "typelist.hpp"
#include "IPprotocolProcedureList.hpp"
#include "ResultData.h"
#include "DebugMess.h"
#include "stdio.h"
#include "templates.hpp"

namespace 
{
	struct Data
	{
		wchar_t Ok[4];
		double tresholdKlass1;
		double tresholdKlass2;
		double tresholdKlass3;
	};
	struct XXData
	{
		bool ok;
		wchar_t *typeSize;
		void Test(Data *s)
		{
			ok = 0 == wcscmp(L"Ok", s->Ok);
			wchar_t buf[512];
			if(ok)
			{
                ResultViewerData &r = Singleton<ResultViewerData>::Instance();
				r.tresholdKlass1 = s->tresholdKlass1;
				r.tresholdKlass2 = s->tresholdKlass2;
				r.tresholdKlass3 = s->tresholdKlass3;
				wsprintf(buf, L"<ff00>������ ���������� <ff>%s"
					, typeSize
					);
				app.MainWindowTopLabel(buf);
				SetEvent(App::ProgrammContinueEvent);
				wsprintf(buf, L"\"1 ����� %s\" \"2 ����� %s\" \"3 ����� %s\""
					, Wchar_from<double, 3>(r.tresholdKlass1)()
					, Wchar_from<double, 3>(r.tresholdKlass2)()
					, Wchar_from<double, 3>(r.tresholdKlass3)()
					);
				app.MainWindowBottomLabel(App::status_typesize, buf);
				dprint("###@@@  thresh  1 klass %f  2 klass %f  2 klass %f++++++\n", r.tresholdKlass1, r.tresholdKlass2, r.tresholdKlass3);
			}
			else
			{
				wsprintf(buf, L"<ff0000>���������� ����������� <ff>%s", typeSize);
				app.MainWindowTopLabel(buf);
				app.MainWindowBottomLabel(App::status_typesize, L"");
				dprint("###@@@  nhtshold EEERRRRRR XXXXXXXX +++++\n");
			}
		}
	} xxData;
}

namespace TypeSizeProtocol
{
		struct Stored: public CommonClient
		{
			XXData &item;
			Frame *f;
			Stored(XXData &item, Frame *f, wchar_t *data)
				: item(item)
				, f(f)
			{
				item.ok = false;
				f->data.id = TL::IndexOf<__ip_protocol_procedure_list__, TypeSizeProtocol::Server>::value;
				int len = 1 + wcslen(data);
				wcscpy_s((wchar_t *)f->data.buf, len, data);
				f->length = 2 * len;
				f->proc = Recv<Stored>;
			}

			bool Do()
			{
				item.Test((Data *)f->data.buf);
				f->proc = Stop;
				return true;
			}

			static void *operator new(size_t size, void *ptr)
			{
				return ptr;
			}
			static void operator delete(void *, void *){}
		};		
	bool Client::Do(wchar_t *addr, int port, wchar_t *data)
	{
		Frame *f = Frame::Get();
		xxData.typeSize = data;
		Stored *stored = new(Frame::AdditionalData<Stored>(f)) Stored(xxData, f, data);
		NetClient::Connect(addr, port, f);
		Sleep(1000);
		return stored->item.ok;
	}

}