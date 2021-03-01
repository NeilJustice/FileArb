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
   bool randomBytes = false;
   bool randomChars = false;
   bool parallel = false;
   bool minimal = false;

   // Calculated fields
   string fileNamePrefix;
   string fileExtension;
};

#ifdef _WIN32
#ifdef _DEBUG
static_assert(sizeof(FileArbArgs) == 216);
#else
static_assert(sizeof(FileArbArgs) == 184);
#endif
#endif
