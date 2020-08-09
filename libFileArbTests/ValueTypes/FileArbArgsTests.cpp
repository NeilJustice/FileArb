#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

TESTS(FileArbArgsTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
AFACT(Usage_IsExpectedString)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsTo0)
{
   FileArbArgs args;
   ARE_EQUAL("", args.commandLine);
   ARE_EQUAL(ProgramMode::Unset, args.programMode);
   ARE_EQUAL(fs::path(), args.targetDirectoryPath);
   IS_ZERO(args.numberOfDirectoriesToCreate);
   IS_ZERO(args.numberOfFilesToCreate);
   IS_ZERO(args.numberOfLinesPerFile);
   IS_ZERO(args.numberOfCharactersPerLine);
   IS_ZERO(args.numberOfBytesPerFile);
   IS_FALSE(args.parallel);
   IS_FALSE(args.verbose);
   ARE_EQUAL("", args.fileExtension);
}

TEST(Usage_IsExpectedString)
{
   ARE_EQUAL(
R"(FileArb v0.9.0 - Creates an arbitrary number of text or binary files.
https://github.com/NeilJustice/FileArb

Usage:
   filearb create-text-files --target=<TargetDirectoryPath> --directories=<NumberOfDirectories> --files=<FilesPerDirectory> --lines=<LinesPerFile> --characters=<CharactersPerLine> [--parallel] [--verbose]
   filearb create-binary-files --target=<TargetDirectoryPath> --directories=<NumberOfDirectories> --files=<NumberOfFiles> --bytes=<BytesPerFile> [--parallel] [--verbose]
)", FileArbArgs::CommandLineUsage);
}

RUN_TESTS(FileArbArgsTests)
