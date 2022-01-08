#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"

CreateBinaryFilesSubProgram::CreateBinaryFilesSubProgram()
   // Constant Components
   : _binaryFileBytesMaker(make_unique<BinaryFileBytesMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFilesSubProgram::~CreateBinaryFilesSubProgram()
{
}

int CreateBinaryFilesSubProgram::Run(const FileArbArgs& args)
{
   if (args.generateRandomBytes)
   {
      const string randomBytesString = _binaryFileBytesMaker->MakeRandomBytesString(args.numberOfBytesPerFile);
      _fileCreator->CreateFiles(randomBytesString, args);
   }
   else
   {
      const string nonRandomBytesString = _binaryFileBytesMaker->MakeNonRandomBytesString(args.numberOfBytesPerFile);
      _fileCreator->CreateFiles(nonRandomBytesString, args);
   }
   return 0;
}
