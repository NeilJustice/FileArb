#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"

FileArbArgsParser::FileArbArgsParser()
   // Function Pointers
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
   args.commandLine = Vector::JoinWithSeparator(stringArgs, ' ');
   const map<string, docopt::Value> docoptValues = _docoptParser->ParseArgs(FileArbArgs::CommandLineUsage, stringArgs);
   const bool isCreateTextFile = _docoptParser->GetRequiredBool(docoptValues, "create-text-file");
   const bool isCreateTextFilesMode = _docoptParser->GetRequiredBool(docoptValues, "create-text-files");
   const bool isCreateBinaryFileMode = _docoptParser->GetRequiredBool(docoptValues, "create-binary-file");
   const bool isCreateBinaryFilesMode = _docoptParser->GetRequiredBool(docoptValues, "create-binary-files");
   args.programMode = _call_DetermineProgramMode(isCreateTextFile, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);
   args.fileExtension = _call_DetermineFileExtension(isCreateTextFile, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);
   args.targetDirectoryPath = _docoptParser->GetRequiredString(docoptValues, "--target");

   static const vector<int> allProgramModesAsInts =
   {
      static_cast<int>(ProgramMode::CreateTextFile),
      static_cast<int>(ProgramMode::CreateTextFiles),
      static_cast<int>(ProgramMode::CreateBinaryFile),
      static_cast<int>(ProgramMode::CreateBinaryFiles)
   };
   const int programModeAsInt = static_cast<int>(args.programMode);

   args.numberOfDirectoriesToCreate = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--directories", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) });

   args.numberOfFilesToCreate = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--files", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFiles), static_cast<int>(ProgramMode::CreateBinaryFiles) });

   args.numberOfLinesPerFile = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--lines", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) });

   args.numberOfCharactersPerLine = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--characters", programModeAsInt, { static_cast<int>(ProgramMode::CreateTextFile), static_cast<int>(ProgramMode::CreateTextFiles) });

   args.numberOfBytesPerFile = _docoptParser->GetProgramModeSpecificRequiredSizeT(
      docoptValues, "--bytes", programModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFile), static_cast<int>(ProgramMode::CreateBinaryFiles) });

   args.randomBytes = _docoptParser->GetOptionalBool(docoptValues, "--random-bytes");
   args.parallel = _docoptParser->GetOptionalBool(docoptValues, "--parallel");
   args.verbose = _docoptParser->GetOptionalBool(docoptValues, "--verbose");
   return args;
}

ProgramMode FileArbArgsParser::DetermineProgramMode(
   bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode)
{
   if (isCreateTextFileMode)
   {
      return ProgramMode::CreateTextFile;
   }
   else if (isCreateTextFilesMode)
   {
      return ProgramMode::CreateTextFiles;
   }
   else if (isCreateBinaryFileMode)
   {
      return ProgramMode::CreateBinaryFile;
   }
   release_assert(isCreateBinaryFilesMode);
   return ProgramMode::CreateBinaryFiles;
}

string FileArbArgsParser::DetermineFileExtension(
   bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode)
{
   if (isCreateTextFileMode)
   {
      return ".txt"s;
   }
   else if (isCreateTextFilesMode)
   {
      return ".txt"s;
   }
   else if (isCreateBinaryFileMode)
   {
      return ".bin"s;
   }
   release_assert(isCreateBinaryFilesMode);
   return ".bin"s;
}
