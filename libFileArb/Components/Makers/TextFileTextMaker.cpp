#include "pch.h"
#include "libFileArb/Components/Makers/LineReplicator.h"
#include "libFileArb/Components/Makers/RandomStringMaker.h"
#include "libFileArb/Components/Makers/TextFileTextMaker.h"

TextFileTextMaker::TextFileTextMaker()
   // Constant Components
   : _lineReplicator(make_unique<LineReplicator>())
   , _randomStringMaker(make_unique<RandomStringMaker>())
{
}

TextFileTextMaker::~TextFileTextMaker()
{
}

string TextFileTextMaker::MakeNonRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const
{
   string allZerosLine(numberOfCharactersPerLine + 1, '0');
   allZerosLine[allZerosLine.size() - 1] = '\n';
   string allZerosFileText = _lineReplicator->ReplicateLineNTimes(allZerosLine, numberOfLines);
   return allZerosFileText;
}

string TextFileTextMaker::MakeRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const
{
   ostringstream oss;
   for (size_t i = 0; i < numberOfLines; ++i)
   {
      string randomCapitalLettersString = _randomStringMaker->MakeRandomCapitalLettersString(numberOfCharactersPerLine);
      oss << randomCapitalLettersString << '\n';
   }
   string randomCapitalLettersFileText = oss.str();
   return randomCapitalLettersFileText;
}
