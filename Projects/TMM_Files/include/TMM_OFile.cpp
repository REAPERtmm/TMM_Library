#include "TMM_OFile.h"

TMM::OFileTS::OFileTS(const char* path) : OFile(path)
{
    InitializeCriticalSection(&mCS);
}

TMM::OFileTS::~OFileTS()
{
    DeleteCriticalSection(&mCS);
}

bool TMM::OFileTS::Open()
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::Open();
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::Close()
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::Close();
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::SeekAt(uint64_t position)
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::SeekAt(position);
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::SeekAdvance(uint64_t offset)
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::SeekAdvance(offset);
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::SeekEnd(uint64_t offset)
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::SeekEnd(offset);
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::ClearAndOpen()
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::ClearAndOpen();
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::Write(const void* pSrc, uint64_t size)
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::Write(pSrc, size);
    LeaveCriticalSection(&mCS);
    return result;
}

bool TMM::OFileTS::WriteAt(void* pSrc, uint64_t size, uint64_t position)
{
    bool result;
    EnterCriticalSection(&mCS);
    result = OFile::WriteAt(pSrc, size, position);
    LeaveCriticalSection(&mCS);
    return result;
}
