#pragma once

#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>
#include "Logger.h"

using namespace std;

class Graphics {
public:
    Graphics();
    ~Graphics();

    bool Init(HWND hwnd, bool windowed, int wndw, int wndh, bool vsync, std::wstring& maxVertex, std::wstring& maxPixel);
    void Clear(D3DCOLOR color);
    void BeginScene();
    void EndScene();
    HRESULT Present();
    LPDIRECT3DDEVICE9 GetDevice();
    bool ChangeDisplaySet(int w, int h, bool windowed, bool vsync);
    void ResetDevice();
private:
    LPDIRECT3DDEVICE9 device;
    D3DPRESENT_PARAMETERS d3dpp;
    LPDIRECT3D9 direct3d;
    HWND hwnd;
};