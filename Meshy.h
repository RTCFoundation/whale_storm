
#pragma once

#include "IoLoop.h"
#include "F:\whale_storm\dep\net.h"

#ifdef OS_LINUX
#include "epoll/EPollClient.h"
#include "epoll/EPollConnection.h"
#include "epoll/EPollServer.h"
#include "epoll/EPollStream.h"
#elif defined(OS_WIN32)
#include "iocp/IOCPClient.h"
#include "iocp/IOCPConnection.h"
#include "iocp/IOCPServer.h"
#include "iocp/IOCPStream.h"
#endif

namespace meshy {
#ifdef OS_LINUX
    typedef EPollServer TcpServer;
    typedef EPollConnection TcpConnection;
    typedef EPollClient TcpClient;
    typedef EPollStream TcpStream;
#elif defined(OS_WIN32)
    typedef IOCPServer TcpServer;
    //typedef WSAConnection TcpConnection;
#define TcpConnection WSAConnection
    typedef IOCPClient TcpClient;
    typedef IOCPStream TcpStream;
#endif

}