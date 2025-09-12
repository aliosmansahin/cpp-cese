#include "Graphics.h"

Graphics::Graphics() {

}
Graphics::~Graphics() {
    if (device) {
        device->Release();
        device = NULL;
    }
    if (direct3d) {
        direct3d->Release();
        direct3d = NULL;
    }
}

bool Graphics::Init(HWND hwnd, bool windowed, int wndw, int wndh, bool vsync, std::wstring& maxVertex, std::wstring& maxPixel) {
    this->hwnd = hwnd;

    direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!direct3d) {
        cout << "Direct3D Could Not Create!" << endl;
        return 0;
    }

    Logger::Log(std::to_string(direct3d->GetAdapterCount()) + " graphic adapters found");
    unsigned int adapterCount = direct3d->GetAdapterCount();
    
    for (int i = 0; i < adapterCount; ++i) {
        D3DADAPTER_IDENTIFIER9 identifier;
        direct3d->GetAdapterIdentifier(i, 0, &identifier);
        Logger::Log("Adapter " + std::to_string(i) + ": " + identifier.Description);
    }
    

    D3DDISPLAYMODE displayMode = { 0 };
    direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
    HRESULT result = direct3d->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayMode.Format, D3DFMT_A8R8G8B8, windowed);

    D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
    if (result != D3D_OK) {
        deviceType = D3DDEVTYPE_REF;
    }

    DWORD vertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    D3DADAPTER_IDENTIFIER9 adapter;
    direct3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapter);
    if (adapter.VendorId == 0x10DE) {
        vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
        
    }
    else if (adapter.VendorId == 0x1002) {
        vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }
    else if (adapter.VendorId == 0x8086) {
        vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }


    ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
    d3dpp.BackBufferWidth = wndw;
    d3dpp.BackBufferHeight = wndh;
    d3dpp.Windowed = windowed;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.Flags = 0;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    if (vsync)
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    else
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

    direct3d->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd,
        vertexProcessingType, &d3dpp, &device);
    if (!device) {
        MessageBox(hwnd, L"Direct3D Device Cound Not Create!", L"ERROR", MB_ICONERROR);
        return 0;
    }

    return true;
}
void Graphics::Clear(D3DCOLOR color) {
    device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1, 0);
}
void Graphics::BeginScene() {
    device->BeginScene();
}
void Graphics::EndScene() {
    device->EndScene();
}
HRESULT Graphics::Present() {
    return device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 Graphics::GetDevice()
{
    return device;
}

bool Graphics::ChangeDisplaySet(int w, int h, bool windowed, bool vsync)
{
    d3dpp.BackBufferWidth = w;
    d3dpp.BackBufferHeight = h;
    d3dpp.Windowed = windowed;
    if (vsync)
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    else
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    HRESULT hr = device->Reset(&d3dpp);
    if (FAILED(hr)) {
        exit(0);
    }
    return true;
}

void Graphics::ResetDevice()
{
    HRESULT hr = device->Reset(&d3dpp);
    if (FAILED(hr)) {
        exit(0);
    }
    /*device->Release();
    direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);
    if (!device) {
        cout << "Direct3D Device Cound Not Create!" << endl;
        exit(0);
    }*/
}
