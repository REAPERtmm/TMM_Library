#include "TMM_AudioParser.h"

namespace TMM
{
    TMM::FileParser_WAV::FileParser_WAV() : mpFileContent(nullptr) {}

    TMM::FileParser_WAV::~FileParser_WAV() { }

    TMM::ERROR_CODE TMM::FileParser_WAV::Parse(const char* path)
    {
        TMM::IFile file(path);

        if(file.Open() == false) return PARSING::ERROR_OPEN;

        mpFileContent = new FileContent_WAV();
        if (file.Read(&mpFileContent->mHeader, sizeof(TMM::FileContent_WAV::HEADER_WAV)) == false)  return PARSING::ERROR_READ;

        if (mpFileContent->mHeader.FileTypeBlocID != RIFF_ID) return PARSING::ERROR_WRONG_FORMAT;
        if (mpFileContent->mHeader.FileFormatID != WAVE_ID) return PARSING::ERROR_WRONG_FORMAT;
        if (mpFileContent->mHeader.FormatBlocID != FMT_ID) return PARSING::ERROR_WRONG_FORMAT;

        unsigned int offset = sizeof(TMM::FileContent_WAV::HEADER_WAV);
        bool isDataBloc = false;
        FileContent_WAV::BLOC_WAV* pBloc;
        do {

            mpFileContent->mBloc.push_back({});
            pBloc = &*mpFileContent->mBloc.rbegin();
            pBloc->OffsetInFile = offset;

            if (file.ReadAt(&pBloc->Header, sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV), offset) == false) return PARSING::ERROR_READ;
            offset += sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV);

            isDataBloc = pBloc->Header.DataBlocID == DATA_ID;

            if (isDataBloc)
            {
                pBloc->pData = new char[pBloc->Header.DataSize];
                mpFileContent->mOwnDataBloc = true;
                if (file.ReadAt(pBloc->pData, pBloc->Header.DataSize, offset) == false) return PARSING::ERROR_READ;
                mpFileContent->mpDataBloc = pBloc;
            }

