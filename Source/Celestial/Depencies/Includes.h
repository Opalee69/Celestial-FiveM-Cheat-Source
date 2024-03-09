#pragma once

//Standard libs
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <minwindef.h>
#include <sstream>
#include <memory>
#include <fstream>
#include <Psapi.h>
#include <xmmintrin.h>
#include <DirectXMath.h>
#include <filesystem>

//d3d11
#include <d3d11.h>
#include <tchar.h>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

//d3d9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

//Hook
#include <MinHook.h>
#include <kiero.h>

//Imgui
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <gui.h>
#include <imgui_tricks.hpp>
#include <colorpicker.h>

// Depencies/Encryption
#include <Xor_.h>
#include <Encryption.h>

// Depencies/Includes
#include <Singleton.h>

// Depencies/Memory
#include <Memory.h>

// Depencies/Game -/offsets -/Math -/Helper
#include <Vectors.h>
#include <Init.h>
#include <World.h>
#include <Helper.h>

// Features -/Visuals -/Aimbot
#include <Vars.h>

#include <Visuals.h>
#include <Aimhelper.h>

//Fonts
#include <glypther.h>
#include <fontb.h>

#pragma comment( lib, "freetype64.lib" )


