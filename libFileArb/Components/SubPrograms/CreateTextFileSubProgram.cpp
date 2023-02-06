#include "pch.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"
#include "libFileArb/UtilityComponents/Time/StopwatchFactory.h"

CreateTextFileSubProgram::CreateTextFileSubProgram()
   // Constant Components
   : _textFileTextMaker(make_unique<TextFileTextMaker>())
{
}

CreateTextFileSubProgram::~CreateTextFileSubProgram()
{
}

int CreateTextFileSubProgram::Run(const FileArbArgs& args)
{
   const shared_ptr<Utils::Stopwatch> stopwatch = _stopwatchFactory->NewAndStartStopwatch();

   string fileText;
   if (args.generateRandomLetters)
   {
      fileText = _textFileTextMaker->MakeRandomFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
   }
   else
   {
      fileText = _textFileTextMaker->MakeNonRandomFileText(args.numberOfLinesPerFile, args.numberOfCharactersPerLine);
   }
   const fs::path filePath = args.targetDirectoryPath / "textfile.txt";
   _fileSystem->CreateTextFile(filePath, fileText);

   const unsigned long long elapsedMilliseconds = stopwatch->StopAndGetElapsedMilliseconds();
   const string message = Utils::String::ConcatValues("Wrote text file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
   _console->ThreadIdWriteLine(message);
   return 0;
}
