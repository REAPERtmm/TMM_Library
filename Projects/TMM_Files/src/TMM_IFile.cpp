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

	IFileTS::IFileTS(const char* path) : IFile(path)
	{
		InitializeCriticalSection(&mCS);
	}

	IFileTS::~IFileTS()
	{
		DeleteCriticalSection(&mCS);
	}

	bool IFileTS::Open()
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::Open();
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::Close()
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::Close();
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::SeekAt(uint64_t position)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::SeekAt(position);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::SeekAdvance(uint64_t offset)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::SeekAdvance(offset);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::SeekEnd(uint64_t offset)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::SeekEnd(offset);
		LeaveCriticalSection(&mCS);
		return result;
	}

	uint64_t IFileTS::ReadAllAllocate(char** pDest, uint64_t position)
	{
		uint64_t result;
		EnterCriticalSection(&mCS);
		result = IFile::ReadAllAllocate(pDest, position);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::Read(void* pDest, uint64_t size)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::Read(pDest, size);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IFileTS::ReadAt(void* pDest, uint64_t size, uint64_t position)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IFile::ReadAt(pDest, size, position);
		LeaveCriticalSection(&mCS);
		return result;
	}

}

