#pragma once

struct FileArbArgs
{
   static const string CommandLineUsage_create_binary_file_args;
   static const string CommandLineUsage_create_binary_file;

   static const string CommandLineUsage_create_binary_files_args;
   static const string CommandLineUsage_create_binary_files;

   static const string CommandLineUsage_create_text_file_args;
   static const string CommandLineUsage_create_text_file;

   static const string CommandLineUsage_create_text_files_args;
   static const string CommandLineUsage_create_text_files;

   static const string CommandLineUsage;

   // Command line fields
   string commandLine;
   ProgramMode programMode = ProgramMode::Unset;
   fs::path targetDirectoryPath;
   size_t numberOfDirectoriesToCreate = 0;
   size_t numberOfFilesToCreate = 0;
   size_t numberOfLinesPerFile = 0;
   size_t numberOfCharactersPerLine = 0;
   size_t numberOfBytesPerFile = 0;
   bool generateRandomBytes = false;
   bool generateRandomLetters = false;
   bool parallel = false;
   bool quiet = false;

   // Calculated fields
   string fileNamePrefix;
   string fileExtension;
};
