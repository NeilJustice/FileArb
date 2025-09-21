#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFileSubProgram.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

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
   const shared_ptr<Utils::Stopwatch> stopwatch = _stopwatchFactory->NewAndStartStopwatch();

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
