#include "UI.h"

Drawable::Drawable(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring text)
{
	this->device = device;
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	this->text = text;
	this->UIclass = UIclass;
	this->visible = visible;
	this->pausedScreen = pausedScreen;
	this->name = name;
	color = D3DCOLOR_XRGB(r, g, b);

	if (hpos == L"LEFT" && vpos == L"TOP")
		format = DT_LEFT && DT_TOP;
	else if (hpos == L"CENTER" && vpos == L"TOP")
		format = DT_CENTER | DT_TOP;
	else if (hpos == L"RIGHT" && vpos == L"TOP")
		format = DT_RIGHT | DT_TOP;
	else if (hpos == L"LEFT" && vpos == L"CENTER")
		format = DT_LEFT | DT_VCENTER;
	else if (hpos == L"CENTER" && vpos == L"CENTER")
		format = DT_CENTER | DT_VCENTER;
	else if (hpos == L"RIGHT" && vpos == L"CENTER")
		format = DT_RIGHT | DT_VCENTER;
	else if (hpos == L"LEFT" && vpos == L"BOTTOM")
		format = DT_LEFT | DT_BOTTOM;
	else if (hpos == L"CENTER" && vpos == L"BOTTOM")
		format = DT_CENTER | DT_BOTTOM;
	else if (hpos == L"RIGHT" && vpos == L"BOTTOM")
		format = DT_RIGHT | DT_BOTTOM;

	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

Drawable::~Drawable()
{
	font->Release();
}

void Drawable::Draw()
{
	if (visible)
		font->DrawTextW(NULL, text.c_str(), -1, &crd, format, color);
}

void Drawable::Update(wchar_t key)
{
}

void Drawable::SetHower(POINT m)
{
}

void Drawable::SetWait(bool wait)
{
}

void Drawable::SetVisible(bool visible)
{
	this->visible = visible;
}

void Drawable::SetEditable(bool editable)
{
}

void Drawable::SetText(std::wstring text)
{
	this->text = text;
}

void Drawable::SetPos(int left, int right, int top, int bottom, int height, int nx)
{
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	font->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

void Drawable::SetOptionText(int optioni, std::wstring text)
{
}

void Drawable::SetInput(std::wstring option)
{
}

bool Drawable::SetSelected(int selected)
{
	return false;
}

void Drawable::ReloadWorlds(LPDIRECT3DDEVICE9 device)
{
}

void Drawable::AddOption(std::wstring)
{
}

void Drawable::SetTitle(std::wstring text)
{
}

void Drawable::ResetObjects()
{
	font->OnLostDevice();
}

void Drawable::LoadObjects()
{
	font->OnResetDevice();
}

bool Drawable::GetClicked(POINT m)
{
	return false;
}

bool Drawable::GetVisible()
{
	return visible;
}

bool Drawable::GetPausedScreen()
{
	return pausedScreen;
}

int Drawable::GetSelected()
{
	return 0;
}

int Drawable::GetClickedBtn(POINT m)
{
	return 0;
}

std::string Drawable::WhatIsThis()
{
	return "Drawable";
}

std::wstring Drawable::GetTarget()
{
	return L"";
}

std::wstring Drawable::GetOptionText(int optioni)
{
	return L"";
}

std::wstring Drawable::GetUIClass()
{
	return UIclass;
}

std::wstring Drawable::GetTitle()
{
	return L"";
}

std::wstring Drawable::GetClickedWorld(POINT m)
{
	return L"";
}

std::wstring Drawable::GetInput()
{
	return L"";
}

std::wstring Drawable::GetName()
{
	return name;
}

Selectable::Selectable(LPDIRECT3DDEVICE9 device, std::wstring name,
	bool pausedScreen, int left, int right, int top, int bottom,
	int height, std::wstring vpos, std::wstring hpos,
	int r, int g, int b, bool visible, std::wstring UIclass,
	std::wstring target, std::wstring text)
{
	this->device = device;
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	this->text = text;
	this->target = target;
	this->UIclass = UIclass;
	this->visible = visible;
	this->pausedScreen = pausedScreen;
	this->name = name;
	color = D3DCOLOR_XRGB(r, g, b);

	if (hpos == L"LEFT" && vpos == L"TOP")
		format = DT_LEFT && DT_TOP;
	else if (hpos == L"CENTER" && vpos == L"TOP")
		format = DT_CENTER | DT_TOP;
	else if (hpos == L"RIGHT" && vpos == L"TOP")
		format = DT_RIGHT | DT_TOP;
	else if (hpos == L"LEFT" && vpos == L"CENTER")
		format = DT_LEFT | DT_VCENTER;
	else if (hpos == L"CENTER" && vpos == L"CENTER")
		format = DT_CENTER | DT_VCENTER;
	else if (hpos == L"RIGHT" && vpos == L"CENTER")
		format = DT_RIGHT | DT_VCENTER;
	else if (hpos == L"LEFT" && vpos == L"BOTTOM")
		format = DT_LEFT | DT_BOTTOM;
	else if (hpos == L"CENTER" && vpos == L"BOTTOM")
		format = DT_CENTER | DT_BOTTOM;
	else if (hpos == L"RIGHT" && vpos == L"BOTTOM")
		format = DT_RIGHT | DT_BOTTOM;

	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

Selectable::~Selectable()
{
	font->Release();
}

void Selectable::Draw()
{
	if (visible) {
		D3DRECT rect;
		rect.x1 = crd.left;
		rect.x2 = crd.right;
		rect.y1 = crd.top;
		rect.y2 = crd.bottom;

		if (!hower) {
			device->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		}
		else {
			device->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 127, 127, 127), 1, 0);
		}
		font->DrawTextW(NULL, text.c_str(), -1, &crd, format, color);
	}
}

void Selectable::Update(wchar_t key)
{
}

void Selectable::SetHower(POINT m)
{
	hower = (m.x >= crd.left && m.x <= crd.right && m.y >= crd.top && m.y <= crd.bottom);
}

void Selectable::SetWait(bool wait)
{
}

void Selectable::SetVisible(bool visible)
{
	this->visible = visible;
}

void Selectable::SetInput(std::wstring option)
{
}

void Selectable::SetOptionText(int optioni, std::wstring text)
{
}

void Selectable::SetPos(int left, int right, int top, int bottom, int height, int nx)
{
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	font->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

void Selectable::SetEditable(bool editable)
{
}

void Selectable::SetText(std::wstring text)
{
	this->text = text;
}

bool Selectable::SetSelected(int selected)
{
	return false;
}

void Selectable::ReloadWorlds(LPDIRECT3DDEVICE9 device)
{
}

void Selectable::AddOption(std::wstring)
{
}

void Selectable::SetTitle(std::wstring text)
{
}

void Selectable::ResetObjects()
{
	font->OnLostDevice();
}

void Selectable::LoadObjects()
{
	font->OnResetDevice();
}

bool Selectable::GetClicked(POINT m)
{
	if (m.x > crd.left && m.x < crd.right && m.y > crd.top && m.y < crd.bottom)
		return true;
	return false;
}

bool Selectable::GetVisible()
{
	return visible;
}

bool Selectable::GetPausedScreen()
{
	return pausedScreen;
}

int Selectable::GetSelected()
{
	return 0;
}

int Selectable::GetClickedBtn(POINT m)
{
	return 0;
}

std::string Selectable::WhatIsThis()
{
	return "Selectable";
}

std::wstring Selectable::GetOptionText(int optioni)
{
	return L"";
}

std::wstring Selectable::GetTarget()
{
	return target;
}

std::wstring Selectable::GetUIClass()
{
	return UIclass;
}

std::wstring Selectable::GetClickedWorld(POINT m)
{
	return L"";
}

std::wstring Selectable::GetInput()
{
	return L"";
}

std::wstring Selectable::GetTitle()
{
	return text;
}

std::wstring Selectable::GetName()
{
	return name;
}

Editable::Editable(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring target, std::wstring text)
{
	this->device = device;
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	this->text = text;
	this->target = target;
	this->UIclass = UIclass;
	this->visible = visible;
	this->pausedScreen = pausedScreen;
	this->name = name;
	color = D3DCOLOR_XRGB(r, g, b);

	if (hpos == L"LEFT" && vpos == L"TOP")
		format = DT_LEFT && DT_TOP;
	else if (hpos == L"CENTER" && vpos == L"TOP")
		format = DT_CENTER | DT_TOP;
	else if (hpos == L"RIGHT" && vpos == L"TOP")
		format = DT_RIGHT | DT_TOP;
	else if (hpos == L"LEFT" && vpos == L"CENTER")
		format = DT_LEFT | DT_VCENTER;
	else if (hpos == L"CENTER" && vpos == L"CENTER")
		format = DT_CENTER | DT_VCENTER;
	else if (hpos == L"RIGHT" && vpos == L"CENTER")
		format = DT_RIGHT | DT_VCENTER;
	else if (hpos == L"LEFT" && vpos == L"BOTTOM")
		format = DT_LEFT | DT_BOTTOM;
	else if (hpos == L"CENTER" && vpos == L"BOTTOM")
		format = DT_CENTER | DT_BOTTOM;
	else if (hpos == L"RIGHT" && vpos == L"BOTTOM")
		format = DT_RIGHT | DT_BOTTOM;

	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

Editable::~Editable()
{
	font->Release();
}

void Editable::Draw()
{
	std::wstring outText = L"";
	if (inputText.length() == 0) {
		outText = text + L": ";
	}
	outText += inputText;
	if (inputText.length() != charLimit && editable)
		outText += L"_";
	if (visible) {
		D3DRECT rect;
		rect.x1 = crd.left;
		rect.x2 = crd.right;
		rect.y1 = crd.top;
		rect.y2 = crd.bottom;

		if (!hower) {
			device->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		}
		else {
			device->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 127, 127, 127), 1, 0);
		}
		font->DrawTextW(NULL, outText.c_str(), -1, &crd, format, color);
	}
}

void Editable::Update(wchar_t key)
{
	if (editable) {
		std::wstring conStr = L"";
		conStr += key;

		if (key == VK_BACK) {
			std::wstring tmpText = L"";
			for (int i = 0; i < inputText.length(); i++) {
				if (i < inputText.length() - 1)
					tmpText += inputText[i];
			}
			inputText = tmpText;
		}
		else if (key == VK_RETURN) {
			editable = false;
		}
		else {
			if (inputText.length() < charLimit) {
				inputText += conStr;
			}
		}
	}
}

void Editable::SetHower(POINT m)
{
	if (editable == false) {
		hower = (m.x > crd.left && m.x < crd.right && m.y > crd.top && m.y < crd.bottom);
	}
}

void Editable::SetVisible(bool visible)
{
	editable = false;
	inputText = L"";
	this->visible = visible;
}

void Editable::SetWait(bool wait)
{
	this->wait = wait;
}

void Editable::SetInput(std::wstring option)
{
	inputText = option;
}

void Editable::SetEditable(bool editable)
{
	this->editable = editable;
}

void Editable::SetOptionText(int optioni, std::wstring text)
{
}

void Editable::SetPos(int left, int right, int top, int bottom, int height, int nx)
{
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	font->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &font);
}

