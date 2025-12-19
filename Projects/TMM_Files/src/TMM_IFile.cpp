#include "TMM_IFile.h"

namespace TMM 
{
	IFile::IFile(const char* path) : BaseFile("rb", path) {}

	uint64_t IFile::ReadAllAllocate(char** pDest, uint64_t position)
	{
		return BaseFile::ReadAllAllocate(pDest, position);
	}

	bool IFile::Read(void* pDest, uint64_t size)
	{
		return BaseFile::Read(pDest, size);
	}

	bool IFile::ReadAt(void* pDest, uint64_t size, uint64_t position)
	{
		return BaseFile::ReadAt(pDest, size, position);
	}


}

