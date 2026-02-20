
#pragma once
#include "libFileArb/ValueTypes/FileArbArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<FileArbArgs>
   {
      static void AssertEqual(const FileArbArgs& expectedFileArbArgs, const FileArbArgs& actualFileArbArgs)
      {
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, programMode);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, targetDirectoryPath);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, numberOfDirectoriesToCreate);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, numberOfFilesToCreate);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, numberOfLinesPerFile);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, numberOfCharactersPerLine);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, numberOfBytesPerFile);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, generateRandomBytes);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, generateRandomLetters);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, parallel);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, quiet);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, fileNamePrefix);
         FIELDS_ARE_EQUAL(expectedFileArbArgs, actualFileArbArgs, fileExtension);
      }
   };

   inline FileArbArgs TestableFileArbArgs(const RandomGenerator* randomGenerator)
   {
      FileArbArgs randomFileArbArgs;
      randomFileArbArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
      randomFileArbArgs.targetDirectoryPath = randomGenerator->FilesystemPath();
      randomFileArbArgs.numberOfDirectoriesToCreate = randomGenerator->SizeT();
      randomFileArbArgs.numberOfFilesToCreate = randomGenerator->SizeT();
      randomFileArbArgs.numberOfLinesPerFile = randomGenerator->SizeT();
      randomFileArbArgs.numberOfCharactersPerLine = randomGenerator->SizeT();
      randomFileArbArgs.numberOfBytesPerFile = randomGenerator->SizeT();
      randomFileArbArgs.generateRandomBytes = randomGenerator->Bool();
      randomFileArbArgs.generateRandomLetters = randomGenerator->Bool();
      randomFileArbArgs.parallel = randomGenerator->Bool();
      randomFileArbArgs.quiet = randomGenerator->Bool();
      randomFileArbArgs.fileNamePrefix = randomGenerator->String();
      randomFileArbArgs.fileExtension = randomGenerator->String();
      return randomFileArbArgs;
   }

   template<>
   inline FileArbArgs Random()
   {
      return TestableFileArbArgs(RandomGenerator::Instance());
   }
}
