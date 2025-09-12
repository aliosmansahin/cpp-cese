#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <thread>
#include <memory>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <string>
#include "Graphics.h"
#include "Net.h"
#include "UI.h"
#include "Sound.h"
#include "Logger.h"
#include "Shader.h"

#define FVF (D3DFVF_XYZ | D3DFVF_TEX1)

using namespace std;

struct VERTEX {
	float x, y, z, u, v;
};

struct BackgroundVertex {
	float x, y, z, rwz;
	D3DCOLOR color;
};

struct OBJ {
	float bottom, left, top, right;
};

struct OBJECTS {
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 VB;
	LPDIRECT3DINDEXBUFFER9 IB;
	int verticesSize;
	int indicesSize;
	~OBJECTS() {
		if (texture)
			texture->Release();
		if (VB)
			VB->Release();
		if (IB)
			IB->Release();
	}
};

struct ENEMY {
	float x, y, z, YAW;
	std::shared_ptr<OBJECTS> objs;
};

struct NKDELEMENT {
	std::wstring nick;
	int killCount, deadCount;
	LPD3DXFONT font;
	RECT nickRect, killRect, deadRect;
};

struct COLLOBJ {
	float front, back, left, right, top, bottom;
};

struct Crosshair {
	float length, weight, space, outline;
	D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 0);
	std::wstring name;
};

