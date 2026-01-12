#include "TMM_WAVParser.h"


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

    bool isDataBloc = false;
    do {
        if (fread(&mpFileContent->mDataBloc.Header, sizeof(TMM::FileContent_WAV::HEADER_BLOC_WAV), 1, pFile) != 1) return PARSING::ERROR_READ;
        isDataBloc = mpFileContent->mDataBloc.Header.DataBlocID == DATA_ID;

        if (isDataBloc)
        {
            mpFileContent->mDataBloc.pData = new char[mpFileContent->mDataBloc.Header.DataSize];
            if (fread(mpFileContent->mDataBloc.pData, mpFileContent->mDataBloc.Header.DataSize, 1, pFile) != 1) return PARSING::ERROR_READ;
        }

        if (feof(pFile)) break;
    } while (!isDataBloc);

    fclose(pFile);
    return PARSING::SUCESS;
}

TMM::FileContent* TMM::Parser_WAV::GetContentRef()
{
    return mpFileContent;
}

char* TMM::FileContent_WAV::GetContent()
{
    return mDataBloc.pData;
}

unsigned int TMM::FileContent_WAV::GetContentSize() const
{
    return mDataBloc.Header.DataSize;
}
