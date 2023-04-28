#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN    
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <queue>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")

#define WM_SOCKET (WM_USER + 1)

#include "SCResult.h"
#include "SClient.h"
#include "SMessage.h"
#include "QueueMessageManager.h"
#include "GameManager.h"
#include "Server.h"