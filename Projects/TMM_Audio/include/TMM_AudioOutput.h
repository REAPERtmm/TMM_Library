#pragma once 

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_AudioData.h"

// REQUIRED external include
#include <xaudio2.h>

namespace TMM
{
	
	class AudioOutput
	{
		IXAudio2* mpXAudio2;
		IXAudio2MasteringVoice* mpMaster;
		bool mIsInit;

		friend class AudioData;
	public:

		AudioOutput();
		virtual ~AudioOutput();
		
		ERROR_CODE Init();

		ERROR_CODE CreateAudio(AudioData* pOut);
		ERROR_CODE CreateAudioFromFile(const char* file, AudioData* pOut);
		ERROR_CODE CreateAudioFromContent(AudioFileContent* pContent, AudioData* pOut);

		void Play(AudioData& data);

		IXAudio2* GetAudio();

		void UnInit();

	};

}