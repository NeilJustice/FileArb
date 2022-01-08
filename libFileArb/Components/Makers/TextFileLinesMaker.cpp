#include "pch.h"
#include "libFileArb/Components/Makers/LineReplicator.h"
#include "libFileArb/Components/Makers/RandomStringMaker.h"
#include "libFileArb/Components/Makers/TextFileLinesMaker.h"

TextFileLinesMaker::TextFileLinesMaker()
   // Constant Components
   : _lineReplicator(make_unique<LineReplicator>())
   , _randomStringMaker(make_unique<RandomStringMaker>())
{
}

TextFileLinesMaker::~TextFileLinesMaker()
{
}

string TextFileLinesMaker::MakeFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const
{
   string allZerosLine(numberOfCharactersPerLine + 1, '0');
   allZerosLine[allZerosLine.size() - 1] = '\n';
   string allZerosFileText = _lineReplicator->ReplicateLineNTimes(allZerosLine, numberOfLines);
   return allZerosFileText;
}

string TextFileLinesMaker::MakeRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const
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

vector<string> TextFileLinesMaker::MakeRandomFileTexts(size_t /*totalNumberOfFiles*/, size_t /*numberOfLines*/, size_t /*numberOfCharactersPerLine*/) const
{
   vector<string> randomFileTexts;
   // _twoArgElementsGenerator_MakeRandomFileText->GenerateElement(
   //    totalNumberOfFiles, this, &TextFileLinesMaker::MakeRandomFileText, numberOfLines, numberOfCharactersPerLine);
   return randomFileTexts;
}
