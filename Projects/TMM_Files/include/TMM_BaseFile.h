#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>

// REQUIRED external include
#include <cstdio>

namespace TMM 
{
	class BaseFile {
	protected:
		const char* mMode;
		const char* mPath;
		FILE* mpFile;
		bool mIsOpened;

		BaseFile(const char* mode, const char* path);
		virtual ~BaseFile();
		bool InternalOpen();
		bool InternalClose();
		bool InternalRead(void* pDest, uint64_t size);
		bool InternalWrite(const void* pSrc, uint64_t size);
		bool InternalSeek(uint64_t position, int mode);
		bool InternalSeekAdvance(uint64_t offset);
		bool InternalSeekAt(uint64_t position);
		bool InternalSeekEnd(uint64_t offset = 0);

		/// <summary>
		/// Put you at the EOF
		/// </summary>
		uint64_t InternalGetFileSize();

		/* === IFile Functions */
		virtual bool Read(void* pDest, uint64_t size);
		virtual bool ReadAt(void* pDest, uint64_t size, uint64_t position);
		/// <summary>
		/// Allocate a char[] of the size of the file and fill it with all data in file, then return it's size in bytes. DEPRECATED ON LARGE FILES !
		/// </summary>
		virtual uint64_t ReadAllAllocate(char** pDest, uint64_t position);

		/* === OFile Functions */
		virtual bool Write(const void* pSrc, uint64_t size);
		virtual bool WriteAt(void* pSrc, uint64_t size, uint64_t position);
		virtual bool ClearAndOpen() = 0;
	public:
		/// <summary>
		/// Not Thread Safe
		/// </summary>
		bool IsOpened() const;
		
		virtual bool SeekAt(uint64_t position);
		virtual bool SeekAdvance(uint64_t offset);
		virtual bool SeekEnd(uint64_t offset = 0);

		virtual bool EndOfFile();

		virtual bool Open();
		virtual bool Close();
	};
}

#include "TMM_BaseFile.hpp"