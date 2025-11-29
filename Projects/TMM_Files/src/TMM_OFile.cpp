#include "TMM_OFile.h"

namespace TMM
{
	OFile::OFile(const char* path) : BaseFile("ab", path) {}

	bool OFile::ClearAndOpen()
	{
		mMode = "wb";
		return Open();
	}

	bool OFile::Write(const void* pSrc, uint64_t size)
	{
		return BaseFile::Write(pSrc, size);
	}

	bool OFile::WriteAt(void* pSrc, uint64_t size, uint64_t position)
	{
		return BaseFile::WriteAt(pSrc, size, position);
	}
}