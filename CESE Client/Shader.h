#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class Shader
{
public:
	Shader();
	~Shader();
	bool Init(HWND hwnd, LPDIRECT3DDEVICE9 device, const wchar_t* vertexShaderFile, const wchar_t* pixelShaderFile);
	void Use();
private:
	LPDIRECT3DVERTEXSHADER9 vertexShader;
	LPDIRECT3DPIXELSHADER9 pixelShader;
	LPDIRECT3DDEVICE9 device;
};

