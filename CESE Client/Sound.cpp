#include "Sound.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}


HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
} 


Sound::Sound()
{
}

Sound::~Sound()
{
    pMasterVoice = nullptr;
    if(pXAudio2)
        pXAudio2->Release();
    pXAudio2 = nullptr;
    CoUninitialize();
}

bool Sound::Init(HWND hwnd)
{
    HRESULT hr;
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
		return false;

	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return false;

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return false;


    DWORD channelMask;
    pMasterVoice->GetChannelMask(&channelMask);
    
    if (FAILED(X3DAudioInitialize(channelMask, X3DAUDIO_SPEED_OF_SOUND, X3DInstance)))
        return false;

	return true;
}

SOUNDBUFFER* Sound::CreateSound(std::wstring file)
{
    HRESULT hr = 0;

    WAVEFORMATEXTENSIBLE wfx = { 0 };
    XAUDIO2_BUFFER buffer = { 0 };
    SOUNDBUFFER* soundBuffer = new SOUNDBUFFER();

    // Open the file
    HANDLE hFile = CreateFile(
        file.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return nullptr;

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return nullptr;

    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return nullptr;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

    //fill out the audio data buffer with the contents of the fourccDATA chunk
    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

    soundBuffer->buffer = buffer;
    soundBuffer->wfx = wfx;

    return soundBuffer;
}

void Sound::PlayThread(SOUNDBUFFER* buffer) {
    IXAudio2SourceVoice* pSourceVoice;

    VoiceCallback voiceCallback;
    if (FAILED(pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&buffer->wfx,
        0, XAUDIO2_DEFAULT_FREQ_RATIO, &voiceCallback, NULL, NULL))) return;

    if (FAILED(pSourceVoice->SubmitSourceBuffer(&buffer->buffer)))
        return;

    if (FAILED(pSourceVoice->Start(0)))
        return;

    WaitForSingleObjectEx(voiceCallback.hBufferEndEvent, INFINITE, TRUE);

    pSourceVoice->DestroyVoice();
    pSourceVoice = nullptr;
}

