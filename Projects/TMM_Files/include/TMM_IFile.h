#pragma once
#include "TMM_BaseFile.h"

namespace TMM {

	class IFile : public BaseFile {
	public:
		IFile(const char* path);
		virtual ~IFile() = default;

		virtual uint64_t ReadAllAllocate(char** pDest, uint64_t position) override;
		virtual bool Read(void* pDest, uint64_t size) override;
		virtual bool ReadAt(void* pDest, uint64_t size, uint64_t position) override;
	};

}