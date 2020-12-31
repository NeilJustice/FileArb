#pragma once

struct FileArbArgs
{
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
   bool parallel = false;
   bool verbose = false;

   // Calculated fields
   string fileExtension;
};

#ifdef _WIN32
#ifdef _DEBUG
static_assert(sizeof(FileArbArgs) == 176);
#else
static_assert(sizeof(FileArbArgs) == 152);
#endif
#endif