void Editable::SetText(std::wstring text)
{
	this->text = text;
}

bool Editable::SetSelected(int selected)
{
	return false;
}

void Editable::ReloadWorlds(LPDIRECT3DDEVICE9 device)
{
}

void Editable::AddOption(std::wstring)
{
}

void Editable::SetTitle(std::wstring text)
{
}

void Editable::ResetObjects()
{
	font->OnLostDevice();
}

void Editable::LoadObjects()
{
	font->OnResetDevice();
}

bool Editable::GetClicked(POINT m)
{
	if (m.x > crd.left && m.x < crd.right && m.y > crd.top && m.y < crd.bottom)
		return true;
	return false;
}

bool Editable::GetVisible()
{
	return visible;
}

bool Editable::GetPausedScreen()
{
	return pausedScreen;
}

int Editable::GetSelected()
{
	return editable;
}

int Editable::GetClickedBtn(POINT m)
{
	return 0;
}

std::string Editable::WhatIsThis()
{
	return "Editable";
}

std::wstring Editable::GetOptionText(int optioni)
{
	return L"";
}

std::wstring Editable::GetTarget()
{
	return target;
}

std::wstring Editable::GetUIClass()
{
	return UIclass;
}

std::wstring Editable::GetTitle()
{
	return L"";
}

