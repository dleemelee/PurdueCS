#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

#include "Utils.hpp"
#include "Config.hpp"
#include "server/TcpConnection.hpp"
#include "error/ConnectionError.hpp"
#include "error/SocketError.hpp"
#include "error/TodoError.hpp"

TcpConnection::TcpConnection(Config const& config, int master_fd) :
    m_config(config),
    m_master(master_fd),
    m_shutdown(false)
{
	m_conn = accept(m_master, nullptr, nullptr);
	if(m_conn == -1) {
		throw SocketError(std::string("accept"));
	}

}

TcpConnection::~TcpConnection() noexcept
{
    d_printf("Closing connection on %d", m_conn);

    if (close(m_conn) == -1) d_errorf("Could not close connection %d", m_conn);
}

void TcpConnection::shutdown()
{
    d_printf("Shutting down connection on %d", m_conn);
    
    if (::shutdown(m_conn, SHUT_RDWR) == -1) d_errorf("Could not shut down connection %d", m_conn);

    m_shutdown = true;
}

bool TcpConnection::getc(unsigned char* c)
{
    if (read(m_conn, c, sizeof(unsigned char)) == 0 )
	{
		return false;
	}
	return true;
}

void TcpConnection::putc(unsigned char c)
{
	char * mychar = NULL;
	*mychar = c;
    write(m_conn, mychar, 1);
}

void TcpConnection::puts(std::string const& str)
{
	char mychar[str.size()];
	strcpy(mychar, str.c_str());
	write(m_conn, mychar, str.size());
}

void TcpConnection::putbuf(void const* buf, size_t bufsize)
{
    write(m_conn, buf, bufsize);
}
