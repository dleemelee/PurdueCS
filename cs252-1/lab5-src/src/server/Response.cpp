#include <string>
#include <cstring>
#include <map>

#include "server/Response.hpp"
#include "server/TcpConnection.hpp"
#include "http/HttpStatus.hpp"
#include "error/ResponseError.hpp"
#include "error/TodoError.hpp"
#include "Config.hpp"

Response::Response(Config const& config, TcpConnection& conn) :
    m_config(config),
    m_conn(conn),
    m_headers_sent(false)
{
    // We want every response to have this header
    // It tells browsers that we want separate connections per request
    m_headers["Connection"] = "close";
}

void Response::send(void const* buf, size_t bufsize, bool raw)
{
	if (raw == false) {
		send_headers();
	}
	else {
		m_conn.putbuf(buf, bufsize);		
	}

}

void Response::send_headers()
{
    for(std::map<std::string, std::string>::iterator it = m_headers.begin(); it != m_headers.end(); ++it)
	{
		m_conn.puts( it->first+" : "+it->second+"\r\n" );
	}
}

void Response::set_header(std::string const& key, std::string const& value)
{
    m_headers[key] = value;
}

void Response::set_status(HttpStatus const& status)
{
    m_status_text = status.to_string();
}
