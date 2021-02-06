#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

const string FileArbArgs::CommandLineUsage =
R"(FileArb v0.9.0
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
)";
