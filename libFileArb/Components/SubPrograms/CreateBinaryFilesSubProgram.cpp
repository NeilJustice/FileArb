#include "pch.h"
#include "libFileArb/Components/Makers/BinaryFileBytesMaker.h"
#include "libFileArb/Components/Makers/FilePathsMaker.h"
#include "libFileArb/Components/SubPrograms/CreateBinaryFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

CreateBinaryFilesSubProgram::CreateBinaryFilesSubProgram()
   // Constant Components
   : _binaryFileBytesMaker(make_unique<BinaryFileBytesMaker>())
   , _filePathsMaker(make_unique<FilePathsMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateBinaryFilesSubProgram::~CreateBinaryFilesSubProgram()
{
}

int CreateBinaryFilesSubProgram::Run(const FileArbArgs& args)
{
   const shared_ptr<Utils::Stopwatch> createFilesStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   if (args.generateRandomBytes)
   {
      const vector<fs::path> allFilePaths = _filePathsMaker->MakeFilePaths(args);
      _fileCreator->CreateRandomBinaryFiles(allFilePaths, args);
   }
   else
   {
      const string nonRandomBytesString = _binaryFileBytesMaker->MakeNonRandomBytesString(args.numberOfBytesPerFile);
      _fileCreator->CreateFiles(nonRandomBytesString, args);
   }
   const unsigned long long elapsedMilliseconds = createFilesStopwatch->StopAndGetElapsedMilliseconds();
   const size_t totalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string createdFilesMessage = Utils::String::ConcatValues(
      "Wrote " , totalNumberOfFiles, " binary files to ", args.numberOfDirectoriesToCreate, " directories [" , elapsedMilliseconds, " ms]");
   _console->ThreadIdWriteLine(createdFilesMessage);
   return 0;
}
