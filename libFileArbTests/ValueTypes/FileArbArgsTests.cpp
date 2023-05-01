#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

TESTS(FileArbArgsTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(CommandLineUsage_create_binary_file_args_AreExpectedStrings)
AFACT(CommandLineUsage_create_binary_files_args_AreExpectedStrings)
AFACT(CommandLineUsage_create_text_file_args_AreExpectedStrings)
AFACT(CommandLineUsage_create_text_files_args_AreExpectedStrings)
AFACT(CommandLineUsage_IsExpectedString)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   const FileArbArgs defaultFileArbArgs{};
   FileArbArgs expectedDefaultFileArbArgs{};
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
   expectedDefaultFileArbArgs.quiet = false;
   expectedDefaultFileArbArgs.fileNamePrefix = "";
   expectedDefaultFileArbArgs.fileExtension = "";
   ARE_EQUAL(expectedDefaultFileArbArgs, defaultFileArbArgs);
}

TEST(CommandLineUsage_create_binary_file_args_AreExpectedStrings)
{
   const string expectedArgs =
R"(filearb create-binary-file
   --target=<DirectoryPath>
   --bytes=<NumberOfBytes>
   [--random-bytes])";
   ARE_EQUAL(expectedArgs, FileArbArgs::CommandLineUsage_create_binary_file_args);

   const string expectedUsage =
R"(Usage:
   )" + expectedArgs;
   ARE_EQUAL(expectedUsage, FileArbArgs::CommandLineUsage_create_binary_file);
}

TEST(CommandLineUsage_create_binary_files_args_AreExpectedStrings)
{
   const string expectedArgs =
R"(filearb create-binary-files
   --target=<DirectoryPath>
   --directories=<NumberOfDirectories>
   --files=<NumberOfFiles>
   --bytes=<BytesPerFile>
   [--random-bytes]
   [--parallel]
   [--quiet])";
   ARE_EQUAL(expectedArgs, FileArbArgs::CommandLineUsage_create_binary_files_args);

   const string expectedUsage =
R"(Usage:
   )" + expectedArgs;
   ARE_EQUAL(expectedUsage, FileArbArgs::CommandLineUsage_create_binary_files);
}

TEST(CommandLineUsage_create_text_file_args_AreExpectedStrings)
{
   const string expectedArgs =
R"(filearb create-text-file
   --target=<DirectoryPath>
   --lines=<LinesPerFile>
   --characters=<CharactersPerLine>
   [--random-letters])";
   ARE_EQUAL(expectedArgs, FileArbArgs::CommandLineUsage_create_text_file_args);

   const string expectedUsage =
R"(Usage:
   )" + expectedArgs;
   ARE_EQUAL(expectedUsage, FileArbArgs::CommandLineUsage_create_text_file);
}

TEST(CommandLineUsage_create_text_files_args_AreExpectedStrings)
{
   const string expectedArgs =
R"(filearb create-text-files
   --target=<DirectoryPath>
   --directories=<NumberOfDirectories>
   --files=<FilesPerDirectory>
   --lines=<LinesPerFile>
   --characters=<CharactersPerLine>
   [--random-letters]
   [--parallel]
   [--quiet])";
   ARE_EQUAL(expectedArgs, FileArbArgs::CommandLineUsage_create_text_files_args);

   const string expectedUsage =
R"(Usage:
   )" + expectedArgs;
   ARE_EQUAL(expectedUsage, FileArbArgs::CommandLineUsage_create_text_files);
}

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(FileArb v1.1.0 - Creates arbitrarily large text files or binary files.
Optional suffixes for --bytes arguments: b or B, k or K, m or M, and g or G.

Usage:
   filearb create-binary-file
      --target=<DirectoryPath>
      --bytes=<NumberOfBytes>
      [--random-bytes]
   filearb create-binary-files
      --target=<DirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<NumberOfFiles>
      --bytes=<BytesPerFile>
      [--random-bytes]
      [--parallel]
      [--quiet]
   filearb create-text-file
      --target=<DirectoryPath>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--random-letters]
   filearb create-text-files
      --target=<DirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--random-letters]
      [--parallel]
      [--quiet]
)", FileArbArgs::CommandLineUsage);
}

RUN_TESTS(FileArbArgsTests)