std::wstring Editable::GetClickedWorld(POINT m)
{
	return L"";
}

std::wstring Editable::GetInput()
{
	return inputText;
}

std::wstring Editable::GetName()
{
	return name;
}

ListOption::ListOption(LPDIRECT3DDEVICE9 device, std::wstring name, bool pausedScreen, int left, int right, int top, int bottom, int height, std::wstring vpos, std::wstring hpos, int r, int g, int b, bool visible, std::wstring UIclass, std::wstring target, std::wstring title, int wx)
{
	this->device = device;
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;
	this->height = height;
	this->title = title;
	this->target = target;
	this->UIclass = UIclass;
	this->visible = visible;
	this->pausedScreen = pausedScreen;
	this->name = name;
	color = D3DCOLOR_XRGB(r, g, b);

	if (hpos == L"LEFT" && vpos == L"TOP")
		format = DT_LEFT && DT_TOP;
	else if (hpos == L"CENTER" && vpos == L"TOP")
		format = DT_CENTER | DT_TOP;
	else if (hpos == L"RIGHT" && vpos == L"TOP")
		format = DT_RIGHT | DT_TOP;
	else if (hpos == L"LEFT" && vpos == L"CENTER")
		format = DT_LEFT | DT_VCENTER;
	else if (hpos == L"CENTER" && vpos == L"CENTER")
		format = DT_CENTER | DT_VCENTER;
	else if (hpos == L"RIGHT" && vpos == L"CENTER")
		format = DT_RIGHT | DT_VCENTER;
	else if (hpos == L"LEFT" && vpos == L"BOTTOM")
		format = DT_LEFT | DT_BOTTOM;
	else if (hpos == L"CENTER" && vpos == L"BOTTOM")
		format = DT_CENTER | DT_BOTTOM;
	else if (hpos == L"RIGHT" && vpos == L"BOTTOM")
		format = DT_RIGHT | DT_BOTTOM;

	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &titlefont);
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &leftbtnfont);
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &rightbtnfont);
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &optionfont);

	titleTexRect.left = 0;
	titleTexRect.right = (crd.right - crd.left) / 2;
	titleTexRect.top = 0;
	titleTexRect.bottom = crd.bottom - crd.top;
	titleRect.top = crd.top;
	titleRect.bottom = crd.bottom;
	titleRect.left = crd.left;
	titleRect.right = crd.left + (crd.right - crd.left) / 2;

	leftBtnRect.left = crd.left + (crd.right - crd.left) / 2;
	leftBtnRect.right = crd.left + (crd.right - crd.left) / 2 + (wx / 100 * 4);
	leftBtnRect.top = crd.top;
	leftBtnRect.bottom = crd.bottom;
	leftBtnTexRect.left = (crd.right - crd.left) / 2;
	leftBtnTexRect.right = (crd.right - crd.left) / 2 + (wx / 100 * 4);
	leftBtnTexRect.top = 0;
	leftBtnTexRect.bottom = crd.bottom - crd.top;

	optionRect.left = crd.left + (crd.right - crd.left) / 2 + (wx / 100 * 4);
	optionRect.right = crd.right - (wx / 100 * 4);
	optionRect.top = crd.top;
	optionRect.bottom = crd.bottom;
	optionTexRect.left = (crd.right - crd.left) / 2 + (wx / 100 * 4);
	optionTexRect.right = (crd.right - crd.left) - (wx / 100 * 4);
	optionTexRect.top = 0;
	optionTexRect.bottom = crd.bottom - crd.top;

	rightBtnRect.left = crd.right - (wx / 100 * 4);
	rightBtnRect.right = crd.right;
	rightBtnRect.top = crd.top;
	rightBtnRect.bottom = crd.bottom;
	rightBtnTexRect.left = (crd.right - crd.left) - (wx / 100 * 4);
	rightBtnTexRect.right = crd.right - crd.left;
	rightBtnTexRect.top = 0;
	rightBtnTexRect.bottom = crd.bottom - crd.top;
}

