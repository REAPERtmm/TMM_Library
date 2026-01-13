#include "TMM_WAVParser.h"

// TODO : REMOVE
#include <iostream> 

TMM::Parser_WAV::Parser_WAV() : mpFileContent(nullptr) {}

TMM::Parser_WAV::~Parser_WAV() { }

TMM::ERROR_CODE TMM::Parser_WAV::Parse(const char* path)
{
    FILE* pFile;
    if (fopen_s(&pFile, path, "rb")) return PARSING::ERROR_OPEN;

    mpFileContent = new FileContent_WAV();
    if (fread(&mpFileContent->mHeader, sizeof(TMM::FileContent_WAV::HEADER_WAV), 1, pFile) != 1) return PARSING::ERROR_READ;

    if (mpFileContent->mHeader.FileTypeBlocID != RIFF_ID) return PARSING::ERROR_WRONG_FORMAT;
    if (mpFileContent->mHeader.FileFormatID != WAVE_ID) return PARSING::ERROR_WRONG_FORMAT;
    if (mpFileContent->mHeader.FormatBlocID != FMT_ID) return PARSING::ERROR_WRONG_FORMAT;

    unsigned int offset = sizeof(TMM::FileContent_WAV::HEADER_WAV);
    bool isDataBloc = false;
    FileContent_WAV::BLOC_WAV* pBloc;
    do {
        fseek(pFile, offset, 0);

        mpFileContent->mBloc.push_back({});
        pBloc = &*mpFileContent->mBloc.rbegin();
        pBloc->OffsetInFile = offset;

        if (fread(&pBloc->Header, sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV), 1, pFile) != 1) return PARSING::ERROR_READ;

        isDataBloc = pBloc->Header.DataBlocID == DATA_ID;

        if (isDataBloc)
        {
            pBloc->pData = new char[pBloc->Header.DataSize];
            mpFileContent->mOwnDataBloc = true;
            if (fread(pBloc->pData, pBloc->Header.DataSize, 1, pFile) != 1) return PARSING::ERROR_READ;
            mpFileContent->mpDataBloc = pBloc;
        }

        offset += sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV) + pBloc->Header.DataSize;
        if (feof(pFile)) break;
    } while (!isDataBloc);

    fclose(pFile);
    return PARSING::SUCESS;
}

TMM::ERROR_CODE TMM::Parser_WAV::Serialize(const char* path, FileContent* pFileContent)
{
    mpFileContent = (FileContent_WAV*)pFileContent;
    FILE* pFile;
    if (fopen_s(&pFile, path, "wb")) return PARSING::ERROR_OPEN;

    if (fwrite(&mpFileContent->mHeader, sizeof(TMM::FileContent_WAV::HEADER_WAV), 1, pFile) != 1) return PARSING::ERROR_WRITE;
    if (fwrite(&mpFileContent->mpDataBloc->Header, sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV), 1, pFile) != 1) return PARSING::ERROR_WRITE;
    if (fwrite(&mpFileContent->mpDataBloc->pData, mpFileContent->mpDataBloc->Header.DataSize, 1, pFile) != 1) return PARSING::ERROR_WRITE;

    fclose(pFile);
    return TMM::PARSING::SUCESS;
}

TMM::FileContent* TMM::Parser_WAV::GetContentRef()
{
    return mpFileContent;
}

TMM::FileContent_WAV_DESCRIPTOR TMM::FileContent_WAV::GetDescriptor()
{
    return {
        .UseDuration        = false,
        .sampleGroupCount   = mpDataBloc->Header.DataSize / mHeader.BytePerSampleGroup,
        .sampleByteSize     = mHeader.BitsPerSample,
        .channelCount       = mHeader.NbrChannels,
        .SampleRate         = FileContent_WAV_DESCRIPTOR::STANDARD_SAMPLE_RATE_44100,
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
    return new Parser_WAV();
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

TMM::WAV_TYPE_FORMAT TMM::FileContent_WAV::GetTypeFormat() const
{
    return (mHeader.AudioFormat == 3 ? WAV_TYPE_FORMAT::IEEE_FLOATING : WAV_TYPE_FORMAT::PCM_INTEGER);
}

unsigned int TMM::FileContent_WAV::GetTotalSampleCount() const
{
    return mpDataBloc->Header.DataSize / GetSampleGroupByteSize();
}

void* TMM::FileContent_WAV::At(unsigned int i)
{
    return mpDataBloc->pData + (i * GetSampleGroupByteSize());
}

TMM::FileContent_WAV* TMM::FileContent_WAV::Create(FileContent_WAV_DESCRIPTOR& descriptor, void* pData)
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

    return pFileContent;
}

TMM::FileContent_WAV* TMM::FileContent_WAV::CreateEmpty(FileContent_WAV_DESCRIPTOR& descriptor)
{
    if (descriptor.UseDuration)
    {
        descriptor.sampleGroupCount = descriptor.duration_s / descriptor.SampleRate;
        descriptor.UseDuration = false;
    }
    
    unsigned int size = descriptor.sampleGroupCount * descriptor.sampleByteSize * descriptor.channelCount;
    return Create(descriptor, new char[size]);
}

TMM::FileContent_WAV* TMM::FileContent_WAV::Cut(Second_f start, Second_f end)
{
    FileContent_WAV_DESCRIPTOR desc = GetDescriptor();

    unsigned int SizeToStart = start * mHeader.SampleRate * mHeader.BytePerSampleGroup;
    unsigned int SizeToEnd = end * mHeader.SampleRate * mHeader.BytePerSampleGroup;
    unsigned int SampleGroupCountCutted = SizeToEnd - SizeToStart;
    desc.sampleGroupCount -= SampleGroupCountCutted;

    // TODO :
    // Cut to 0 s ???
    TMM::FileContent_WAV* pOut = TMM::FileContent_WAV::CreateEmpty(desc);

    memcpy(
        pOut->mpDataBloc->pData, 
        mpDataBloc->pData, 
        SizeToStart
    );
    memcpy(
        pOut->mpDataBloc->pData + SizeToStart,
        mpDataBloc->pData + SizeToStart, 
        mpDataBloc->Header.DataSize - SizeToEnd
    );


    return pOut;
}


