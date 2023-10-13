#include "Menu.h"

struct MenuConfig {
	bool menuActive = false;
	WNDPROC GameWindowProc = NULL;
}menuConf;

LRESULT CALLBACK hWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//pass message to imgui if menu active
	if (menuConf.menuActive) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
			return true;
		}
		ImGuiIO& io = ImGui::GetIO();

		switch (uMsg) {
		case WM_LBUTTONDOWN:
			io.MouseDown[1] = !io.MouseDown[0];
			return 0;
		case WM_RBUTTONDOWN:
			io.MouseDown[1] = !io.MouseDown[1];
			return 0;
		case WM_MBUTTONDOWN:
			io.MouseDown[2] = !io.MouseDown[2];
			return 0;
		case WM_MOUSEWHEEL:
			return 0;
		case WM_MOUSEMOVE:
			io.MousePos.x = (signed short)(lParam);
			io.MousePos.y = (signed short)(lParam >> 16);
			return 0;
		}


	}
	return CallWindowProc(menuConf.GameWindowProc, hWnd, uMsg, wParam, lParam);
}

Menu::Menu(int x, int y) {
	//menuSize.x = x; //pode definir o tamanho do menu aq
	//menuSize.y = y;2
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	myEsp = new ESP();
	
}
Menu::~Menu() {
	menuConf.menuActive = false;
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(FindWindowA(NULL, "AssaultCube"), GWLP_WNDPROC, (LONG_PTR)menuConf.GameWindowProc);
	delete myEsp;
	
}


void Menu::Init() {
	HWND hWnd = NULL;
	while (hWnd == NULL) {
		hWnd = FindWindowA(NULL, "AssaultCube");
	}
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplOpenGL2_Init();
	ImGuiStyle* myStyle = &ImGui::GetStyle();
	ImVec4* colors = myStyle->Colors;
	myStyle->WindowMinSize = ImVec2(300, 300);
	myStyle->WindowPadding = ImVec2(15, 15);
	myStyle->WindowRounding = 10.0f;
	myStyle->WindowPadding = ImVec2(6, 6);
	menuConf.GameWindowProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)hWindProc);
}

void Menu::Toggle() {
	menuConf.menuActive = !menuConf.menuActive;
}
bool Menu::getStatus() {
	return menuConf.menuActive;
}
void Menu::DrawCheat(Font myFont) {
	myEsp->Draw(myFont);
}