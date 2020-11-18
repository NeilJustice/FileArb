#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/TextFileLinesGenerator.h"

TESTS(TextFileLinesGeneratorTests)
AFACT(DefaultConstructor_SetsReplicateLineNTimesFunction)
AFACT(MakeFileText_ReturnsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
FACTS(ReplicateLineNTimes_ReturnsLineReplicatedNTimes)
EVIDENCE

TextFileLinesGenerator _textFileLinesGenerator;
METALMOCK_NONVOID2_STATIC(string, FileTextGenerator, ReplicateLineNTimes, const string&, size_t);

STARTUP
{
   _textFileLinesGenerator._call_ReplicateLineNTimes = BIND_2ARG_METALMOCK_OBJECT(ReplicateLineNTimesMock);
}

TEST(DefaultConstructor_SetsReplicateLineNTimesFunction)
{
   const TextFileLinesGenerator textFileLinesGenerator;
   STD_FUNCTION_TARGETS(TextFileLinesGenerator::ReplicateLineNTimes, textFileLinesGenerator._call_ReplicateLineNTimes);
}

TEST(MakeFileText_ReturnsStringWithNumberOfCharactersPerLineReplicatedNumberOfLinesTimes)
{
   const string fileText = ReplicateLineNTimesMock.ReturnRandom();
   const size_t numberOfCharactersPerLine = ZenUnit::RandomBetween<size_t>(0, 2);
   const size_t numberOfLinesPerFile = ZenUnit::RandomBetween<size_t>(0, 2);
   //
   const string returnedFileText = _textFileLinesGenerator.MakeFileText(numberOfCharactersPerLine, numberOfLinesPerFile);
   //
   string expectedLineToWrite(numberOfCharactersPerLine + 1, '0');
   expectedLineToWrite[expectedLineToWrite.size() - 1] = '\n';
   METALMOCK(ReplicateLineNTimesMock.CalledOnceWith(expectedLineToWrite, numberOfLinesPerFile));
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
   const string lineReplicatedNTimes = TextFileLinesGenerator::ReplicateLineNTimes(lineToWrite, n);
   ARE_EQUAL(expectedReturnValue, lineReplicatedNTimes);
}

RUN_TESTS(TextFileLinesGeneratorTests)
