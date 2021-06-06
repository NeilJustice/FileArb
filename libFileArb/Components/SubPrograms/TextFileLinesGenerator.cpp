#include "pch.h"
#include "libFileArb/Components/Random/RandomStringMaker.h"
#include "libFileArb/Components/SubPrograms/TextFileLinesGenerator.h"

TextFileLinesGenerator::TextFileLinesGenerator()
   // Function Pointers
   : _call_ReplicateLineNTimes(ReplicateLineNTimes)
   // Constant Components
   , _randomStringMaker(make_unique<RandomStringMaker>())
{
}

TextFileLinesGenerator::~TextFileLinesGenerator()
{
}

string TextFileLinesGenerator::MakeFileText(size_t numberOfLines, size_t numberOfCharactersPerLine, bool generateRandomLetters) const
{
   if (generateRandomLetters)
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
   string allZerosLine(numberOfCharactersPerLine + 1, '0');
   allZerosLine[allZerosLine.size() - 1] = '\n';
   string allZerosFileText = _call_ReplicateLineNTimes(allZerosLine, numberOfLines);
   return allZerosFileText;
}

string TextFileLinesGenerator::ReplicateLineNTimes(const string& line, size_t n)
{
   const size_t replicatedStringLength = line.size() * n;
   const size_t lineSize = line.size();
   string lineReplicatedNTimes(replicatedStringLength, 0);
   for (size_t i = 0; i < n; ++i)
   {
      const size_t stringOffset = i * lineSize;
      memcpy(const_cast<char*>(lineReplicatedNTimes.c_str()) + stringOffset, line.c_str(), lineSize);
   }
   return lineReplicatedNTimes;
}
