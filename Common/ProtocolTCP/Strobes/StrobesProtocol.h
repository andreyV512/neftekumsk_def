#pragma once
#include "CommonTCP.h"
struct Frame;
namespace StrobesProtocol
{
	class Server: public CommonServer<Server>
	{
	public:
		static bool Do(Frame *);
	};
	class Client: public CommonClient
	{
	public:
		static bool Do(wchar_t *addr, int port);
	};
}