#include "pch.h"
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FileArbArgs>::AssertEqual(const FileArbArgs& expectedFileArbArgs, const FileArbArgs& actualFileArbArgs)
   {
      ARE_EQUAL(expectedFileArbArgs.commandLine, actualFileArbArgs.commandLine);
      ARE_EQUAL(expectedFileArbArgs.programMode, actualFileArbArgs.programMode);
      ARE_EQUAL(expectedFileArbArgs.targetDirectoryPath, actualFileArbArgs.targetDirectoryPath);
      ARE_EQUAL(expectedFileArbArgs.numberOfDirectoriesToCreate, actualFileArbArgs.numberOfDirectoriesToCreate);
      ARE_EQUAL(expectedFileArbArgs.numberOfFilesToCreate, actualFileArbArgs.numberOfFilesToCreate);
      ARE_EQUAL(expectedFileArbArgs.numberOfLinesPerFile, actualFileArbArgs.numberOfLinesPerFile);
      ARE_EQUAL(expectedFileArbArgs.numberOfCharactersPerLine, actualFileArbArgs.numberOfCharactersPerLine);
      ARE_EQUAL(expectedFileArbArgs.numberOfBytesPerFile, actualFileArbArgs.numberOfBytesPerFile);
      ARE_EQUAL(expectedFileArbArgs.generateRandomBytes, actualFileArbArgs.generateRandomBytes);
      ARE_EQUAL(expectedFileArbArgs.generateRandomChars, actualFileArbArgs.generateRandomChars);
      ARE_EQUAL(expectedFileArbArgs.parallel, actualFileArbArgs.parallel);
      ARE_EQUAL(expectedFileArbArgs.minimal, actualFileArbArgs.minimal);
      ARE_EQUAL(expectedFileArbArgs.fileNamePrefix, actualFileArbArgs.fileNamePrefix);
      ARE_EQUAL(expectedFileArbArgs.fileExtension, actualFileArbArgs.fileExtension);
   }

   FileArbArgs TestableFileArbArgs(const RandomGenerator* randomGenerator)
   {
      FileArbArgs randomFileArbArgs;
      randomFileArbArgs.commandLine = randomGenerator->String();
      randomFileArbArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
      randomFileArbArgs.targetDirectoryPath = randomGenerator->FilesystemPath();
      randomFileArbArgs.numberOfDirectoriesToCreate = randomGenerator->SizeT();
      randomFileArbArgs.numberOfFilesToCreate = randomGenerator->SizeT();
      randomFileArbArgs.numberOfLinesPerFile = randomGenerator->SizeT();
      randomFileArbArgs.numberOfCharactersPerLine = randomGenerator->SizeT();
      randomFileArbArgs.numberOfBytesPerFile = randomGenerator->SizeT();
      randomFileArbArgs.generateRandomBytes = randomGenerator->Bool();
      randomFileArbArgs.generateRandomChars = randomGenerator->Bool();
      randomFileArbArgs.parallel = randomGenerator->Bool();
      randomFileArbArgs.minimal = randomGenerator->Bool();
      randomFileArbArgs.fileNamePrefix = randomGenerator->String();
      randomFileArbArgs.fileExtension = randomGenerator->String();
      return randomFileArbArgs;
   }

   template<>
   FileArbArgs Random()
   {
      return TestableFileArbArgs(RandomGenerator::Instance());
   }
}
