#include "TMM_AudioOutput.h"


namespace TMM
{

	AudioOutput::AudioOutput() :
		mpXAudio2(nullptr),
		mIsInit(false)
	{

	}

	AudioOutput::~AudioOutput()
	{

	}

	ERROR_CODE AudioOutput::Init()
	{
		HRESULT hr;

		hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr)) return hr;

		hr = XAudio2Create(&mpXAudio2);
		if (FAILED(hr)) return hr;
		
		hr = mpXAudio2->CreateMasteringVoice(&mpMaster);
		if (FAILED(hr)) return hr;

		mIsInit = true;
		return 0;
	}

	ERROR_CODE AudioOutput::CreateAudio(AudioData* pOut)
	{
		if (pOut == nullptr) return 1;
		return 0;
	}

	ERROR_CODE AudioOutput::CreateAudioFromFile(const char* file, AudioData* pOut)
	{
		if (pOut == nullptr) return 1;

		pOut->LoadFromFile(file);
		pOut->CreateSource(this);
		return 0;
	}

	ERROR_CODE AudioOutput::CreateAudioFromContent(AudioFileContent* pContent, AudioData* pOut)
	{
		if (pOut == nullptr) return 1;

		pOut->LoadFromContent(pContent);
		pOut->CreateSource(this);
		return 0;
	}

	void AudioOutput::Play(AudioData& data)
	{
		data.mpSource->Start();
	}

	IXAudio2* AudioOutput::GetAudio()
	{
		return mpXAudio2;
	}

	void AudioOutput::UnInit()
	{
		mpMaster->DestroyVoice();
		mpXAudio2->Release();
		CoUninitialize();
		mIsInit = false;
	}

}