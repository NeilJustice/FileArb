#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"
#include "libFileArb/Components/Args/PreamblePrinter.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/Vector/VectorHelper.h"

ArgsParser::ArgsParser()
   // Function Callers
   : _call_exit(exit)
   // Constant Components
   , _bytesStringConverter(make_unique<BytesStringConverter>())
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _createBinaryFileArgsParser(make_unique<CreateBinaryFileArgsParser>())
   , _createTextFileArgsParser(make_unique<CreateTextFileArgsParser>())
   , _createBinaryFilesArgsParser(make_unique<CreateBinaryFilesArgsParser>())
   , _createTextFilesArgsParser(make_unique<CreateTextFilesArgsParser>())
   , _docoptParser(make_unique<DocoptParser>())
   , _preamblePrinter(make_unique<Utils::PreamblePrinter>())
   , _programModeDeterminer(make_unique<ProgramModeDeterminer>())
   , _vectorHelper(make_unique<Utils::VectorHelper>())
{
}

ArgsParser::~ArgsParser()
{
}

FileArbArgs ArgsParser::ParseStringArgs(const vector<string>& stringArgs) const
{
   const string commandLine = _vectorHelper->Join(stringArgs, ' ');
   _preamblePrinter->PrintPreamble(commandLine, _console.get());

   const map<string, docopt::value> docoptArgs = _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage, stringArgs, false);
   const ProgramMode programMode = _programModeDeterminer->DetermineProgramMode(docoptArgs);

   FileArbArgs fileArbArgs;
   switch (programMode)
   {
      case ProgramMode::CreateBinaryFile:
      {
         fileArbArgs = _createBinaryFileArgsParser->ParseArgs(docoptArgs);
         break;
      }
      case ProgramMode::CreateTextFile:
      {
         fileArbArgs = _createTextFileArgsParser->ParseArgs(docoptArgs);
         break;
      }
      case ProgramMode::CreateBinaryFiles:
      {
         fileArbArgs = _createBinaryFilesArgsParser->ParseArgs(docoptArgs);
         break;
      }
      case ProgramMode::CreateTextFiles:
      {
         fileArbArgs = _createTextFilesArgsParser->ParseArgs(docoptArgs);
         break;
      }
      default:
      {
         _console->ThreadIdWriteLineWithColor("Error: Invalid command line arguments", Color::Red);
         _console->NakedWriteLine(FileArbArgs::CommandLineUsage);
         _call_exit(1);
      }
   }
   return fileArbArgs;
}
