#include "pch.h"
#include "libFileArb/Components/SubPrograms/TextFileLinesGenerator.h"

TextFileLinesGenerator::TextFileLinesGenerator()
   // Function Pointers
   : _call_ReplicateLineNTimes(ReplicateLineNTimes)
{
}

string TextFileLinesGenerator::MakeFileText(size_t numberOfCharactersPerLine, size_t numberOfLinesPerFile, bool generateRandomChars) const
{
   if (generateRandomChars)
   {
      return string();
   }
   else
   {
      string allZerosLine(numberOfCharactersPerLine + 1, '0');
      allZerosLine[allZerosLine.size() - 1] = '\n';
      string allZerosFileText = _call_ReplicateLineNTimes(allZerosLine, numberOfLinesPerFile);
      return allZerosFileText;
   }
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
