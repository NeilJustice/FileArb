#pragma once

struct FileArbArgs
{
   static const string CommandLineUsage;

   string commandLine;
   ProgramMode programMode = ProgramMode::Unset;
   fs::path targetDirectoryPath;
   size_t numberOfDirectoriesToCreate = 0;
   size_t numberOfFilesToCreate = 0;
   size_t numberOfLinesPerFile = 0;
   size_t numberOfCharactersPerLine = 0;
   size_t numberOfBytesPerFile = 0;
   bool parallel = false;
   bool verbose = false;

   string fileExtension;
};
