#pragma once 
#include "TMM_BaseFile.h"

namespace TMM
{
	class OFile : public BaseFile {
	public:
		OFile(const char* path);
		virtual ~OFile() = default;

		virtual bool ClearAndOpen() override;
		virtual bool Write(const void* pSrc, uint64_t size) override;
		virtual bool WriteAt(void* pSrc, uint64_t size, uint64_t position) override;
	};

}
