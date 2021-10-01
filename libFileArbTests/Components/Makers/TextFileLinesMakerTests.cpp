#include "pch.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"
#include "libFileArbTests/Components/Makers/MetalMock/RandomStringMakerMock.h"

TESTS(TextFileLinesMakerTests)
AFACT(DefaultConstructor_SetsReplicateLineNTimesFunction)
AFACT(MakeFileText_GenerateRandomCharsIsTrue_ReturnsRandomCharsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
AFACT(MakeFileText_GenerateRandomCharsIsFalse_ReturnsAllZerosStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
FACTS(ReplicateLineNTimes_ReturnsLineReplicatedNTimes)
EVIDENCE

TextFileLinesMaker _textFileLinesMaker;
// Function Pointers
METALMOCK_NONVOID2_STATIC(string, FileTextGenerator, ReplicateLineNTimes, const string&, size_t)
// Constant Components
RandomStringMakerMock* _randomStringMakerMock = nullptr;

STARTUP
{
   // Function Pointers
   _textFileLinesMaker._call_ReplicateLineNTimes = BIND_2ARG_METALMOCK_OBJECT(ReplicateLineNTimesMock);
   // Constant Components
   _textFileLinesMaker._randomStringMaker.reset(_randomStringMakerMock = new RandomStringMakerMock);
}

TEST(DefaultConstructor_SetsReplicateLineNTimesFunction)
{
   TextFileLinesMaker textFileLinesMaker;
   // Function Pointers
   STD_FUNCTION_TARGETS(TextFileLinesMaker::ReplicateLineNTimes, textFileLinesMaker._call_ReplicateLineNTimes);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(textFileLinesMaker._randomStringMaker);
}

TEST(MakeFileText_GenerateRandomCharsIsTrue_ReturnsRandomCharsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
{
   const string randomCapitalLettersString1 = ZenUnit::Random<string>();
   const string randomCapitalLettersString2 = ZenUnit::Random<string>();
   const string randomCapitalLettersString3 = ZenUnit::Random<string>();
   _randomStringMakerMock->MakeRandomCapitalLettersStringMock.ReturnValues(
      randomCapitalLettersString1, randomCapitalLettersString2, randomCapitalLettersString3);
   const size_t numberOfCharactersPerLine = ZenUnit::Random<size_t>();
   //
   const string randomCapitalLettersFileText = _textFileLinesMaker.MakeFileText(3, numberOfCharactersPerLine, true);
   //
   METALMOCK(_randomStringMakerMock->MakeRandomCapitalLettersStringMock.CalledNTimesWith(3, numberOfCharactersPerLine));
   const string expectedRandomCapitalLettersFileText =
      randomCapitalLettersString1 + "\n" +
      randomCapitalLettersString2 + "\n" +
      randomCapitalLettersString3 + "\n";
   ARE_EQUAL(expectedRandomCapitalLettersFileText, randomCapitalLettersFileText);
}

TEST(MakeFileText_GenerateRandomCharsIsFalse_ReturnsAllZerosStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
{
   const string fileText = ReplicateLineNTimesMock.ReturnRandom();
   const size_t numberOfLines = ZenUnit::RandomBetween<size_t>(0, 2);
   const size_t numberOfCharactersPerLine = ZenUnit::RandomBetween<size_t>(0, 2);
   //
   const string returnedFileText = _textFileLinesMaker.MakeFileText(numberOfLines, numberOfCharactersPerLine, false);
   //
   string expectedLineToWrite(numberOfCharactersPerLine + 1, '0');
   expectedLineToWrite[expectedLineToWrite.size() - 1] = '\n';
   METALMOCK(ReplicateLineNTimesMock.CalledOnceWith(expectedLineToWrite, numberOfLines));
   ARE_EQUAL(fileText, returnedFileText);
}

TEST3X3(ReplicateLineNTimes_ReturnsLineReplicatedNTimes,
   size_t n, const string& lineToWrite, const string& expectedReturnValue,
   0ull, "Line", "",
   1ull, "Line", "Line",
   2ull, "Line", "LineLine",
   3ull, "Line", "LineLineLine",
   0ull, "123", "",
   1ull, "123", "123",
   2ull, "123", "123123",
   3ull, "123", "123123123")
{
   const string lineReplicatedNTimes = TextFileLinesMaker::ReplicateLineNTimes(lineToWrite, n);
   ARE_EQUAL(expectedReturnValue, lineReplicatedNTimes);
}

RUN_TESTS(TextFileLinesMakerTests)
