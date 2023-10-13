#pragma once
#include <Windows.h>
#include "Imgui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_opengl2.h"
#pragma comment(lib, "OpenGL32.lib")
#include "ESP.h"

#include "Others.h"
#include "debugger.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK hWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Menu
{
private:
	ESP* myEsp = nullptr;

	
public:
	Menu(int x, int y);
	~Menu();
	void Init();
	void Toggle();
	void DrawCheat(Font myFont);
	bool getStatus();
};

