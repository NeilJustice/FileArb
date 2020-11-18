#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"

FileArbArgsParser::FileArbArgsParser()
   // Function Callers
   : _call_DetermineProgramMode(FileArbArgsParser::DetermineProgramMode)
   , _call_DetermineFileExtension(FileArbArgsParser::DetermineFileExtension)
   // Constant Components
   , _console(make_unique<Console>())
   , _docoptParser(make_unique<DocoptParser>())
{
}

FileArbArgsParser::~FileArbArgsParser()
{
}

FileArbArgs FileArbArgsParser::ParseArgs(const vector<string>& stringArgs) const
{
   FileArbArgs args;
   args.commandLine = Vector::Join(stringArgs, ' ');
   const map<string, docopt::Value> docoptValues =
      _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage, stringArgs);
   const bool isCreateTextFilesMode = _docoptParser->GetRequiredBool(docoptValues, "create-text-files");
   const bool isCreateBinaryFilesMode = _docoptParser->GetRequiredBool(docoptValues, "create-binary-files");
   args.programMode = _call_DetermineProgramMode(isCreateTextFilesMode, isCreateBinaryFilesMode);
   args.fileExtension = _call_DetermineFileExtension(isCreateTextFilesMode, isCreateBinaryFilesMode);
   args.targetDirectoryPath = _docoptParser->GetRequiredString(docoptValues, "--target");

   const int programModeAsInt = static_cast<int>(args.programMode);
   const vector<int> createTextFilesAndCreateBinaryFiles =
   {
      static_cast<int>(ProgramMode::CreateTextFiles),
      static_cast<int>(ProgramMode::CreateBinaryFiles)
   };

   args.numberOfDirectoriesToCreate = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--directories", programModeAsInt, createTextFilesAndCreateBinaryFiles);

   args.numberOfFilesToCreate = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--files", programModeAsInt, createTextFilesAndCreateBinaryFiles);

   args.numberOfLinesPerFile = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--lines", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles) });

   args.numberOfCharactersPerLine = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--characters", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles) });

   args.numberOfBytesPerFile = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--bytes", programModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFiles) });

   args.parallel = _docoptParser->GetRequiredBool(docoptValues, "--parallel");
   args.verbose = _docoptParser->GetRequiredBool(docoptValues, "--verbose");
   return args;
}

ProgramMode FileArbArgsParser::DetermineProgramMode(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode)
{
   if (isCreateTextFilesMode)
   {
      return ProgramMode::CreateTextFiles;
   }
   else
   {
      release_assert(isCreateBinaryFilesMode);
      return ProgramMode::CreateBinaryFiles;
   }
}

string FileArbArgsParser::DetermineFileExtension(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode)
{
   if (isCreateTextFilesMode)
   {
      return ".txt"s;
   }
   else
   {
      release_assert(isCreateBinaryFilesMode);
      return ".bin"s;
   }
}

void FileArbArgsParser::PrintPreamble(const FileArbArgs& args) const
{
   const string runningMessage = "[FileArb] CommandLine: " + args.commandLine;
   _console->WriteLine(runningMessage);
}
