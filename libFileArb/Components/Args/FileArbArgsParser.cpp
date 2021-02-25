#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Args/FileArbArgsParser.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"

FileArbArgsParser::FileArbArgsParser()
   // Function Pointers
   : _call_DetermineProgramMode(FileArbArgsParser::DetermineProgramMode)
   , _call_GetFileNamePrefixAndFileExtension(FileArbArgsParser::GetFileNamePrefixAndFileExtension)
   // Constant Components
   , _bytesStringConverter(make_unique<BytesStringConverter>())
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

   const pair<string, string> fileNamePrefixAndFileExtension = _call_GetFileNamePrefixAndFileExtension(
      isCreateTextFile, isCreateTextFilesMode, isCreateBinaryFileMode, isCreateBinaryFilesMode);
   args.fileNamePrefix = fileNamePrefixAndFileExtension.first;
   args.fileExtension = fileNamePrefixAndFileExtension.second;

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

   const string bytesString = _docoptParser->GetProgramModeSpecificRequiredString(
      docoptValues, "--bytes", programModeAsInt, { static_cast<int>(ProgramMode::CreateBinaryFile), static_cast<int>(ProgramMode::CreateBinaryFiles) });
   args.numberOfBytesPerFile = _bytesStringConverter->ConvertBytesStringToBytes(bytesString);

   args.randomBytes = _docoptParser->GetOptionalBool(docoptValues, "--random-bytes");
   args.parallel = _docoptParser->GetOptionalBool(docoptValues, "--parallel");
   args.minimal = _docoptParser->GetOptionalBool(docoptValues, "--minimal");
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

pair<string, string> FileArbArgsParser::GetFileNamePrefixAndFileExtension(
   bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode)
{
   if (isCreateTextFileMode || isCreateTextFilesMode)
   {
      return make_pair("text", ".txt");
   }
   release_assert(isCreateBinaryFileMode || isCreateBinaryFilesMode);
   return make_pair("binary", ".bin");
}
