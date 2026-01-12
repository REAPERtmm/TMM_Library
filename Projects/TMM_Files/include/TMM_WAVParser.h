#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_FileParser.h"

// REQUIRED external include
#include <stdio.h>

#define RIFF_ID 0x46464952
#define WAVE_ID 0x46564157
#define FMT_ID  0x20746D66
#define DATA_ID 0x61746164

namespace TMM
{

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
			unsigned short	NbrCanaux		= 0;
			unsigned int	Frequence		= 0;
			unsigned int	BytePerSec		= 0;
			unsigned short	BytePerBloc		= 0;
			unsigned short	BytePerSample	= 0;
		};

		struct HEADER_BLOC_WAV
		{
			unsigned int	DataBlocID		= 0;
			unsigned int	DataSize		= 0;
		};

		struct BLOC_WAV
		{
			HEADER_BLOC_WAV Header			= {};
			char*			pData			= nullptr;
		};

		HEADER_WAV	mHeader		{};
		BLOC_WAV	mDataBloc	{};

	public:
		virtual char* GetContent()					override;
		virtual unsigned int GetContentSize() const	override;
	};

	class Parser_WAV : public FileParser
	{
		friend class FileContent_WAV;
		FileContent_WAV* mpFileContent;

	public:
		Parser_WAV();
		virtual ~Parser_WAV();

		virtual ERROR_CODE Parse(const char* path)	override;
		virtual FileContent* GetContentRef()		override;
	};

}