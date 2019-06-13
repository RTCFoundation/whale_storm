

#pragma once

const int MAX_EVENT_COUNT = 5000;
const int MAX_RECV_BUFF = 65535;

#ifdef OS_WIN32
#include "iocp/iocploop.h"
#define IoLoop IOCPLoop
#elif defined(OS_LINUX)
#include "epoll/EPollLoop.h"
#define IoLoop EPollLoop
#endif
