#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <sstream>
#include <conio.h>
#include <fstream>

class UI
{
public:
	virtual void Draw() = 0;
	virtual void Update(wchar_t key) = 0;
	virtual void SetHower(POINT m) = 0;
	virtual void SetVisible(bool visible) = 0;
	virtual void SetEditable(bool editable) = 0;
	virtual void SetWait(bool wait) = 0;
	virtual void SetText(std::wstring text) = 0;
	virtual void SetInput(std::wstring option) = 0;
	virtual void SetPos(int left, int right, int top, int bottom, int height, int nx) = 0;
	virtual void ReloadWorlds(LPDIRECT3DDEVICE9 device) = 0;
	virtual void SetOptionText(int optioni, std::wstring text) = 0;
	virtual void AddOption(std::wstring option) = 0;
	virtual void SetTitle(std::wstring text) = 0;
	virtual void ResetObjects() = 0;
	virtual void LoadObjects() = 0;
	virtual bool SetSelected(int selected) = 0;
	virtual bool GetClicked(POINT m) = 0;
	virtual bool GetVisible() = 0;
	virtual bool GetPausedScreen() = 0;
	virtual int GetSelected() = 0;
	virtual int GetClickedBtn(POINT m) = 0;
	virtual std::string WhatIsThis() = 0;
	virtual std::wstring GetOptionText(int optioni) = 0;
	virtual std::wstring GetTarget() = 0;
	virtual std::wstring GetUIClass() = 0;
	virtual std::wstring GetTitle() = 0;
	virtual std::wstring GetClickedWorld(POINT m) = 0;
	virtual std::wstring GetInput() = 0;
	virtual std::wstring GetName() = 0;
};

class Drawable : public UI {
public:
	Drawable(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring text);
	~Drawable();
	void Draw() override;
	void Update(wchar_t key) override;
	void SetHower(POINT m) override;
	void SetWait(bool wait) override;
	void SetVisible(bool visible) override;
	void SetEditable(bool editable) override;
	void SetText(std::wstring text) override;
	void SetPos(int left, int right, int top, int bottom, int height, int nx) override;
	void SetOptionText(int optioni, std::wstring text) override;
	void SetInput(std::wstring option) override;
	void ReloadWorlds(LPDIRECT3DDEVICE9 device) override;
	void AddOption(std::wstring option) override;
	void SetTitle(std::wstring text) override;
	void ResetObjects() override;
	void LoadObjects() override;
	bool SetSelected(int selected) override;
	bool GetClicked(POINT m) override;
	bool GetVisible() override;
	bool GetPausedScreen() override;
	int GetSelected() override;
	int GetClickedBtn(POINT m) override;
	std::string WhatIsThis() override;
	std::wstring GetTarget() override;
	std::wstring GetOptionText(int optioni) override;
	std::wstring GetUIClass() override;
	std::wstring GetTitle() override;
	std::wstring GetClickedWorld(POINT m) override;
	std::wstring GetInput() override;
	std::wstring GetName() override;
private:
	RECT crd;
	LPD3DXFONT font;
	LPDIRECT3DDEVICE9 device;
	DWORD format;
	std::wstring text;
	std::wstring UIclass;
	std::wstring name;
	D3DCOLOR color;
	int height;
	bool visible;
	bool pausedScreen;
};

class Selectable : public UI {
public:
	Selectable(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring target, std::wstring text);
	~Selectable();
	void Draw() override;
	void Update(wchar_t key) override;
	void SetHower(POINT m) override;
	void SetWait(bool wait) override;
	void SetVisible(bool visible) override;
	void SetInput(std::wstring option) override;
	void SetOptionText(int optioni, std::wstring text) override;
	void SetPos(int left, int right, int top, int bottom, int height, int nx) override;
	void SetEditable(bool editable) override;
	void SetText(std::wstring text) override;
	void ReloadWorlds(LPDIRECT3DDEVICE9 device) override;
	void AddOption(std::wstring option) override;
	void SetTitle(std::wstring text) override;
	void ResetObjects() override;
	void LoadObjects() override;
	bool SetSelected(int selected) override;
	bool GetClicked(POINT m) override;
	bool GetVisible() override;
	bool GetPausedScreen() override;
	int GetSelected() override;
	int GetClickedBtn(POINT m) override;
	std::string WhatIsThis() override;
	std::wstring GetOptionText(int optioni) override;
	std::wstring GetTarget() override;
	std::wstring GetUIClass() override;
	std::wstring GetClickedWorld(POINT m) override;
	std::wstring GetInput() override;
	std::wstring GetTitle() override;
	std::wstring GetName() override;
private:
	RECT crd;
	LPD3DXFONT font;
	LPDIRECT3DDEVICE9 device;
	DWORD format;
	std::wstring text;
	std::wstring target;
	std::wstring UIclass;
	std::wstring name;
	D3DCOLOR color;
	int height;
	bool visible;
	bool pausedScreen;
	bool hower = false;
};

