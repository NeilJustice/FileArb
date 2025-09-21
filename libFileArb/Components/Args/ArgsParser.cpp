#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/CreateBinaryFileArgsParser.h"
#include "libFileArb/Components/Args/CreateBinaryFilesArgsParser.h"
#include "libFileArb/Components/Args/CreateTextFileArgsParser.h"
#include "libFileArb/Components/Args/CreateTextFilesArgsParser.h"
#include "libFileArb/Components/Args/ProgramModeDeterminer.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"

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
   , _docoptParser(make_unique<Utils::DocoptParser>())
   , _programModeDeterminer(make_unique<ProgramModeDeterminer>())
{
}

ArgsParser::~ArgsParser()
{
}

FileArbArgs ArgsParser::ParseStringArgs(const vector<string>& stringArgs) const
{
   const string commandLine = Utils::Vector::Join(stringArgs, ' ');
   const string runningMessage = Utils::String::ConcatStrings("Running: ", commandLine);
   _console->ThreadIdWriteLineWithColor(runningMessage, Color::White);

   const fs::path workingDirectoryPath = _fileSystem->GetCurrentPath();
   const string workingDirectoryMessage = Utils::String::ConcatStrings("WorkingDirectory: ", workingDirectoryPath.string());
   _console->ThreadIdWriteLineWithColor(workingDirectoryMessage, Color::White);

   const map<string, docopt::Value> docoptArgs_create_binary_file =
      _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage_create_binary_file, stringArgs);

   const map<string, docopt::Value> docoptArgs_create_text_file =
      _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage_create_text_file, stringArgs);

   const map<string, docopt::Value> docoptArgs_create_binary_files =
      _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage_create_binary_files, stringArgs);

   const map<string, docopt::Value> docoptArgs_create_text_files =
      _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage_create_text_files, stringArgs);

   const ProgramMode programMode = _programModeDeterminer->DetermineProgramMode(
      docoptArgs_create_binary_file,
      docoptArgs_create_text_file,
      docoptArgs_create_binary_files,
      docoptArgs_create_text_files);

   FileArbArgs fileArbArgs;
   switch (programMode)
   {
      case ProgramMode::CreateBinaryFile:
      {
         fileArbArgs = _createBinaryFileArgsParser->ParseArgs(docoptArgs_create_binary_file, commandLine);
         break;
      }
      case ProgramMode::CreateTextFile:
      {
         fileArbArgs = _createTextFileArgsParser->ParseArgs(docoptArgs_create_text_file, commandLine);
         break;
      }
      case ProgramMode::CreateBinaryFiles:
      {
         fileArbArgs = _createBinaryFilesArgsParser->ParseArgs(docoptArgs_create_binary_files, commandLine);
         break;
      }
      case ProgramMode::CreateTextFiles:
      {
         fileArbArgs = _createTextFilesArgsParser->ParseArgs(docoptArgs_create_text_files, commandLine);
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
