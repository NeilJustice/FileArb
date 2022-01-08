#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateBinaryFileSubProgram::CreateBinaryFileSubProgram()
   // Constant Components
   : _binaryFileBytesMaker(make_unique<BinaryFileBytesMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFileSubProgram::~CreateBinaryFileSubProgram()
{
}

int CreateBinaryFileSubProgram::Run(const FileArbArgs& args)
{
   const string bytesString = _binaryFileBytesMaker->MakeNonRandomBytesString(args.numberOfBytesPerFile);
   _fileCreator->CreateFileWithBytes(args, bytesString);
   return 0;
}
