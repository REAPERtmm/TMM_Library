#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_FileParser.h"

// REQUIRED external include
#include <stdio.h>
#include <memory>
#include <vector>

#define RIFF_ID 0x46464952
#define WAVE_ID 0x45564157
#define FMT_ID  0x20746D66
#define DATA_ID 0x61746164

namespace TMM
{
	enum WAV_TYPE_FORMAT : unsigned short {
		PCM_INTEGER		= 1,
		IEEE_FLOATING	= 3,
	};

	struct FileContent_WAV_DESCRIPTOR {
		static constexpr unsigned int STANDARD_SAMPLE_RATE_11025 = 11025;
		static constexpr unsigned int STANDARD_SAMPLE_RATE_22050 = 22050;
		static constexpr unsigned int STANDARD_SAMPLE_RATE_44100 = 44100;
		static constexpr unsigned int STANDARD_SAMPLE_RATE_48000 = 48000;
		static constexpr unsigned int STANDARD_SAMPLE_RATE_96000 = 96000;

		bool UseDuration = false;
		union
		{
			unsigned int sampleGroupCount = 0;
			unsigned int duration_s;
		};
		unsigned short sampleByteSize	= 16;
		unsigned short channelCount	= 1;
		unsigned int SampleRate		= STANDARD_SAMPLE_RATE_44100;

		WAV_TYPE_FORMAT format = WAV_TYPE_FORMAT::PCM_INTEGER;

	};

	class FileContent_WAV : public FileContent
	{
		friend class Parser_WAV;

		struct HEADER_WAV
		{
			unsigned int	FileTypeBlocID	= 0;
			unsigned int	FileSize		= 0;
			unsigned int	FileFormatID	= 0;
			unsigned int	FormatBlocID	= 0;
			unsigned int	BlocSize		= 0;
			unsigned short	AudioFormat		= 0;
			unsigned short	NbrChannels		= 0;
			unsigned int	SampleRate		= 0;
			unsigned int	BytePerSec		= 0;
			unsigned short	BytePerSampleGroup		= 0;
			unsigned short	BitsPerSample	= 0;
		};

		struct HEADER_BLOC_WAV
		{
			unsigned int	DataBlocID		= 0;
			unsigned int	DataSize		= 0;
		};

		struct BLOC_WAV
		{
			HEADER_BLOC_WAV Header			= {};
			unsigned int OffsetInFile		= 0;
			char*			pData			= nullptr;
		};

		HEADER_WAV	mHeader				{};
		BLOC_WAV*	mpDataBloc			{};
		std::vector<BLOC_WAV> mBloc		{};
		bool		mOwnDataBloc		= false;

		FileContent_WAV_DESCRIPTOR GetDescriptor();
		void CopySampleGroupTo(char* pDest, char* pSampleGroup);

	public:
		virtual ~FileContent_WAV();

		// Accesstion
		virtual PARSING::FileFormat GetFormat()		const override;
		virtual FileParser* GetParser()				const override;
		virtual unsigned int GetContentSize()		const override;
		virtual char* GetContent()					override;
		unsigned short GetChannelCount()			const;
		unsigned short GetSampleByteSize()			const;
		unsigned short GetSampleGroupByteSize()		const;
		unsigned int GetBytePerSeconds()			const;
		WAV_TYPE_FORMAT GetTypeFormat()				const;
		unsigned int GetTotalSampleCount()			const;
		void* At(unsigned int i);

		// Creation
		static FileContent_WAV* Create(FileContent_WAV_DESCRIPTOR& descriptor, void* pData);
		static FileContent_WAV* CreateEmpty(FileContent_WAV_DESCRIPTOR& descriptor);

		// Transformation
		FileContent_WAV* Cut(Second_f start, Second_f end);
	};

	class Parser_WAV : public FileParser
	{
		friend class FileContent_WAV;
		FileContent_WAV* mpFileContent;

	public:
		Parser_WAV();
		virtual ~Parser_WAV();

		virtual ERROR_CODE Parse(const char* path)									override;
		virtual ERROR_CODE Serialize(const char* path, FileContent* pFileContent)	override;
		virtual FileContent* GetContentRef()										override;
	};

}