            offset += pBloc->Header.DataSize;
            if (file.EndOfFile()) break;
        } while (!isDataBloc);

        file.Close();
        return PARSING::SUCESS;
    }

    TMM::ERROR_CODE TMM::FileParser_WAV::Serialize(const char* path, FileContent* pFileContent)
    {
        mpFileContent = (FileContent_WAV*)pFileContent;
     
        TMM::OFile file(path);
        if (file.ClearAndOpen() == false) return PARSING::ERROR_OPEN;

        if (file.Write(&mpFileContent->mHeader, sizeof(TMM::FileContent_WAV::HEADER_WAV)) == false) return PARSING::ERROR_WRITE;
        if (file.Write(&mpFileContent->mpDataBloc->Header, sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV)) == false) return PARSING::ERROR_WRITE;
        if (file.Write(mpFileContent->mpDataBloc->pData, mpFileContent->mpDataBloc->Header.DataSize) == false) return PARSING::ERROR_WRITE;

        file.Close();
        return TMM::PARSING::SUCESS;
    }

    TMM::FileContent* TMM::FileParser_WAV::GetContentRef()
    {
        return mpFileContent;
    }

    TMM::FileContent_WAV_DESCRIPTOR TMM::FileContent_WAV::GetDescriptor()
    {
        unsigned short BytePerSample = mHeader.BitsPerSample / 8;
        return {
            .UseDuration        = false,
            .sampleGroupCount   = mpDataBloc->Header.DataSize / mHeader.BytePerSampleGroup,
            .sampleByteSize     = BytePerSample,
            .channelCount       = mHeader.NbrChannels,
            .SampleRate         = mHeader.SampleRate,
            .format             = (WAV_TYPE_FORMAT)mHeader.AudioFormat,
        };
    }

    void TMM::FileContent_WAV::CopySampleGroupTo(char* pDest, char* pSampleGroup)
    {
        for (int i = 0; i < mHeader.BytePerSampleGroup; ++i)
        {
            pDest[i] = pSampleGroup[i];
        }
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::InternalCreate(FileContent_WAV_DESCRIPTOR& descriptor, void* pData, bool is_owner)
    {
        TMM::FileContent_WAV* pFileContent = new TMM::FileContent_WAV();

        if (descriptor.UseDuration)
        {
            descriptor.sampleGroupCount = descriptor.duration_s / descriptor.SampleRate;
        }

        pFileContent->mBloc.push_back({});
        pFileContent->mpDataBloc = &*pFileContent->mBloc.rbegin();

        pFileContent->mHeader.FileTypeBlocID = RIFF_ID;
        pFileContent->mHeader.FileSize = (
            sizeof(FileContent_WAV::HEADER_WAV)
            + sizeof(FileContent_WAV::HEADER_BLOC_WAV)
            + descriptor.sampleGroupCount * descriptor.sampleByteSize * descriptor.channelCount
            - 8
            ) * 8;
        pFileContent->mHeader.FileFormatID = WAVE_ID;

        pFileContent->mHeader.FormatBlocID = FMT_ID;
        pFileContent->mHeader.BlocSize = 16;
        pFileContent->mHeader.AudioFormat = descriptor.format;
        pFileContent->mHeader.NbrChannels = descriptor.channelCount;
        pFileContent->mHeader.SampleRate = descriptor.SampleRate;
        pFileContent->mHeader.BytePerSec = descriptor.SampleRate * descriptor.sampleByteSize * descriptor.channelCount;
        pFileContent->mHeader.BytePerSampleGroup = descriptor.sampleByteSize * descriptor.channelCount;
        pFileContent->mHeader.BitsPerSample = descriptor.sampleByteSize * 8;

        pFileContent->mpDataBloc->Header.DataBlocID = DATA_ID;
        pFileContent->mpDataBloc->OffsetInFile = sizeof(FileContent_WAV::HEADER_WAV) + sizeof(FileContent_WAV::HEADER_BLOC_WAV);
        pFileContent->mpDataBloc->Header.DataSize = descriptor.sampleGroupCount * descriptor.sampleByteSize * descriptor.channelCount;

        pFileContent->mpDataBloc->pData = (char*)pData;
        pFileContent->mOwnDataBloc = is_owner;

        return pFileContent;
    }

    TMM::FileContent_WAV::~FileContent_WAV()
    {
        if(mOwnDataBloc) delete[] mpDataBloc->pData;
    }

    char* TMM::FileContent_WAV::GetContent()
    {
        return mpDataBloc->pData;
    }

    TMM::PARSING::FileFormat TMM::FileContent_WAV::GetFormat() const
    {
        return PARSING::FileFormat::WAV;
    }

    TMM::FileParser* TMM::FileContent_WAV::GetParser() const
    {
        return new FileParser_WAV();
    }

    unsigned int TMM::FileContent_WAV::GetContentSize() const
    {
        return mpDataBloc->Header.DataSize;
    }

    unsigned short TMM::FileContent_WAV::GetChannelCount() const
    {
        return mHeader.NbrChannels;
    }

    unsigned short TMM::FileContent_WAV::GetSampleByteSize() const
    {
        return mHeader.BitsPerSample / 8;
    }

    unsigned short TMM::FileContent_WAV::GetSampleGroupByteSize() const
    {
        return mHeader.BytePerSampleGroup;
    }

    unsigned int TMM::FileContent_WAV::GetBytePerSeconds() const
    {
        return mHeader.BytePerSec;
    }

    unsigned int FileContent_WAV::GetSampleRate() const
    {
        return mHeader.SampleRate;
    }

    TMM::WAV_TYPE_FORMAT TMM::FileContent_WAV::GetTypeFormat() const
    {
        return (mHeader.AudioFormat == 3 ? WAV_TYPE_FORMAT::IEEE_FLOATING : WAV_TYPE_FORMAT::PCM_INTEGER);
    }

    unsigned int TMM::FileContent_WAV::GetTotalSampleCount() const
    {
        return mpDataBloc->Header.DataSize / GetSampleGroupByteSize();
    }

    TMM::Second_f TMM::FileContent_WAV::GetDuration() const
    {
        return GetTotalSampleCount() / mHeader.SampleRate;
    }

    BASE_TYPE FileContent_WAV::GetEncodedType() const
    {

        if (mHeader.AudioFormat == 1) {
            switch (mHeader.BitsPerSample)
            {
            case 8 : return BASE_TYPE::INT8;
            case 16: return BASE_TYPE::INT16;
            case 24: return BASE_TYPE::INT32;
            case 32: return BASE_TYPE::INT32;
            case 64: return BASE_TYPE::INT64;
            default: return BASE_TYPE::UNKNOWN;
            }
        }
        else if (mHeader.BitsPerSample == 32) return BASE_TYPE::FLOAT;
        else if (mHeader.BitsPerSample == 64) return BASE_TYPE::DOUBLE;


        return BASE_TYPE::UNKNOWN;
    }

    void* TMM::FileContent_WAV::At(unsigned int i)
    {
        return mpDataBloc->pData + (i * GetSampleGroupByteSize());
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::Create(FileContent_WAV_DESCRIPTOR& descriptor, void* pData)
    {
        return InternalCreate(descriptor, pData, false);
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::CreateEmpty(FileContent_WAV_DESCRIPTOR& descriptor)
    {
        if (descriptor.UseDuration)
        {
            descriptor.sampleGroupCount = descriptor.duration_s / descriptor.SampleRate;
            descriptor.UseDuration = false;
        }
    
        unsigned int size = descriptor.sampleGroupCount * descriptor.sampleByteSize * descriptor.channelCount;
        return InternalCreate(descriptor, new char[size], true);
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::CutRemove(Second_f start, Second_f end)
    {
        FileContent_WAV_DESCRIPTOR desc = GetDescriptor();

        unsigned int SizeToStart = start * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToStart -= SizeToStart % GetSampleGroupByteSize();

        unsigned int SizeToEnd = end * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToEnd -= SizeToEnd % GetSampleGroupByteSize();

        unsigned int SampleGroupCountCuttedSize = (SizeToEnd - SizeToStart);
        unsigned int SampleGroupCountCutted = SampleGroupCountCuttedSize / mHeader.BytePerSampleGroup;
        desc.sampleGroupCount -= SampleGroupCountCutted;

        TMM::FileContent_WAV* pOut = TMM::FileContent_WAV::CreateEmpty(desc);

        memcpy(
            pOut->mpDataBloc->pData, 
            mpDataBloc->pData, 
            SizeToStart
        );
        memcpy(
            pOut->mpDataBloc->pData + SizeToStart,
            mpDataBloc->pData + SizeToStart + SampleGroupCountCuttedSize, 
            mpDataBloc->Header.DataSize - SizeToEnd
        );

        return pOut;
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::CutKeep(Second_f start, Second_f end)
    {
        FileContent_WAV_DESCRIPTOR desc = GetDescriptor();

        unsigned int SizeToStart = start * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToStart -= SizeToStart % GetSampleGroupByteSize();
        unsigned int SizeToEnd = end * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToEnd -= SizeToEnd % GetSampleGroupByteSize();
        unsigned int SampleGroupCountCuttedSize = SizeToEnd - SizeToStart;
        unsigned int SampleGroupCountCutted = SampleGroupCountCuttedSize / mHeader.BytePerSampleGroup;
        desc.sampleGroupCount = SampleGroupCountCutted;

        TMM::FileContent_WAV* pOut = TMM::FileContent_WAV::CreateEmpty(desc);

        memcpy(
            pOut->mpDataBloc->pData,
            mpDataBloc->pData + SizeToStart,
            SampleGroupCountCuttedSize
        );

        return pOut;
    }

    TMM::FileContent_WAV* TMM::FileContent_WAV::Add(Second_f t, void* pData, uint64_t size)
    {
        FileContent_WAV_DESCRIPTOR desc = GetDescriptor();

        unsigned int SizeToTime = t * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToTime -= SizeToTime % GetSampleGroupByteSize();
        unsigned int SampleGroupCountCutted = SizeToTime / mHeader.BytePerSampleGroup;
        desc.sampleGroupCount += SampleGroupCountCutted;

        TMM::FileContent_WAV* pOut = TMM::FileContent_WAV::CreateEmpty(desc);

        memcpy(
            pOut->mpDataBloc->pData,
            mpDataBloc->pData,
            SizeToTime
        );
        memcpy(
            pOut->mpDataBloc->pData + SizeToTime,
            pData,
            size
        );
        memcpy(
            pOut->mpDataBloc->pData + SizeToTime + size,
            mpDataBloc->pData + SizeToTime,
            mpDataBloc->Header.DataSize - SizeToTime
        );

        return pOut;
    }

    void FileContent_WAV::Reverse(Second_f start, Second_f end)
    {
        end = (end > start ? end : GetDuration());

        unsigned int SizeToStart = start * mHeader.SampleRate * mHeader.BytePerSampleGroup;
        SizeToStart -= SizeToStart % GetSampleGroupByteSize();
        unsigned int SizeToEnd = end * mHeader.SampleRate * GetSampleGroupByteSize();
        SizeToEnd -= SizeToEnd % GetSampleGroupByteSize();

        unsigned int SampleGroupCountCutted = (SizeToEnd - SizeToStart) / GetSampleGroupByteSize();

        char* buffer_temp = new char[GetSampleGroupByteSize()];

        for (unsigned int i = 0; i < SampleGroupCountCutted * 0.5f; ++i)
        {
            unsigned int offset = i * GetSampleGroupByteSize();
            char* pLeft     = GetContent() + SizeToStart + offset;
            char* pRight    = GetContent() + SizeToEnd - offset - GetSampleGroupByteSize();

            CopySampleGroupTo(buffer_temp, pLeft);
            CopySampleGroupTo(pLeft, pRight);
            CopySampleGroupTo(pRight, buffer_temp);
        }

        delete[] buffer_temp;
    }

}


