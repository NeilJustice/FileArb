#include "pch.h"
#include "libFileArb/Components/Makers/FilePathsMaker.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFilesSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

CreateTextFilesSubProgram::CreateTextFilesSubProgram()
   // Constant Components
   : _textFileTextMaker(make_unique<TextFileTextMaker>())
   , _filePathsMaker(make_unique<FilePathsMaker>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
{
}

CreateTextFilesSubProgram::~CreateTextFilesSubProgram()
{
}

int CreateTextFilesSubProgram::Run(const FileArbArgs& args)
{
   const shared_ptr<Utils::Stopwatch> createFilesStopwatch = _stopwatchFactory->NewAndStartStopwatch();
   if (args.generateRandomLetters)
   {
       const vector<fs::path> allFilePaths = _filePathsMaker->MakeFilePaths(args);
      _fileCreator->CreateRandomTextFiles(allFilePaths, args);
   }
   else
   {
      const string fileText = _textFileTextMaker->MakeNonRandomFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
      _fileCreator->CreateFiles(fileText, args);
   }
   const unsigned long long elapsedMilliseconds = createFilesStopwatch->StopAndGetElapsedMilliseconds();
   const size_t totalNumberOfFiles = args.numberOfFilesToCreate * args.numberOfDirectoriesToCreate;
   const string createdFilesMessage = Utils::String::ConcatValues(
      "Wrote " , totalNumberOfFiles, " text files to ", args.numberOfDirectoriesToCreate, " directories [" , elapsedMilliseconds, " ms]");
   _console->ThreadIdWriteLine(createdFilesMessage);
   return 0;
}
