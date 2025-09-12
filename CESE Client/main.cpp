#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include "Game.h"
#include "Logger.h"

using namespace std;

Game* game;
bool focus = true;
std::string version;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_ACTIVATEAPP:
        if (game)
            game->SetFocusedWindow(wParam);
        break;
    case WM_KEYDOWN:
        if (LOWORD(wParam) == VK_ESCAPE) {
            if (game) {
                if (game->GetLoaded() && game->GetState() == 1) {
                    if (game->GetPaused()) {
                        game->SetPaused(false);
                    }
                    else {
                        game->SetPaused(true);
                    }
                    game->PauseMenu();
                }
            }
        }
        break;
    case WM_LBUTTONDOWN:
        if (game) {
            if (focus) {
                if (!game->GetFireEnable()) {
                    game->SetFireEnable(true);
                    game->SetBulletThread();
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        if (game) {
            game->SetFireEnable(false);
            game->ClickUI();
        }
        break;
    case WM_CHAR:
        if (game)
            game->UpdateEditable((wchar_t)wParam);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    /*
        I USED THIS PROCESS TO TRY UPDATING SYSTEM
        BUT NOW IT WON'T WORK
    */
    /*int argc;
    argv = CommandLineToArgvW(GetCommandLine(), &argc);
    argc = 0;
    if (argc == 1) {
        PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        if (!CreateProcess(L"CESE Updater.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            MessageBox(NULL, L"\"CESE Updater.exe\" process creation failed.", L"ERROR", MB_OK | MB_ICONERROR);
            return 0;
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return 0;
    }


    Sleep(1000);
    

    ifstream readFiles("files.txt");
    if (readFiles.is_open()) {
        readFiles.close();

        filesystem::remove("CESE Updater.exe_");
        remove("files.txt");
    }
    */

    ifstream readFiles("version");
    if (!readFiles.is_open()) {
        MessageBox(NULL, L"\"version.txt\" not found.", L"ERROR", MB_OK | MB_ICONERROR);
        return 0;
    }
    readFiles >> version;
    readFiles.close();

    Logger::Log("Window Loading");

    cout << "Window Loading..." << endl;
    // VARIABLES
    MSG msg;
    HWND hwnd;
    int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
    int WindowHeight = GetSystemMetrics(SM_CYSCREEN);
    bool Windowed = false;
    bool Vsync = false;
    string sWindowed;
    string sWW, sWH;
    string sVsync;
    string destination;

    bool configFile0 = true;

    ifstream readConfig("Saves/display.cfg");
    if (!readConfig.is_open()) {
        cout << "Config File Can't Open!" << endl;
        Logger::Log("Config file was not found");
        configFile0 = false;
    }
    while (readConfig >> destination) {
        if (destination == "windowed") {
            readConfig >> sWindowed;
            if (sWindowed == "1")
                Windowed = true;
            else
                Windowed = false;
        }
        else if (destination == "resolution") {
            readConfig >> sWW >> sWH;
            WindowWidth = stoi(sWW);
            WindowHeight = stoi(sWH);
        }
        else if (destination == "vsync") {
            readConfig >> sVsync;
            if (sVsync == "1")
                Vsync = true;
            else
                Vsync = false;
        }
    }
    readConfig.close();
    if (configFile0) {
        Logger::Log("Config file loaded");
    }

    string sSens;
    string sAdditional;
    float sens = 1;
    bool additional = false;

    bool configFile1 = true;

    ifstream readConfig1("Saves/game.cfg");
    if (!readConfig1.is_open()) {
        cout << "Config File Can't Open!" << endl;
        Logger::Log("Config file was not found");
        configFile1 = false;
    }
    while (readConfig1 >> destination) {
        if (destination == "sens") {
            readConfig1 >> sSens;

            try {
                size_t startPos = sSens.find(",");
                if(startPos != std::string::npos)
                    sSens.replace(startPos, 1, ".");
                sens = stof(sSens);
            }
            catch (exception e) {
                Logger::Log(e.what());
                sens = 1.0f;
            }
        }
        else if (destination == "additionaldata") {
            readConfig1 >> sAdditional;
            additional = sAdditional == "1";
        }
    }
    readConfig1.close();
    if (configFile1) {
        Logger::Log("Config file loaded");
    }

    // WINDOW CLASS
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 5);
    wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"WindowClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // REGISTER WINDOW CLASS
    if (!RegisterClassEx(&wc)) {
        cout << "Window Class Could Not Create!" << endl;
        return 0;
    }

    RECT windowRect;
    windowRect.left = 0;
    windowRect.right = WindowWidth;
    windowRect.top = 0;
    windowRect.bottom = WindowHeight;

    //if (Windowed) {
    AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, false);
    //}

    // CREATE WINDOW
    hwnd = CreateWindowEx(NULL, L"WindowClass", L"CESE Client",
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
        //WS_POPUP,
        (GetSystemMetrics(SM_CXSCREEN) / 2) - (windowRect.right / 2),
        (GetSystemMetrics(SM_CYSCREEN) / 2) - (windowRect.bottom / 2),
        windowRect.right, windowRect.bottom,
        NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        cout << "Window Could Not Create!" << endl;
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

    Logger::Log("Window was created");

    msg = { 0 };

    game = new Game();
    if (game->Init(hwnd, msg, Windowed, WindowWidth, WindowHeight, Vsync, version, sens, additional)) {
        game->Run();
        return (int)msg.wParam;
    }
    delete game;
    //CoUninitialize();
    return (int)msg.wParam;
}