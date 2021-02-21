#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

const string FileArbArgs::CommandLineUsage =
R"(FileArb v0.10.0
Creates an arbitrary number of text files or binary files
containing an arbitrary number of lines, characters, or bytes.
Optional suffixes for --bytes=<BytesPerFile>: B, KB, MB, or GB
https://github.com/NeilJustice/FileArb

Usage:
   filearb create-binary-file
      --target=<TargetDirectoryPath>
      --bytes=<BytesPerFile>
      [--random-bytes]
   filearb create-binary-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<NumberOfFiles>
      --bytes=<BytesPerFile>
      [--random-bytes]
      [--parallel]
      [--minimal]
   filearb create-text-file
      --target=<TargetDirectoryPath>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
   filearb create-text-files
      --target=<TargetDirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--parallel]
      [--minimal]
)";
