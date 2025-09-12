#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include "json.hpp"

using json = nlohmann::json;

class Net
{
public:
	Net();
	~Net();
	bool Init(std::wstring nick, std::wstring url, std::wstring& map, float& x, float& y, float& z, int& exitCode);
	bool LeaveServer();
	json GetData(int& recvBytes);
	json GetTCP(int& recvBytes);
	bool SendData(float x, float y, float z, float yaw, std::wstring nick);
	bool SendBullet(float x, float y, float z, float lx, float ly, float lz);
private:
	std::string ws2s(const std::wstring& str);
	std::wstring s2ws(const std::string& str);
};

