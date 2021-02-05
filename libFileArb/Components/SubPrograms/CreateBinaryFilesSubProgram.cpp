#include "pch.h"
#include "libFileArb/Components/SubPrograms/BinaryFileBytesGenerator.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
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
   const string bytesString = _binaryFileBytesGenerator->MakeBytesString(args.numberOfBytesPerFile, args.randomBytes);
   _fileCreator->CreateFiles(args, bytesString);
   return 0;
}
