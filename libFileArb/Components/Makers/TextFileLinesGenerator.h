#pragma once
class RandomStringMaker;

class TextFileLinesGenerator
{
   friend class TextFileLinesGeneratorTests;
private:
   // Function Pointers
   function<string(const string&, size_t)> _call_ReplicateLineNTimes;
   // Constant Components
   unique_ptr<const RandomStringMaker> _randomStringMaker;
   // Mutable Fields
   string _fileText;
public:
   TextFileLinesGenerator();
   virtual ~TextFileLinesGenerator();
   virtual string MakeFileText(size_t numberOfLines, size_t numberOfCharactersPerLine, bool generateRandomLetters) const;
private:
   static string ReplicateLineNTimes(const string& line, size_t n);
};