ListOption::~ListOption()
{
	titlefont->Release();
	leftbtnfont->Release();
	rightbtnfont->Release();
	optionfont->Release();
}

void ListOption::Draw()
{
	if (visible) {
		//TITLE
		D3DRECT rectTitle;
		rectTitle.x1 = titleTexRect.left + titleRect.left;
		rectTitle.x2 = titleTexRect.right + titleRect.left;
		rectTitle.y1 = titleTexRect.top + titleRect.top;
		rectTitle.y2 = titleTexRect.bottom + titleRect.top;

		device->Clear(1, &rectTitle, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		titlefont->DrawTextW(NULL, title.c_str(), -1, &titleRect, format, color);

		//LEFT
		D3DRECT rectLeft;
		rectLeft.x1 = leftBtnTexRect.left + titleRect.left;
		rectLeft.x2 = leftBtnTexRect.right + titleRect.left;
		rectLeft.y1 = leftBtnTexRect.top + titleRect.top;
		rectLeft.y2 = leftBtnTexRect.bottom + titleRect.top;

		if (!leftHower) {
			device->Clear(1, &rectLeft, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		}
		else {
			device->Clear(1, &rectLeft, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 127, 127, 127), 1, 0);
		}

		if (selected >= 1)
			leftbtnfont->DrawTextA(NULL, "<", -1, &leftBtnRect, DT_CENTER | DT_VCENTER, color);

		//OPTION
		D3DRECT rectOption;
		rectOption.x1 = optionTexRect.left + titleRect.left;
		rectOption.x2 = optionTexRect.right + titleRect.left;
		rectOption.y1 = optionTexRect.top + titleRect.top;
		rectOption.y2 = optionTexRect.bottom + titleRect.top;

		device->Clear(1, &rectOption, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		optionfont->DrawTextW(NULL, options[selected].c_str(), -1, &optionRect, DT_CENTER | DT_VCENTER, color);

		//RIGHT
		D3DRECT rectRight;
		rectRight.x1 = rightBtnTexRect.left + titleRect.left;
		rectRight.x2 = rightBtnTexRect.right + titleRect.left;
		rectRight.y1 = rightBtnTexRect.top + titleRect.top;
		rectRight.y2 = rightBtnTexRect.bottom + titleRect.top;

		if (!rightHower) {
			device->Clear(1, &rectRight, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 195, 195, 195), 1, 0);
		}
		else {
			device->Clear(1, &rectRight, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 127, 127, 127), 1, 0);
		}

		if (selected < options.size() - 1)
			rightbtnfont->DrawTextA(NULL, ">", -1, &rightBtnRect, DT_CENTER | DT_VCENTER, color);
	}
}