class Editable : public UI {
public:
	Editable(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring target, std::wstring text);
	~Editable();
	void Draw() override;
	void Update(wchar_t key) override;
	void SetHower(POINT m) override;
	void SetVisible(bool visible) override;
	void SetWait(bool wait) override;
	void SetInput(std::wstring option) override;
	void SetEditable(bool editable) override;
	void SetOptionText(int optioni, std::wstring text) override;
	void SetPos(int left, int right, int top, int bottom, int height, int nx) override;
	void SetText(std::wstring text) override;
	void ReloadWorlds(LPDIRECT3DDEVICE9 device) override;
	void AddOption(std::wstring option) override;
	void SetTitle(std::wstring text) override;
	void ResetObjects() override;
	void LoadObjects() override;
	bool SetSelected(int selected) override;
	bool GetClicked(POINT m) override;
	bool GetVisible() override;
	bool GetPausedScreen() override;
	int GetSelected() override;
	int GetClickedBtn(POINT m) override;
	std::string WhatIsThis() override;
	std::wstring GetOptionText(int optioni) override;
	std::wstring GetTarget() override;
	std::wstring GetUIClass() override;
	std::wstring GetTitle() override;
	std::wstring GetClickedWorld(POINT m) override;
	std::wstring GetInput() override;
	std::wstring GetName() override;
private:
	RECT crd;
	LPD3DXFONT font;
	LPDIRECT3DDEVICE9 device;
	DWORD format;
	std::wstring text;
	std::wstring inputText = L"";
	std::wstring target;
	std::wstring UIclass;
	std::wstring name;
	D3DCOLOR color;
	int height;
	int charLimit = 50;
	bool visible;
	bool editable = false;
	bool wait = false;
	bool pausedScreen;
	bool hower = false;;
};

class ListOption : public UI {
public:
	ListOption(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring target, std::wstring text, int wx);
	~ListOption();
	void Draw() override;
	void Update(wchar_t key) override;
	void SetHower(POINT m) override;
	void SetVisible(bool visible) override;
	void SetWait(bool wait) override;
	void SetEditable(bool editable) override;
	void SetInput(std::wstring option) override;
	void SetOptionText(int optioni, std::wstring text) override;
	void SetPos(int left, int right, int top, int bottom, int height, int nx) override;
	void SetText(std::wstring text) override;
	void ReloadWorlds(LPDIRECT3DDEVICE9 device) override;
	void AddOption(std::wstring option) override;
	void SetTitle(std::wstring text) override;
	void ResetObjects() override;
	void LoadObjects() override;
	bool SetSelected(int selected) override;
	bool GetClicked(POINT m) override;
	bool GetVisible() override;
	bool GetPausedScreen() override;
	int GetSelected() override;
	int GetClickedBtn(POINT m) override;
	std::wstring GetOptionText(int optioni) override;
	std::string WhatIsThis() override;
	std::wstring GetTitle() override;
	std::wstring GetTarget() override;
	std::wstring GetUIClass() override;
	std::wstring GetClickedWorld(POINT m) override;
	std::wstring GetInput() override;
	std::wstring GetName() override;
private:
	RECT crd;
	RECT titleRect;
	RECT titleTexRect;
	RECT leftBtnRect;
	RECT leftBtnTexRect;
	RECT optionRect;
	RECT optionTexRect;
	RECT rightBtnRect;
	RECT rightBtnTexRect;
	DWORD format;
	LPDIRECT3DDEVICE9 device;
	LPD3DXFONT titlefont;
	LPD3DXFONT leftbtnfont;
	LPD3DXFONT rightbtnfont;
	LPD3DXFONT optionfont;
	std::wstring title;
	std::wstring target;
	std::wstring name;
	std::wstring UIclass;
	std::vector<std::wstring> options;
	D3DCOLOR color;
	int height;
	int selected;
	bool visible;
	bool pausedScreen;
	bool leftHower;
	bool rightHower;
};