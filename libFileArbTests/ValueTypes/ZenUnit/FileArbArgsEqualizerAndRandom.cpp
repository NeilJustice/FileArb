#include "pch.h"
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FileArbArgs>::AssertEqual(const FileArbArgs& expectedFileArbArgs, const FileArbArgs& actualFileArbArgs)
   {
      ARE_EQUAL(expectedFileArbArgs.commandLine, actualFileArbArgs.commandLine);
      ARE_EQUAL(expectedFileArbArgs.programMode, actualFileArbArgs.programMode);
      ARE_EQUAL(expectedFileArbArgs.numberOfFilesToCreate, actualFileArbArgs.numberOfFilesToCreate);
      ARE_EQUAL(expectedFileArbArgs.numberOfLinesPerFile, actualFileArbArgs.numberOfLinesPerFile);
      ARE_EQUAL(expectedFileArbArgs.numberOfCharactersPerLine, actualFileArbArgs.numberOfCharactersPerLine);
      ARE_EQUAL(expectedFileArbArgs.numberOfDirectoriesToCreate, actualFileArbArgs.numberOfDirectoriesToCreate);
      ARE_EQUAL(expectedFileArbArgs.targetDirectoryPath, actualFileArbArgs.targetDirectoryPath);
      ARE_EQUAL(expectedFileArbArgs.parallel, actualFileArbArgs.parallel);
      ARE_EQUAL(expectedFileArbArgs.verbose, actualFileArbArgs.verbose);
      ARE_EQUAL(expectedFileArbArgs.fileExtension, actualFileArbArgs.fileExtension);
   }

   template<>
   FileArbArgs Random()
   {
      FileArbArgs randomFileArbArgs;
      randomFileArbArgs.commandLine = ZenUnit::Random<string>();
      randomFileArbArgs.programMode = ZenUnit::RandomNon0Enum<ProgramMode>(ProgramMode::MaxValue);
      randomFileArbArgs.numberOfFilesToCreate = ZenUnit::RandomNon0<size_t>();
      randomFileArbArgs.numberOfLinesPerFile = ZenUnit::RandomNon0<size_t>();
      randomFileArbArgs.numberOfCharactersPerLine = ZenUnit::RandomNon0<size_t>();
      randomFileArbArgs.numberOfDirectoriesToCreate = ZenUnit::RandomNon0<size_t>();
      randomFileArbArgs.targetDirectoryPath = ZenUnit::Random<string>();
      randomFileArbArgs.parallel = true;
      randomFileArbArgs.verbose = true;
      randomFileArbArgs.fileExtension = ZenUnit::Random<string>();
      return randomFileArbArgs;
   };
}
