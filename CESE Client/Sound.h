#pragma once

#include <xaudio2.h>
#include <x3daudio.h>
#include <string>
#include <memory>
#include <thread>
#include <fstream>

struct SOUNDBUFFER {
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
};

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
    HANDLE hBufferEndEvent;
    VoiceCallback() : hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)) {}
    ~VoiceCallback() { CloseHandle(hBufferEndEvent); }

    //Called when the voice has just finished playing a contiguous audio stream.
    void OnStreamEnd() {}

    //Unused methods are stubs
    void OnVoiceProcessingPassEnd() { }
    void OnVoiceProcessingPassStart(UINT32 SamplesRequired) {    }
    void OnBufferEnd(void* pBufferContext) { SetEvent(hBufferEndEvent);  }
    void OnBufferStart(void* pBufferContext) {    }
    void OnLoopEnd(void* pBufferContext) {    }
    void OnVoiceError(void* pBufferContext, HRESULT Error) { }
};

class Sound
{
public:
	Sound();
	~Sound();
	bool Init(HWND hwnd);
	SOUNDBUFFER* CreateSound(std::wstring file);
    void PlayThread(SOUNDBUFFER* buffer);
    void Play3DThread(SOUNDBUFFER* buffer, X3DAUDIO_LISTENER listener2, X3DAUDIO_EMITTER emitter2);
	void Play(SOUNDBUFFER* buffer);
    void Play3D(SOUNDBUFFER* buffer, float emX, float emY, float emZ, float emLookX, float emLookY, float emLookZ);
    void UpdateListener(float lisX, float lisY, float lisZ, float lisLookX, float lisLookY, float lisLookZ);
    void UpdateSound(X3DAUDIO_LISTENER listener2, X3DAUDIO_EMITTER emitter2, IXAudio2SourceVoice* pSourceVoice, X3DAUDIO_DSP_SETTINGS DSPSettings, SOUNDBUFFER* buffer, bool* finished);
private:
	IXAudio2* pXAudio2 = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;
    X3DAUDIO_HANDLE X3DInstance;
    float lisX, lisY, lisZ, lisLookX, lisLookY, lisLookZ;
};
