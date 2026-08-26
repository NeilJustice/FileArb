
#pragma once
#include "libFileArb/ValueTypes/FileArbArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<FileArbArgs>
   {
      static void AssertEqual(const FileArbArgs& expectedArgs, const FileArbArgs& actualFileArbArgs)
      {
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, programMode);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, targetDirectoryPath);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, numberOfDirectoriesToCreate);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, numberOfFilesToCreate);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, numberOfLinesPerFile);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, numberOfCharactersPerLine);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, numberOfBytesPerFile);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, generateRandomBytes);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, generateRandomLetters);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, parallel);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, quiet);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, fileNamePrefix);
         FIELDS_ARE_EQUAL(expectedArgs, actualFileArbArgs, fileExtension);
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