void ListOption::Update(wchar_t key)
{
}

void ListOption::SetHower(POINT m)
{
	if (selected >= 1) {
		leftHower = (m.x > leftBtnRect.left && m.x < leftBtnRect.right && m.y > leftBtnRect.top && m.y < leftBtnRect.bottom);
	}
	else {
		leftHower = false;
	}
	if (selected < options.size() - 1) {
		rightHower = (m.x > rightBtnRect.left && m.x < rightBtnRect.right && m.y > rightBtnRect.top && m.y < rightBtnRect.bottom);
	}
	else {
		rightHower = false;
	}
}

void ListOption::SetVisible(bool visible)
{
	this->visible = visible;
}

void ListOption::SetWait(bool wait)
{
}

void ListOption::SetEditable(bool editable)
{
}

void ListOption::SetInput(std::wstring option)
{
	for (int i = 0; i < options.size(); i++) {
		if (options[i] == option) {
			selected = i;
			break;
		}
	}
}

void ListOption::SetOptionText(int optioni, std::wstring text)
{
	options[optioni] = text;
}

void ListOption::SetPos(int left, int right, int top, int bottom, int height, int nx)
{
	crd.left = left;
	crd.right = right;
	crd.bottom = bottom;
	crd.top = top;

	titleTexRect.left = 0;
	titleTexRect.right = (crd.right - crd.left) / 2;
	titleTexRect.top = 0;
	titleTexRect.bottom = crd.bottom - crd.top;
	titleRect.top = crd.top;
	titleRect.bottom = crd.bottom;
	titleRect.left = crd.left;
	titleRect.right = crd.left + (crd.right - crd.left) / 2;

	leftBtnRect.left = crd.left + (crd.right - crd.left) / 2;
	leftBtnRect.right = crd.left + (crd.right - crd.left) / 2 + (nx / 100 * 4);
	leftBtnRect.top = crd.top;
	leftBtnRect.bottom = crd.bottom;
	leftBtnTexRect.left = (crd.right - crd.left) / 2;
	leftBtnTexRect.right = (crd.right - crd.left) / 2 + (nx / 100 * 4);
	leftBtnTexRect.top = 0;
	leftBtnTexRect.bottom = crd.bottom - crd.top;

	optionRect.left = crd.left + (crd.right - crd.left) / 2 + (nx / 100 * 4);
	optionRect.right = crd.right - (nx / 100 * 4);
	optionRect.top = crd.top;
	optionRect.bottom = crd.bottom;
	optionTexRect.left = (crd.right - crd.left) / 2 + (nx / 100 * 4);
	optionTexRect.right = (crd.right - crd.left) - (nx / 100 * 4);
	optionTexRect.top = 0;
	optionTexRect.bottom = crd.bottom - crd.top;

	rightBtnRect.left = crd.right - (nx / 100 * 4);
	rightBtnRect.right = crd.right;
	rightBtnRect.top = crd.top;
	rightBtnRect.bottom = crd.bottom;
	rightBtnTexRect.left = (crd.right - crd.left) - (nx / 100 * 4);
	rightBtnTexRect.right = crd.right - crd.left;
	rightBtnTexRect.top = 0;
	rightBtnTexRect.bottom = crd.bottom - crd.top;
	this->height = height;
	titlefont->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &titlefont);
	leftbtnfont->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &leftbtnfont);
	rightbtnfont->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &rightbtnfont);
	optionfont->Release();
	D3DXCreateFont(device, height, 0, 0, 1, 0, 162, NULL, NULL, NULL, L"arial", &optionfont);
}

