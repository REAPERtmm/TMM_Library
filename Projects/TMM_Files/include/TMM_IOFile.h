#pragma once
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

	class IOFileTS : public IOFile {
		CRITICAL_SECTION mCS;
	public:
		IOFileTS(const char* path);
		virtual ~IOFileTS();

		bool Open() override final;
		bool Close() override final;

		bool SeekAt(uint64_t position) override final;
		bool SeekAdvance(uint64_t offset) override final;
		bool SeekEnd(uint64_t offset = 0) override final;

		bool ClearAndOpen() override final;
		uint64_t ReadAllAllocate(char** pDest, uint64_t position) override final;
		bool Read(void* pDest, uint64_t size) override final;
		bool ReadAt(void* pDest, uint64_t size, uint64_t position) override final;
		bool Write(const void* pSrc, uint64_t size) override final;
		bool WriteAt(void* pSrc, uint64_t size, uint64_t position) override final;
	};
}