class Game
{
public:
	Game();
	~Game();
	bool Init(HWND hwnd, MSG msg, bool windowed, int wndw, int wndh, bool vsync, std::string verNumber, float sens, bool additional);
	void GameLoop();
	void Draw();
	void DrawMap();
	void DrawEnemies();
	void DrawHealth();
	void DrawAdditionalData();
	void DrawOnlineAdditionalData();
	void DrawOnlineData();
	void DrawGamePausedBackground();
	void Update();
	void UpdateLoadThreads();
	void ProceedIsDead();
	void ProceedMovement();
	void Run();
	void ChangeResolution();
	void ProceedDeviceLost();
	void KeyboardInput();
	void MouseInput();
	void SetAllMatrixIdentity();
	void SetFocusedWindow(bool focused);
	void CalculateDeltaTime();
	void CalculateCollision();
	void RecvTCPThread();
	void RecvThread();
	void SetFireEnable(bool enable);
	bool GetFireEnable();
	void SendBullet();
	void SetBulletThread();
	void ShowCursorG();
	void HideCursorG();
	void Spawn();
	bool LoadMainMenu();
	bool LoadGame(bool online, std::wstring connURL);
	void UpdateEditable(wchar_t key);
	void HowerUI(POINT m);
	void ClickUI();
	bool LoadMain();
	void LoadThread();
	void LoadConnThread();
	void LoadOffThread();
	void PauseMenu();
	bool GetPaused();
	void SetPaused(bool paused);
	void CalculateFPS();
	void MouseVisible();
	void ResetObjects();
	void LoadObjects();
	bool GetLoaded();
	int  GetState();
	void DrawCrosshair(int centerx, int centery);
	bool LoadCrosshairs();
	bool SaveCrosshairs();
	void LoadBackgroundBuffers(LPDIRECT3DVERTEXBUFFER9& vb, LPDIRECT3DINDEXBUFFER9& ib, LPD3DXFONT font, RECT* rect, std::wstring text);
	void LoadPauseBackgroundBuffers(LPDIRECT3DVERTEXBUFFER9& vb, LPDIRECT3DINDEXBUFFER9& ib);
	void LoadAllBackgroundBuffers();
	void SetRects();
	void SetCrosshairSettings(int uiindex);
	void ProceedListOptions(int uiindex);
	bool LoadCharBuffers();
	void LoadFonts();
	void SetPosOfUIs(int i);
	void ReleaseFonts();
	void LoadUIs();
	bool LoadSounds();
	void SetRenderTargets();
	std::string ws2s(const std::wstring& str);
	std::wstring s2ws(const std::string& str);
private:
	std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> FPSlastTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> frameStart = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> fireStart = std::chrono::steady_clock::now();
	Sound* sound = new Sound();
	Shader* mainShader = new Shader();
	Shader* backgroundShader = new Shader();
	SOUNDBUFFER* clickBuffer = nullptr;
	SOUNDBUFFER* fireBuffer = nullptr;
	float deltaTime = 0.0f;
	float sensitivity = 1.0f;
	float YAW = 90.0f, PITCH = 0.0f;
	float aimDown = -30.0f;
	float gravity = -20.0f;
	float velocityY = 0.0f;
	float angle = 0.0f;
	float velocityScale = 10.0f;
	float velocityV = 0.0f;
	float velocityH = 0.0f;
	float velocityMotion = 30.0f;
	float jumpStopMotion = 100.0f;
	float bunnyMotion = 2.0f;
	float velocityMax = 7.0f;
	float topMapNamePosSize = 0.0f;
	float topMapNamePosVelocity = 2000.0f;
	float walkMoveDistance = 12.0f;
	float walkMoveSpeed = 2.0f;
	float tmpPitch = 0.0f;
	int ping = 0.0f;
	int spawnMinX = 0;
	int spawnMaxX = 0;
	int spawnMinZ = 0;
	int spawnMaxZ = 0;
	int spawnY = 0;
	int currentCrosshair = 0;
	bool wPressed = false;
	bool sPressed = false;
	bool aPressed = false;
	bool dPressed = false;
	bool touched = false;
	bool touchedS = false;
	bool stopped = true;
	bool firstMouse = true;
	bool jumpEnable = false;
	bool viewMaps = false;
	bool focusedWindow = true;
	bool gamePaused = false;
	bool spawnable = false;
	bool showScores = false;
	bool connWait = false;
	bool connFailed = false;
	bool windowed = false;
	bool fireForce = false;
	bool fixFireForce = false;
	bool vsync = false;
	bool isDead = false;
	bool mouseChange = false;
	bool releaseEnemys = false;
	bool changeResolution = false;
	bool fireEnable = false;
	bool changedResolutionSetting = false;
	bool loaded = false;
	bool deviceLost = false;
	bool firstLoad = true;
	bool online = false;
	bool collX = false, collY = false, collZ = false;
	bool leaveServerWait = false;
	bool serverError = false;
	bool leaving = false;
	bool gameFinished = false;
	bool loadThreadError = false;
	bool setExit = false;
	bool showCrossInSettings = false;
	bool loadThread = true;
	bool loadOnlineThread = false;
	bool showAdditionalData = false;
	bool stoppingJump = false;
	int wndw = 0, wndh = 0;
	int twndw = 0, twndh = 0;
	int state = -1;
	int tmpFPS = -1;
	int FPS = 0;
	int healt = 100;
	int procCount = 0;
	int mdes = 0;
	int frameIndex = 0;
	int recvBytes = 0;
	int recvTCPBytes = 0;
	int lastRestartTime = 10;
	POINT lastMouse;
	std::wstring mapName = L"Map1";
	std::wstring nick = L"";
	std::wstring connURL = L"";
	std::wstring maxVertexShaderVer = L"";
	std::wstring maxPixelShaderVer = L"";
	std::wstring tmpSensitivity = L"";
	std::string verText = "";
	OBJ* collCoords = nullptr;
	Graphics* graphics = nullptr;
	std::unique_ptr<Net> net;
	std::vector<std::unique_ptr<OBJECTS>> objects;
	std::vector<COLLOBJ> collObjects;
	std::vector<ENEMY> enemys;
	std::vector<NKDELEMENT> nkds;
	std::vector<Crosshair> crosshairs;
	std::vector<std::wstring> texPaths;
	std::vector<std::unique_ptr<UI>> UIs;
	std::shared_ptr<OBJECTS> tmpEnemy;
	LPD3DXFONT nkdTmpFont = nullptr;
	HWND hwnd = NULL;
	MSG msg = { 0 };
	D3DXVECTOR3 pos, tmpPos, lookAt, tmpLookAt, flyLookAt, up;
	LPD3DXFONT healtFont = nullptr;
	LPD3DXFONT FPSFont = nullptr;
	LPD3DXFONT PosFont = nullptr;
	RECT healtRect = { 0 };
	RECT FPSRect = { 0 };
	RECT XRect = { 0 };
	RECT YRect = { 0 };
	RECT ZRect = { 0 };
	RECT pkgRect = { 0 };
	RECT restartTimeRect = { 0 };
	RECT pingRect = { 0 };
	LPDIRECT3DVERTEXBUFFER9 healtBackgroundVB = nullptr;
	LPDIRECT3DINDEXBUFFER9 healtBackgroundIB = nullptr;
	LPDIRECT3DVERTEXBUFFER9 pauseBackgroundVB = nullptr;
	LPDIRECT3DINDEXBUFFER9 pauseBackgroundIB = nullptr;
	LPDIRECT3DVERTEXBUFFER9 timeBackgroundVB = nullptr;
	LPDIRECT3DINDEXBUFFER9 timeBackgroundIB = nullptr;
	OBJECTS* skyboxObjects = nullptr;
};