void ListOption::SetText(std::wstring text)
{
}

bool ListOption::SetSelected(int selected)
{
	if (selected >= 0 && selected < options.size()) {
		this->selected = selected;
		return true;
	}
	return false;
}

void ListOption::ReloadWorlds(LPDIRECT3DDEVICE9 device)
{
}

void ListOption::AddOption(std::wstring option)
{
	options.push_back(option);
}

void ListOption::SetTitle(std::wstring text)
{
	title = text;
}

void ListOption::ResetObjects()
{
	titlefont->OnLostDevice();
	leftbtnfont->OnLostDevice();
	rightbtnfont->OnLostDevice();
	optionfont->OnLostDevice();
}

void ListOption::LoadObjects()
{
	titlefont->OnResetDevice();
	leftbtnfont->OnResetDevice();
	rightbtnfont->OnResetDevice();
	optionfont->OnResetDevice();
}

bool ListOption::GetClicked(POINT m)
{
	return false;
}

bool ListOption::GetVisible()
{
	return visible;
}

bool ListOption::GetPausedScreen()
{
	return pausedScreen;
}

int ListOption::GetSelected()
{
	return selected;
}

int ListOption::GetClickedBtn(POINT m)
{
	if (m.x > leftBtnRect.left && m.x < leftBtnRect.right && m.y > leftBtnRect.top && m.y < leftBtnRect.bottom)
		return 1;
	else if (m.x > rightBtnRect.left && m.x < rightBtnRect.right && m.y > rightBtnRect.top && m.y < rightBtnRect.bottom)
		return 2;
	return 0;
}

std::wstring ListOption::GetOptionText(int optioni)
{
	return options[optioni];
}

std::string ListOption::WhatIsThis()
{
	return "ListOption";
}

std::wstring ListOption::GetTitle()
{
	return title;
}

std::wstring ListOption::GetTarget()
{
	return target;
}

std::wstring ListOption::GetUIClass()
{
	return UIclass;
}

std::wstring ListOption::GetClickedWorld(POINT m)
{
	return L"";
}

std::wstring ListOption::GetInput()
{
	return options[selected];
}

std::wstring ListOption::GetName()
{
	return name;
}
