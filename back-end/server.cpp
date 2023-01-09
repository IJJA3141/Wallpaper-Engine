#include <crow.h>
#include "server.h"

namespace http
{
	TcpServer::TcpServer()
	{
		WSASStartup
		m_socket = socket(AF_INET, SOCK_STERAM, 0);
	}

	TcpServer::~TcpServer()
	{

	}
}