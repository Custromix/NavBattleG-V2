// header.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN    
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <SFML/Graphics.hpp>


#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <map>
#include <array>
#include <timeapi.h>


#pragma comment(lib, "ws2_32.lib")

#define WM_SOCKET (WM_USER + 1)

using namespace sf;
using namespace std;

#include "computer.h"
#include "board.h"
#include "boat.h"
#include "game.h"



