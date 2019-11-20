#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <assert.h>
#include <assimp/cimport.h>
#include <assimp\Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

using namespace DirectX;

#pragma comment(lib, "assimp-vc142-mt.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")


#define SCREEN_WIDTH	(1080)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ345


HWND GetWindow();
