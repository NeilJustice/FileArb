#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

TESTS(FileArbArgsTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
AFACT(CommandLineUsage_IsExpectedString)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsTo0)
{
   const FileArbArgs defaultFileArbArgs;
   FileArbArgs expectedDefaultFileArbArgs;
   expectedDefaultFileArbArgs.commandLine = "";
   expectedDefaultFileArbArgs.programMode = ProgramMode::Unset;
   expectedDefaultFileArbArgs.targetDirectoryPath = fs::path();
   expectedDefaultFileArbArgs.numberOfDirectoriesToCreate = 0;
   expectedDefaultFileArbArgs.numberOfFilesToCreate = 0;
   expectedDefaultFileArbArgs.numberOfLinesPerFile = 0;
   expectedDefaultFileArbArgs.numberOfCharactersPerLine = 0;
   expectedDefaultFileArbArgs.numberOfBytesPerFile = 0;
   expectedDefaultFileArbArgs.randomBytes = false;
   expectedDefaultFileArbArgs.parallel = false;
   expectedDefaultFileArbArgs.verbose = false;
   expectedDefaultFileArbArgs.fileExtension = "";
   ARE_EQUAL(expectedDefaultFileArbArgs, defaultFileArbArgs);
}

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(FileArb v0.9.1
Creates an arbitrary number of text files or binary files
containing an arbitrary number of lines, characters, or bytes
for performance testing FileRevisor or filesystems in general.
--bytes=<BytesPerFile> optional suffixes: B, KB, MB, GB
https://github.com/NeilJustice/FileArb

Usage:
   filearb create-text-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--parallel]
      [--verbose]
   filearb create-binary-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<NumberOfFiles>
      --bytes=<BytesPerFile>
      [--random-bytes]
      [--parallel]
      [--verbose]
)", FileArbArgs::CommandLineUsage);
}

RUN_TESTS(FileArbArgsTests)
