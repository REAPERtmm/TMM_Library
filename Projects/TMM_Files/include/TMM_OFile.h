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

	class OFileTS : public OFile
	{
		CRITICAL_SECTION mCS;
	public:
		OFileTS(const char* path);
		virtual ~OFileTS();

		bool Open() override final;
		bool Close() override final;

		bool SeekAt(uint64_t position) override final;
		bool SeekAdvance(uint64_t offset) override final;
		bool SeekEnd(uint64_t offset = 0) override final;

		bool ClearAndOpen() override final;
		bool Write(const void* pSrc, uint64_t size) override final;
		bool WriteAt(void* pSrc, uint64_t size, uint64_t position) override final;
	};
}
