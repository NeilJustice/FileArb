#pragma once

struct FileArbArgs
{
   static const string CommandLineUsage;

   // Command line fields
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
