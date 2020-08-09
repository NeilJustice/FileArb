#include "pch.h"
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"

TESTS(FileArbArgsEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldsNotEqual)
AFACT(ZenUnitRandom_FileArbArgs_ReturnsAllNonDefaultFields)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldsNotEqual)
{
   SETUP_EQUALIZER_TEST(FileArbArgs);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, commandLine, ZenUnit::Random<string>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, programMode, ZenUnit::RandomNon0Enum<ProgramMode>(ProgramMode::MaxValue));
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfFilesToCreate, ZenUnit::RandomNon0<size_t>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfLinesPerFile, ZenUnit::RandomNon0<size_t>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfCharactersPerLine, ZenUnit::RandomNon0<size_t>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfDirectoriesToCreate, ZenUnit::RandomNon0<size_t>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, targetDirectoryPath, ZenUnit::Random<string>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, parallel, true);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, verbose, true);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, fileExtension, ZenUnit::Random<string>());
}

TEST(ZenUnitRandom_FileArbArgs_ReturnsAllNonDefaultFields)
{
   const FileArbArgs randomFileArbArgs = ZenUnit::Random<FileArbArgs>();
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.commandLine);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.programMode);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.numberOfFilesToCreate);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.numberOfLinesPerFile);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.numberOfCharactersPerLine);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.numberOfDirectoriesToCreate);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.targetDirectoryPath);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.parallel);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.verbose);
   IS_NOT_DEFAULT_VALUE(randomFileArbArgs.fileExtension);
}

RUN_TESTS(FileArbArgsEqualizerAndRandomTests)
