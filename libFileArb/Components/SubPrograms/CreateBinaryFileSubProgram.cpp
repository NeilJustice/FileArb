#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

CreateBinaryFileSubProgram::CreateBinaryFileSubProgram()
   // Constant Components
   : _binaryFileBytesMaker(make_unique<BinaryFileBytesMaker>())
{
}

CreateBinaryFileSubProgram::~CreateBinaryFileSubProgram()
{
}

int CreateBinaryFileSubProgram::Run(const FileArbArgs& args)
{
   const shared_ptr<Time::Stopwatch> stopwatch = _stopwatchFactory->NewAndStartStopwatch();

   string fileBytesString;
   if (args.generateRandomBytes)
   {
      fileBytesString = _binaryFileBytesMaker->MakeRandomBytesString(args.numberOfBytesPerFile);
   }
   else
   {
      fileBytesString = _binaryFileBytesMaker->MakeNonRandomBytesString(args.numberOfBytesPerFile);
   }
   const fs::path filePath = args.targetDirectoryPath / "binaryfile.bin";
   _fileSystem->CreateFileWithBytes(filePath, fileBytesString);

   const unsigned long long elapsedMilliseconds = stopwatch->StopAndGetElapsedMilliseconds();
   const string message = Utils::String::ConcatValues("Wrote binary file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
   _console->ThreadIdWriteLine(message);
   return 0;
}
