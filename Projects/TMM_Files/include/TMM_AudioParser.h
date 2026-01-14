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
		unsigned short channelCount		= 1;
		unsigned int SampleRate			= STANDARD_SAMPLE_RATE_44100;

		WAV_TYPE_FORMAT format = WAV_TYPE_FORMAT::PCM_INTEGER;

	};

	class FileContent_WAV : public AudioFileContent
	{
		friend class FileParser_WAV;

		struct HEADER_WAV
		{
			unsigned int	FileTypeBlocID		= 0;
			unsigned int	FileSize			= 0;
			unsigned int	FileFormatID		= 0;
			unsigned int	FormatBlocID		= 0;
			unsigned int	BlocSize			= 0;
			unsigned short	AudioFormat			= 0;
			unsigned short	NbrChannels			= 0;
			unsigned int	SampleRate			= 0;
			unsigned int	BytePerSec			= 0;
			unsigned short	BytePerSampleGroup	= 0;
			unsigned short	BitsPerSample		= 0;
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
		std::vector<BLOC_WAV> mBloc		{};
		BLOC_WAV*	mpDataBloc			= nullptr;
		bool		mOwnDataBloc		= false;

		FileContent_WAV_DESCRIPTOR GetDescriptor();
		void CopySampleGroupTo(char* pDest, char* pSampleGroup);

		static FileContent_WAV* InternalCreate(FileContent_WAV_DESCRIPTOR& descriptor, void* pData, bool is_owner);

	public:
		virtual ~FileContent_WAV();

		// Accesstion
		virtual PARSING::FileFormat GetFormat()	const			override;
		virtual FileParser* GetParser()	const					override;
		virtual unsigned int GetContentSize() const				override;
		virtual char* GetContent()								override;
		virtual unsigned short GetChannelCount() const			override;
		virtual unsigned short GetSampleByteSize() const		override;
		virtual unsigned short GetSampleGroupByteSize() const	override;
		virtual unsigned int GetBytePerSeconds() const			override;
		virtual unsigned int GetSampleRate() const				override;
		virtual unsigned int GetTotalSampleCount() const		override;
		virtual Second_f GetDuration() const					override;
		virtual BASE_TYPE GetEncodedType() const				override;
		WAV_TYPE_FORMAT GetTypeFormat()	const;
		void* At(unsigned int i);

		// Creation
		static FileContent_WAV* Create(FileContent_WAV_DESCRIPTOR& descriptor, void* pData);
		static FileContent_WAV* CreateEmpty(FileContent_WAV_DESCRIPTOR& descriptor);

		// Transformation - Create
		FileContent_WAV* CutRemove(Second_f start, Second_f end);
		FileContent_WAV* CutKeep(Second_f start, Second_f end);
		FileContent_WAV* Add(Second_f t, void* pData, uint64_t size);

		// Transformation - Edit
		void Reverse(Second_f start = 0, Second_f end = -1);

		template<typename T>
		void ChangeSignal(T(*transformation)(const T*), Second_f start = 0, Second_f end = -1);

		template<typename T>
		void ChangeSignal(T(*transformation)(Second_f, const T*), Second_f start = 0, Second_f end = -1);
		template<typename T>
		void ChangeSignal(T(*transformation)(Second_f, const T*, FileContent_WAV*), Second_f start = 0, Second_f end = -1);

		template<typename T>
		void ChangeSignal(T(*transformation)(unsigned int, const T*), Second_f start = 0, Second_f end = -1);
		template<typename T>
		void ChangeSignal(T(*transformation)(unsigned int, const T*, FileContent_WAV*), Second_f start = 0, Second_f end = -1);


		template<typename T, float FACTOR>
		void Amplify();
	};

	class FileParser_WAV : public AudioFileParser
	{
		friend class FileContent_WAV;
		FileContent_WAV* mpFileContent;

	public:
		FileParser_WAV();
		virtual ~FileParser_WAV();

		virtual ERROR_CODE Parse(const char* path)									override;
		virtual ERROR_CODE Serialize(const char* path, FileContent* pFileContent)	override;
		virtual FileContent* GetContentRef()										override;
	};

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(Second_f, const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i * mHeader.SampleRate, At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(Second_f, const T*, FileContent_WAV*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i * mHeader.SampleRate, At(i), this);
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(unsigned int, const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i, At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(unsigned int, const T*, FileContent_WAV*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i, At(i), this);
		}
	}

	template<typename T, float FACTOR>
	inline void FileContent_WAV::Amplify()
	{
		ChangeSignal(+[](Second_f t, const T* pValue) -> T { return FACTOR * *pValue; });
	}

}