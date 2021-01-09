#include "pch.h"
#include "libFileArb/Components/SubPrograms/CreateTextFiles/TextFileLinesGenerator.h"

TextFileLinesGenerator::TextFileLinesGenerator()
   : _call_ReplicateLineNTimes(ReplicateLineNTimes)
{
}

string TextFileLinesGenerator::MakeFileText(size_t numberOfCharactersPerLine, size_t numberOfLinesPerFile) const
{
   string lineToWrite(numberOfCharactersPerLine + 1, '0');
   lineToWrite[lineToWrite.size() - 1] = '\n';
   string fileText = _call_ReplicateLineNTimes(lineToWrite, numberOfLinesPerFile);
   return fileText;
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
