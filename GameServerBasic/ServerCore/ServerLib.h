#pragma once
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")

#include <Ws2tcpip.h>
#include <winsock2.h>
#include <mswsock.h>
#include <Mmsystem.h>
#include <Ws2spi.h>
#include <Mstcpip.h>

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <cassert>
#include <fcntl.h>
#include <algorithm>
#include <functional>

#include <thread>
#include <mutex>
#include <memory>

#include <string>
#include <tchar.h>

#include <ctime>
#include <random>
#include <typeinfo>

#if _DEBUG
#define CONTEXT_SWITCH() Sleep(1)
#else
#define CONTEXT_SWITCH() ::SwitchToThread()
#endif

using Action = std::function<void(void*)>;

// TODO : ��Ÿ ��ƿ
#include "Util/Type.h"
#include "Util/Util.h"

// TODO : �ʼ� ��� ����
