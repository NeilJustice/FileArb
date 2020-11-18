#include "pch.h"
#include "libFileArbTests/ValueTypes/ZenUnit/FileArbArgsEqualizerAndRandom.h"

TESTS(FileArbArgsEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldsNotEqual)
AFACT(TestableFileArbArgs_ReturnsFileArbArgsWithAllRandomFields)
AFACT(ZenUnitRandom_FileArbArgs_DoesNotThrowException)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldsNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(FileArbArgs);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, commandLine, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, programMode, ZenUnit::RandomNon0Enum<ProgramMode>(ProgramMode::MaxValue));
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, targetDirectoryPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfDirectoriesToCreate, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfFilesToCreate, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfLinesPerFile, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfCharactersPerLine, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, numberOfBytesPerFile, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, parallel, true);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, verbose, true);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileArbArgs, fileExtension, ZenUnit::Random<string>());
}

TEST(TestableFileArbArgs_ReturnsFileArbArgsWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const string commandLine = ZenUnit::Random<string>();
   const string fileExtension = ZenUnit::Random<string>();
   randomGeneratorMock.StringMock.ReturnValues(commandLine, fileExtension);

   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   const fs::path targetDirectoryPath = randomGeneratorMock.FilesystemPathMock.ReturnRandom();

   const size_t numberOfDirectoriesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfFilesToCreate = ZenUnit::Random<size_t>();
   const size_t numberOfLinesPerFile = ZenUnit::Random<size_t>();
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   const size_t numberOfBytesPerFile = ZenUnit::Random<size_t>();
   randomGeneratorMock.SizeTMock.ReturnValues(
      numberOfDirectoriesToCreate,
      numberOfFilesToCreate,
      numberOfLinesPerFile,
      numberOfCharactersPerLine,
      numberOfBytesPerFile);

   const bool parallel = ZenUnit::Random<bool>();
   const bool verbose = ZenUnit::Random<bool>();
   randomGeneratorMock.BoolMock.ReturnValues(parallel, verbose);
   //
   const FileArbArgs randomFileArbArgs = TestableFileArbArgs(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(ProgramMode::MaxValue)));
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledOnce());
   METALMOCK(randomGeneratorMock.SizeTMock.CalledNTimes(5));
   METALMOCK(randomGeneratorMock.BoolMock.CalledNTimes(2));
   FileArbArgs expectedRandomFileArbArgs;
   expectedRandomFileArbArgs.commandLine = commandLine;
   expectedRandomFileArbArgs.programMode = programMode;
   expectedRandomFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedRandomFileArbArgs.numberOfDirectoriesToCreate = numberOfDirectoriesToCreate;
   expectedRandomFileArbArgs.numberOfFilesToCreate = numberOfFilesToCreate;
   expectedRandomFileArbArgs.numberOfLinesPerFile = numberOfLinesPerFile;
   expectedRandomFileArbArgs.numberOfCharactersPerLine = numberOfCharactersPerLine;
   expectedRandomFileArbArgs.numberOfBytesPerFile = numberOfBytesPerFile;
   expectedRandomFileArbArgs.targetDirectoryPath = targetDirectoryPath;
   expectedRandomFileArbArgs.parallel = parallel;
   expectedRandomFileArbArgs.verbose = verbose;
   expectedRandomFileArbArgs.fileExtension = fileExtension;
   ARE_EQUAL(expectedRandomFileArbArgs, randomFileArbArgs);
}

TEST(ZenUnitRandom_FileArbArgs_DoesNotThrowException)
{
   ZenUnit::Random<FileArbArgs>();
}

RUN_TESTS(FileArbArgsEqualizerAndRandomTests)
