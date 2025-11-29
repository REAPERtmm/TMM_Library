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

	class IFileTS : public IFile {
		CRITICAL_SECTION mCS;
	public:
		IFileTS(const char* path);
		virtual ~IFileTS();

		bool Open() override final;
		bool Close() override final;

		bool SeekAt(uint64_t position) override final;
		bool SeekAdvance(uint64_t offset) override final;
		bool SeekEnd(uint64_t offset = 0) override final;

		uint64_t ReadAllAllocate(char** pDest, uint64_t position) override final;
		bool Read(void* pDest, uint64_t size) override final;
		bool ReadAt(void* pDest, uint64_t size, uint64_t position) override final;
	};
}