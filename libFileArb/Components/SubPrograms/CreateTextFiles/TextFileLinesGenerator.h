#pragma once

class TextFileLinesGenerator
{
private:
   friend class TextFileLinesGeneratorTests;
   function<string(const string&, size_t)> _call_ReplicateLineNTimes;
   string _fileText;

public:
   TextFileLinesGenerator();
   virtual ~TextFileLinesGenerator() = default;
   virtual string MakeFileText(size_t numberOfCharactersPerLine, size_t numberOfLinesPerFile) const;

private:
   static string ReplicateLineNTimes(const string& line, size_t n);
};
