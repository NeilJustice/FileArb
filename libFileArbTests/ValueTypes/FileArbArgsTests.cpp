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
   expectedDefaultFileArbArgs.generateRandomBytes = false;
   expectedDefaultFileArbArgs.generateRandomLetters = false;
   expectedDefaultFileArbArgs.parallel = false;
   expectedDefaultFileArbArgs.minimal = false;
   expectedDefaultFileArbArgs.fileNamePrefix = "";
   expectedDefaultFileArbArgs.fileExtension = "";
   ARE_EQUAL(expectedDefaultFileArbArgs, defaultFileArbArgs);
}

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(FileArb v0.13.0
Creates an arbitrary number of text files or binary files
containing an arbitrary number of lines, characters, or bytes.
Optional suffixes for --bytes=<BytesPerFile>:
b or B, k or K, m or M, g or G.
https://github.com/NeilJustice/FileArb

Usage:
   filearb create-binary-file
      --target=<DirectoryPath>
      --bytes=<NumberOfBytes>
      [--random-bytes]
   filearb create-text-file
      --target=<DirectoryPath>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--random-letters]
   filearb create-binary-files
      --target=<DirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<NumberOfFiles>
      --bytes=<BytesPerFile>
      [--random-bytes]
      [--parallel]
      [--minimal]
   filearb create-text-files
      --target=<DirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--random-letters]
      [--parallel]
      [--minimal]
)", FileArbArgs::CommandLineUsage);
}

RUN_TESTS(FileArbArgsTests)
