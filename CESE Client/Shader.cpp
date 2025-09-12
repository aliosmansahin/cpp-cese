#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	if (vertexShader)
		vertexShader->Release();
	if (pixelShader)
		pixelShader->Release();
}

bool Shader::Init(HWND hwnd, LPDIRECT3DDEVICE9 device, const wchar_t* vertexShaderFile, const wchar_t* pixelShaderFile)
{
	this->device = device;

	LPD3DXBUFFER shaderBuffer;
	LPD3DXBUFFER errorBuffer;

	HRESULT result = D3DXCompileShaderFromFile(vertexShaderFile, NULL, NULL, "main", "vs_2_0",
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, &shaderBuffer, &errorBuffer, NULL);

	if (FAILED(result)) {
		MessageBox(hwnd, L"Vertex Shader Could Not Compile!", L"ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	result = device->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(), &vertexShader);
	if (FAILED(result)) {
		MessageBox(hwnd, L"Vertex Shader Could Not Create!", L"ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	LPD3DXBUFFER shaderBuffer2;
	LPD3DXBUFFER errorBuffer2;

	result = D3DXCompileShaderFromFile(pixelShaderFile, NULL, NULL, "main", "ps_2_0",
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, &shaderBuffer2, &errorBuffer2, NULL);

	if (FAILED(result)) {
		MessageBox(hwnd, L"Pixel Shader Could Not Compile!", L"ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	result = device->CreatePixelShader((DWORD*)shaderBuffer2->GetBufferPointer(), &pixelShader);
	if (FAILED(result)) {
		MessageBox(hwnd, L"Pixel Shader Could Not Create!", L"ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void Shader::Use()
{
	device->SetVertexShader(vertexShader);
	device->SetPixelShader(pixelShader);
}
