#include "pch.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"
#include "libFileArbTests/Components/Makers/MetalMock/LineReplicatorMock.h"
#include "libFileArbTests/Components/Makers/MetalMock/RandomStringMakerMock.h"

TESTS(TextFileTextMakerTests)
AFACT(DefaultConstructor_SetsReplicateLineNTimesFunction)
AFACT(MakeNonRandomFileText_ReturnsAllZerosStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
AFACT(MakeRandomFileText_ReturnsRandomCharsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
EVIDENCE

TextFileTextMaker _textFileTextMaker;
// Constant Components
LineReplicatorMock* _lineReplicatorMock = nullptr;
RandomStringMakerMock* _randomStringMakerMock = nullptr;

STARTUP
{
   // Constant Components
   _textFileTextMaker._lineReplicator.reset(_lineReplicatorMock = new LineReplicatorMock);
   _textFileTextMaker._randomStringMaker.reset(_randomStringMakerMock = new RandomStringMakerMock);
}

TEST(DefaultConstructor_SetsReplicateLineNTimesFunction)
{
   TextFileTextMaker textFileTextMaker;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(textFileTextMaker._lineReplicator);
   DELETE_TO_ASSERT_NEWED(textFileTextMaker._randomStringMaker);
}

TEST(MakeNonRandomFileText_ReturnsAllZerosStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
{
   const string fileText = _lineReplicatorMock->ReplicateLineNTimesMock.ReturnRandom();
   const size_t numberOfLines = ZenUnit::RandomBetween<size_t>(0, 2);
   const size_t numberOfCharactersPerLine = ZenUnit::RandomBetween<size_t>(0, 2);
   //
   const string returnedFileText = _textFileTextMaker.MakeNonRandomFileText(numberOfLines, numberOfCharactersPerLine);
   //
   string expectedLineToWrite(numberOfCharactersPerLine + 1, '0');
   expectedLineToWrite[expectedLineToWrite.size() - 1] = '\n';
   METALMOCK(_lineReplicatorMock->ReplicateLineNTimesMock.CalledOnceWith(expectedLineToWrite, numberOfLines));
   ARE_EQUAL(fileText, returnedFileText);
}

TEST(MakeRandomFileText_ReturnsRandomCharsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
{
   const string randomCapitalLettersString1 = ZenUnit::Random<string>();
   const string randomCapitalLettersString2 = ZenUnit::Random<string>();
   const string randomCapitalLettersString3 = ZenUnit::Random<string>();
   _randomStringMakerMock->MakeRandomCapitalLettersStringMock.ReturnValues(
      randomCapitalLettersString1, randomCapitalLettersString2, randomCapitalLettersString3);
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   //
   const string randomCapitalLettersFileText = _textFileTextMaker.MakeRandomFileText(3, numberOfCharactersPerLine);
   //
   METALMOCK(_randomStringMakerMock->MakeRandomCapitalLettersStringMock.CalledNTimesWith(3, numberOfCharactersPerLine));
   const string expectedRandomCapitalLettersFileText =
      randomCapitalLettersString1 + "\n" +
      randomCapitalLettersString2 + "\n" +
      randomCapitalLettersString3 + "\n";
   ARE_EQUAL(expectedRandomCapitalLettersFileText, randomCapitalLettersFileText);
}

RUN_TESTS(TextFileTextMakerTests)
