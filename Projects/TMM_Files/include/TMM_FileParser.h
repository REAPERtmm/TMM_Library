#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>

namespace TMM
{
	__interface FileContent;
	__interface FileParser;

	struct PARSING
	{
		enum FileFormat
		{
			TXT,
			WAV
		};

		enum STATUS : int
		{
			SUCESS					= 0b00000000,
			ERROR_OPEN				= 0b00000001,
			ERROR_READ				= 0b00000010,
			ERROR_WRITE				= 0b00000100,
			ERROR_WRONG_FORMAT		= 0b00001000,
			ERROR_UNSUPORTED_FORMAT = 0b00010000,
		};
	};

	__interface FileContent
	{
		virtual PARSING::FileFormat GetFormat() const PURE;
		virtual char* GetContent()					  PURE;
		virtual unsigned int GetContentSize() const	  PURE;
		virtual FileParser* GetParser() const		  PURE;
	};

	__interface FileParser
	{
		// Return if there was an error
		virtual ERROR_CODE Parse(const char* path)									PURE;
		virtual ERROR_CODE Serialize(const char* path, FileContent* pFileContent)	PURE;
		virtual FileContent* GetContentRef()										PURE;
	};

	__interface AudioFileContent : public FileContent
	{
		virtual unsigned short GetChannelCount() const			PURE;
		virtual unsigned short GetSampleByteSize() const		PURE;
		virtual unsigned short GetSampleGroupByteSize()	const	PURE;
		virtual unsigned int GetBytePerSeconds() const			PURE;
		virtual unsigned int GetTotalSampleCount() const		PURE;
		virtual unsigned int GetSampleRate() const				PURE;
		virtual Second_f GetDuration() const					PURE;
		virtual BASE_TYPE GetEncodedType() const				PURE;
	};

	__interface AudioFileParser : public FileParser
	{

	};

}

