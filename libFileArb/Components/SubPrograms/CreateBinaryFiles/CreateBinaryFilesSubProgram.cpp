#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/BinaryFileBytesGenerator.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFiles/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateBinaryFilesSubProgram::CreateBinaryFilesSubProgram()
   // Constant Components
   : _binaryFileBytesGenerator(make_unique<BinaryFileBytesGenerator>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFilesSubProgram::~CreateBinaryFilesSubProgram()
{
}

int CreateBinaryFilesSubProgram::Run(const FileArbArgs& args)
{
   const string fileBytes = _binaryFileBytesGenerator->MakeFileBytes(args.numberOfBytesPerFile, args.randomBytes);
   _fileCreator->WriteFiles(args, fileBytes);
   return 0;
}
