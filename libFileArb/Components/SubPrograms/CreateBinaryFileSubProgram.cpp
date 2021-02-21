#include "pch.h"
#include "libFileArb/Components/SubPrograms/BinaryFileBytesGenerator.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateBinaryFileSubProgram::CreateBinaryFileSubProgram()
   // Constant Components
   : _binaryFileBytesGenerator(make_unique<BinaryFileBytesGenerator>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFileSubProgram::~CreateBinaryFileSubProgram()
{
}

int CreateBinaryFileSubProgram::Run(const FileArbArgs& args)
{
   const string bytesString = _binaryFileBytesGenerator->MakeBytesString(args.numberOfBytesPerFile, args.randomBytes);
   _fileCreator->CreateBinaryFile(args, bytesString);
   return 0;
}
