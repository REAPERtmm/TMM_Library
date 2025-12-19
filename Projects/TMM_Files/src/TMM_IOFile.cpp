#include "TMM_IOFile.h"

namespace TMM
{
	IOFile::IOFile(const char* path) : BaseFile("r+b", path) {}

	bool IOFile::ClearAndOpen()
	{
		mMode = "w+b";
		return Open();
	}

	uint64_t IOFile::ReadAllAllocate(char** pDest, uint64_t position)
	{
		return BaseFile::ReadAllAllocate(pDest, position);
	}

	bool IOFile::Read(void* pDest, uint64_t size)
	{
		return BaseFile::Read(pDest, size);
	}

	bool IOFile::ReadAt(void* pDest, uint64_t size, uint64_t position)
	{
		return BaseFile::ReadAt(pDest, size, position);
	}

	bool IOFile::Write(const void* pSrc, uint64_t size)
	{
		return BaseFile::Write(pSrc, size);
	}

	bool IOFile::WriteAt(void* pSrc, uint64_t size, uint64_t position)
	{
		return BaseFile::WriteAt(pSrc, size, position);
	}


}