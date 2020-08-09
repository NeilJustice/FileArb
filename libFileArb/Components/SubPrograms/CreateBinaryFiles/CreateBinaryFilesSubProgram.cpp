#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

CreateBinaryFilesSubProgram::CreateBinaryFilesSubProgram()
   : _binaryFileBytesGenerator(make_unique<BinaryFileBytesGenerator>())
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFilesSubProgram::~CreateBinaryFilesSubProgram()
{
}

int CreateBinaryFilesSubProgram::Run(const FileArbArgs& args)
{
   const string fileBytes = _binaryFileBytesGenerator->MakeFileBytes(args.numberOfBytesPerFile);
   _fileCreator->WriteFiles(args, fileBytes);
   return 0;
}
