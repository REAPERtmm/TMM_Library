#include "TMM_AudioData.h"
#include "TMM_AudioOutput.h"

namespace TMM {
	XAUDIO2_VOICE_STATE AudioData::GetState()
	{
		XAUDIO2_VOICE_STATE state;
		mpSource->GetState(&state);
		return state;
	}
	TMM::AudioData::AudioData() :
		mpAudioContent(nullptr)
	{
		
	}

	TMM::AudioData::~AudioData()
	{

	}

	void AudioData::LoadFromFile(const char* file)
	{
		TMM::FileParser_WAV pParser;
		pParser.Parse(file);
		mpAudioContent = (TMM::AudioFileContent*)pParser.GetContentRef();

		UpdateWFX();
	}

	void AudioData::LoadFromContent(AudioFileContent* pContent)
	{
		mpAudioContent = pContent;
		UpdateWFX();
	}

	void AudioData::UpdateWFX()
	{
		mWFX.wFormatTag = mpAudioContent->GetFormat();
		mWFX.nChannels = mpAudioContent->GetChannelCount();
		mWFX.nSamplesPerSec = mpAudioContent->GetSampleRate();
		mWFX.wBitsPerSample = mpAudioContent->GetSampleByteSize() * 8;
		mWFX.nBlockAlign = mWFX.nChannels * (mWFX.wBitsPerSample / 8);
		mWFX.nAvgBytesPerSec = mWFX.nSamplesPerSec * mWFX.nBlockAlign;
	}

	ERROR_CODE AudioData::CreateSource(AudioOutput* pOutput)
	{
		HRESULT hr = pOutput->GetAudio()->CreateSourceVoice(&mpSource, &mWFX);
		if (FAILED(hr)) return hr;

		mBuffer.pAudioData = (BYTE*)mpAudioContent->GetContent();
		mBuffer.AudioBytes = mpAudioContent->GetContentSize();
		mBuffer.Flags = XAUDIO2_END_OF_STREAM;

		mpSource->SubmitSourceBuffer(&mBuffer);
	}

}

