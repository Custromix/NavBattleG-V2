#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <map>

#pragma comment(lib, "ws2_32.lib")

#define WM_SOCKET (WM_USER + 1)

#include "SCResult.h"
#include "SClient.h"
#include "Server.h"