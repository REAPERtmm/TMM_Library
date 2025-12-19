#include "TMM_BaseFile.h"
namespace TMM 
{
	/* === BaseFile === */
	BaseFile::BaseFile(const char* mode, const char* path)
		: mMode(mode), mPath(path), mpFile(nullptr), mIsOpened(false)
	{

	}

	BaseFile::~BaseFile()
	{
		if(mIsOpened) Close();
	}

	bool BaseFile::InternalOpen()
	{
		auto err = fopen_s(&mpFile, mPath, mMode);
		if (err != 0) {
			return false;
		}
		mIsOpened = true;
		return true;
	}

	bool BaseFile::InternalClose()
	{
		auto err = fclose(mpFile);
		if (err != 0) {
			return false;
		}
		mIsOpened = false;
		return true;
	}

	bool BaseFile::InternalRead(void* pDest, uint64_t size)
	{
		auto err = fread(pDest, size, 1, mpFile);
		if (err != 1) {
			return false;
		}
		return true;
	}

	bool BaseFile::InternalWrite(const void* pSrc, uint64_t size)
	{
		auto err = fwrite(pSrc, size, 1, mpFile);
		if (err != 1) {
			return false;
		}
		return true;
	}

	bool BaseFile::InternalSeek(uint64_t position, int mode)
	{
		auto err = _fseeki64(mpFile, position, mode);
		if (err != 1) {
			return false;
		}
		return true;
	}

	bool BaseFile::InternalSeekAdvance(uint64_t offset)
	{
		return InternalSeek(offset, SEEK_CUR);
	}

	bool BaseFile::InternalSeekAt(uint64_t position)
	{
		return InternalSeek(position, SEEK_SET);
	}

	bool BaseFile::InternalSeekEnd(uint64_t offset)
	{
		return InternalSeek(offset, SEEK_END);
	}

	uint64_t BaseFile::InternalGetFileSize()
	{
		InternalSeekAt(0);
		uint64_t count = 0;
		while (fgetc(mpFile) != EOF) ++count;
		return count;
	}

	bool BaseFile::IsOpened() const
	{
		return mIsOpened;
	}

	bool BaseFile::SeekAt(uint64_t position)
	{
		return InternalSeekAt(position);
	}

	bool BaseFile::SeekAdvance(uint64_t offset)
	{
		return InternalSeekAdvance(offset);
	}

	bool BaseFile::SeekEnd(uint64_t offset)
	{
		return InternalSeekEnd(offset);
	}

	bool BaseFile::Open()
	{
		if (IsOpened()) return false;
		return InternalOpen();
	}

	bool BaseFile::Close()
	{
		if (IsOpened() == false) return false;
		return InternalClose();
	}

	bool BaseFile::Read(void* pDest, uint64_t size)
	{
		return InternalRead(pDest, size);
	}

	bool BaseFile::ReadAt(void* pDest, uint64_t size, uint64_t position)
	{
		InternalSeekAt(position);
		return InternalRead(pDest, size);
	}

	uint64_t BaseFile::ReadAllAllocate(char** pDest, uint64_t position)
	{
		uint64_t size = InternalGetFileSize();
		InternalSeekAt(0);
		char* pData = new char[size];
		for (uint64_t i = 0; i < size; ++i) {
			pData[i] = fgetc(mpFile);
		}
		*pDest = pData;
		return size;
	}

	bool BaseFile::Write(const void* pSrc, uint64_t size)
	{
		return InternalWrite(pSrc, size);
	}

	bool BaseFile::WriteAt(void* pSrc, uint64_t size, uint64_t position)
	{
		InternalSeekAt(position);
		return InternalWrite(pSrc, size);
	}

}