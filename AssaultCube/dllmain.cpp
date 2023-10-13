#include <Windows.h>
#include "Menu.h"
FILE* pFile = nullptr;
typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hDc);
_wglSwapBuffers wglSwapBuffers;
const char* LOGO = "AssaultCube by FG";
Font glFont;
const int FONT_HEIGHT = 15;
const int FONT_WIDTH = 8;
Menu* myMenu = new Menu(500, 500);

BOOL __stdcall hkSwapBuffers(HDC hDc) {
	HDC currentHDC = wglGetCurrentDC();
	if (!glFont.m_bBuilt || currentHDC != glFont.m_Hdc)
	{
		glFont.Build(FONT_HEIGHT);
	}
	OpenGl::SetupOrtho();
	glFont.Print(OpenGl::getRes().x - strlen(LOGO) * 9, OpenGl::getRes().y - 30.0f, rgb::purple, "%s", LOGO);	
	myMenu->DrawCheat(glFont);
	OpenGl::RestoreGL();
	return wglSwapBuffers(hDc);
}


#define MEM_WRITE (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)
#define MEM_READ (PAGE_EXECUTE_READ | PAGE_READONLY | MEM_WRITE)
#define MEM_EXEC (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)
bool W2S22(Vector3 pos, Vector3& screen, float matrix[16], int windowWidth, int windowHeight) {
    Vector4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    //if entity is behoind u
    if (clipCoords.w < 0.1f)
        return false;
    Vector3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
    return true;
}
DWORD WINAPI onLoad(HMODULE hModule) {

    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    //LP "
    myMenu->Init();
    TrampolineHook* myHook = new TrampolineHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkSwapBuffers, (BYTE*)&wglSwapBuffers, 5);
    myHook->Toggle();


  
    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT))
        {
            myMenu->Toggle();
          
        }

            if (GetAsyncKeyState(VK_END))
            {
                break;
            }
         
            Sleep(1000);  
        }
          delete myMenu;
          delete myHook;
          FreeLibraryAndExitThread(hModule, 0);
          CloseHandle(hModule);
    
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread = 0;
        hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)onLoad, hModule, 0, 0);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

