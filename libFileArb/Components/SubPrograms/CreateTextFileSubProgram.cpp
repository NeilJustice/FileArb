#include "pch.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"
#include "libFileArb/Components/SubPrograms/CreateTextFileSubProgram.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/Time/Stopwatch.h"
#include "libFileArb/Components/Time/StopwatchFactory.h"

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
   const shared_ptr<Utils::Stopwatch> stopwatch = p_stopwatchFactory->NewAndStartStopwatch();

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
   p_fileSystem->CreateTextFile(filePath, fileText);

   const unsigned long long elapsedMilliseconds = stopwatch->StopAndGetElapsedMilliseconds();
   const string message = Utils::String::ConcatValues("Wrote text file ", filePath.string(), " [", elapsedMilliseconds, " ms]");
   p_console->ThreadIdWriteLine(message);
   return 0;
}
