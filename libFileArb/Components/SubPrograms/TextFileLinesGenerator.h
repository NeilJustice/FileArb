#pragma once

class TextFileLinesGenerator
{
   friend class TextFileLinesGeneratorTests;
private:
   // Function Pointers
   function<string(const string&, size_t)> _call_ReplicateLineNTimes;
   // Mutable Fields
   string _fileText;
public:
   TextFileLinesGenerator();
   virtual ~TextFileLinesGenerator() = default;
   virtual string MakeFileText(size_t numberOfCharactersPerLine, size_t numberOfLinesPerFile) const;
private:
   static string ReplicateLineNTimes(const string& line, size_t n);
};
