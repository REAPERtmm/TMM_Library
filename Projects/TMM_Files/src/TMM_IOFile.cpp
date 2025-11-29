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

	IOFileTS::IOFileTS(const char* path) : IOFile(path)
	{
		InitializeCriticalSection(&mCS);
	}

	IOFileTS::~IOFileTS()
	{
		DeleteCriticalSection(&mCS);
	}

	bool IOFileTS::Open()
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::Open();
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::Close()
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::Close();
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::SeekAt(uint64_t position)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::SeekAt(position);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::SeekAdvance(uint64_t offset)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::SeekAdvance(offset);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::SeekEnd(uint64_t offset)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::SeekEnd(offset);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::ClearAndOpen()
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::ClearAndOpen();
		LeaveCriticalSection(&mCS);
		return result;
	}

	uint64_t IOFileTS::ReadAllAllocate(char** pDest, uint64_t position)
	{
		uint64_t result;
		EnterCriticalSection(&mCS);
		result = IOFile::ReadAllAllocate(pDest, position);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::Read(void* pDest, uint64_t size)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::Read(pDest, size);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::ReadAt(void* pDest, uint64_t size, uint64_t position)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::ReadAt(pDest, size, position);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::Write(const void* pSrc, uint64_t size)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::Write(pSrc, size);
		LeaveCriticalSection(&mCS);
		return result;
	}

	bool IOFileTS::WriteAt(void* pSrc, uint64_t size, uint64_t position)
	{
		bool result;
		EnterCriticalSection(&mCS);
		result = IOFile::WriteAt(pSrc, size, position);
		LeaveCriticalSection(&mCS);
		return result;
	}

}