#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

const string FileArbArgs::CommandLineUsage =
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
)";
