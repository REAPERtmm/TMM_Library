#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include <TMM_AudioParser.h>

// REQUIRED external include
#include <xaudio2.h>

namespace TMM
{
	class AudioOutput;

	class AudioData {
		WAVEFORMATEX mWFX					{};
		XAUDIO2_BUFFER mBuffer				{};
		IXAudio2SourceVoice* mpSource		= nullptr;

		AudioFileContent* mpAudioContent	= nullptr;

		friend class AudioOutput;

		void LoadFromFile(const char* file);
		void LoadFromContent(AudioFileContent* pContent);

		void UpdateWFX();
		ERROR_CODE CreateSource(AudioOutput* pOutput);
	public:

		XAUDIO2_VOICE_STATE GetState();

		AudioData();
		virtual ~AudioData();
	};

}