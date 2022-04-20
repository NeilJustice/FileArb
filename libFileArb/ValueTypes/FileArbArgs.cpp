#include "pch.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

const string FileArbArgs::CommandLineUsage_create_binary_file_args =
R"(filearb create-binary-file
   --target=<DirectoryPath>
   --bytes=<NumberOfBytes>
   [--random-bytes])";
const string FileArbArgs::CommandLineUsage_create_binary_file =
R"(Usage:
   )" + CommandLineUsage_create_binary_file_args;

const string FileArbArgs::CommandLineUsage_create_text_file_args =
R"(filearb create-text-file
   --target=<DirectoryPath>
   --lines=<LinesPerFile>
   --characters=<CharactersPerLine>
   [--random-letters])";
const string FileArbArgs::CommandLineUsage_create_text_file =
R"(Usage:
   )" + CommandLineUsage_create_text_file_args;

const string FileArbArgs::CommandLineUsage_create_binary_files_args =
R"(filearb create-binary-files
   --target=<DirectoryPath>
   --directories=<NumberOfDirectories>
   --files=<NumberOfFiles>
   --bytes=<BytesPerFile>
   [--random-bytes]
   [--parallel]
   [--quiet])";
const string FileArbArgs::CommandLineUsage_create_binary_files =
R"(Usage:
   )" + CommandLineUsage_create_binary_files_args;

const string FileArbArgs::CommandLineUsage_create_text_files_args =
R"(filearb create-text-files
   --target=<DirectoryPath>
   --directories=<NumberOfDirectories>
   --files=<FilesPerDirectory>
   --lines=<LinesPerFile>
   --characters=<CharactersPerLine>
   [--random-letters]
   [--parallel]
   [--quiet])";
const string FileArbArgs::CommandLineUsage_create_text_files =
R"(Usage:
   )" + CommandLineUsage_create_text_files_args;

const string FileArbArgs::CommandLineUsage =
R"(FileArb v1.0.0 - Creates arbitrarily large text files or binary files.
Optional suffixes for --bytes arguments: b or B, k or K, m or M, and g or G.

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
      [--quiet]
   filearb create-text-files
      --target=<DirectoryPath>
      --directories=<NumberOfDirectories>
      --files=<FilesPerDirectory>
      --lines=<LinesPerFile>
      --characters=<CharactersPerLine>
      [--random-letters]
      [--parallel]
      [--quiet]
)";