void Sound::Play3DThread(SOUNDBUFFER* buffer, X3DAUDIO_LISTENER listener2, X3DAUDIO_EMITTER emitter2)
{
    IXAudio2SourceVoice* pSourceVoice;

    VoiceCallback voiceCallback;
    if (FAILED(pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&buffer->wfx,
        0, XAUDIO2_DEFAULT_FREQ_RATIO, &voiceCallback, NULL, NULL))) return;

    if (FAILED(pSourceVoice->SubmitSourceBuffer(&buffer->buffer)))
        return;

    pSourceVoice->SetVolume(5.0f);

    XAUDIO2_VOICE_DETAILS details;
    pMasterVoice->GetVoiceDetails(&details);
    XAUDIO2_VOICE_DETAILS details2;
    pSourceVoice->GetVoiceDetails(&details2);

    constexpr float LEFT_AZIMUTH = 3 * X3DAUDIO_PI / 2;
    constexpr float RIGHT_AZIMUTH = X3DAUDIO_PI / 2;
    constexpr float FRONT_LEFT_AZIMUTH = 7 * X3DAUDIO_PI / 4;
    constexpr float FRONT_RIGHT_AZIMUTH = X3DAUDIO_PI / 4;
    constexpr float FRONT_CENTER_AZIMUTH = 0.0f;
    constexpr float LOW_FREQUENCY_AZIMUTH = X3DAUDIO_2PI;
    constexpr float BACK_LEFT_AZIMUTH = 5 * X3DAUDIO_PI / 4;
    constexpr float BACK_RIGHT_AZIMUTH = 3 * X3DAUDIO_PI / 4;
    constexpr float BACK_CENTER_AZIMUTH = X3DAUDIO_PI;

    float c_channelAzimuths[9][8] =
    {
        /* 0 */   { 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
        /* 1 */   { 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
        /* 2 */   { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
        /* 2.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, LOW_FREQUENCY_AZIMUTH, 0.f, 0.f, 0.f, 0.f, 0.f },
        /* 4.0 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f, 0.f, 0.f },
        /* 4.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f, 0.f },
        /* 5.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f },
        /* 6.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, BACK_CENTER_AZIMUTH, 0.f },
        /* 7.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, LEFT_AZIMUTH, RIGHT_AZIMUTH }
    };

    emitter2.ChannelCount = buffer->wfx.Format.nChannels;

    emitter2.ChannelRadius = 1.f;

    emitter2.pChannelAzimuths = c_channelAzimuths[buffer->wfx.Format.nChannels];

    emitter2.CurveDistanceScaler = 1.0f;
    emitter2.DopplerScaler = 1.0f;
    emitter2.InnerRadius = 2.0f;
    emitter2.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;

    X3DAUDIO_DSP_SETTINGS DSPSettings = { 0 };
    FLOAT32* matrix = new FLOAT32[details.InputChannels * details2.InputChannels];
    DSPSettings.SrcChannelCount = emitter2.ChannelCount;
    DSPSettings.DstChannelCount = details.InputChannels;
    DSPSettings.pMatrixCoefficients = matrix;

    bool finished = false;
    std::thread t(&Sound::UpdateSound, this, listener2, emitter2, pSourceVoice, DSPSettings, buffer, &finished);
    t.detach();

    if (FAILED(pSourceVoice->Start(0)))
        return;

    WaitForSingleObjectEx(voiceCallback.hBufferEndEvent, INFINITE, TRUE);

    finished = true;

    Sleep(1000);

    pSourceVoice->DestroyVoice();
    pSourceVoice = nullptr;
    delete[] matrix;
}

void Sound::Play(SOUNDBUFFER* buffer)
{
    std::thread t(&Sound::PlayThread, this, buffer);
    t.detach();
}

void Sound::Play3D(SOUNDBUFFER* buffer, float emX, float emY, float emZ, float emLookX, float emLookY, float emLookZ)
{
    X3DAUDIO_LISTENER listener2 = {};
    X3DAUDIO_EMITTER emitter2 = {};

    listener2.Position = X3DAUDIO_VECTOR(-lisX, lisZ, lisY);
    listener2.OrientFront = X3DAUDIO_VECTOR(-lisLookX, lisLookZ, lisLookY);
    listener2.Velocity = X3DAUDIO_VECTOR(0.0f, 0.0f, 0.0f);
    listener2.OrientTop = X3DAUDIO_VECTOR(0.0f, 0.0f, 1.0f);

    emitter2.Position = X3DAUDIO_VECTOR(0.0f, 0.0f, 0.0f);
    emitter2.Velocity = X3DAUDIO_VECTOR(0.0f, 0.0f, 0.0f);
    emitter2.OrientFront = X3DAUDIO_VECTOR(0.0f, 1.0f, 0.0f);
    emitter2.OrientTop = X3DAUDIO_VECTOR(0.0f, 0.0f, 1.0f);
    std::thread t(&Sound::Play3DThread, this, buffer, listener2, emitter2);
    t.detach();
}

void Sound::UpdateListener(float lisX, float lisY, float lisZ, float lisLookX, float lisLookY, float lisLookZ)
{
    this->lisX = lisX;
    this->lisY = lisY;
    this->lisZ = lisZ;
    this->lisLookX = lisLookX;
    this->lisLookY = lisLookY;
    this->lisLookZ = lisLookZ;
}

void Sound::UpdateSound(X3DAUDIO_LISTENER listener2, X3DAUDIO_EMITTER emitter2, IXAudio2SourceVoice* pSourceVoice, X3DAUDIO_DSP_SETTINGS DSPSettings, SOUNDBUFFER* buffer, bool* finished)
{
    while (true) {
        XAUDIO2_VOICE_DETAILS details;
        pMasterVoice->GetVoiceDetails(&details);

        listener2.Position = X3DAUDIO_VECTOR(-lisX, lisZ, lisY);
        listener2.OrientFront = X3DAUDIO_VECTOR(-lisLookX, lisLookZ, lisLookY);

        X3DAudioCalculate(X3DInstance, &listener2, &emitter2,
            X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB,
            &DSPSettings);

        pSourceVoice->SetFrequencyRatio(DSPSettings.DopplerFactor);
        pSourceVoice->SetOutputMatrix(pMasterVoice, buffer->wfx.Format.nChannels, details.InputChannels, DSPSettings.pMatrixCoefficients);
        XAUDIO2_FILTER_PARAMETERS FilterParameters = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * DSPSettings.LPFDirectCoefficient), 1.0f };
        pSourceVoice->SetFilterParameters(&FilterParameters);
        if (*finished)
            break;
        Sleep(1000 / 300);
    }
}
