#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_BaseFile.h"

namespace TMM
{
	class IOFile : public BaseFile {
	public:
		IOFile(const char* path);
		virtual ~IOFile() = default;

		virtual bool ClearAndOpen() override;
		virtual uint64_t ReadAllAllocate(char** pDest, uint64_t position) override;
		virtual bool Read(void* pDest, uint64_t size) override;
		virtual bool ReadAt(void* pDest, uint64_t size, uint64_t position) override;
		virtual bool Write(const void* pSrc, uint64_t size) override;
		virtual bool WriteAt(void* pSrc, uint64_t size, uint64_t position) override;
	};
}