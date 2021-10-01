#pragma once
class RandomStringMaker;

class TextFileLinesMaker
{
   friend class TextFileLinesMakerTests;
private:
   // Function Pointers
   function<string(const string&, size_t)> _call_ReplicateLineNTimes;
   // Constant Components
   unique_ptr<const RandomStringMaker> _randomStringMaker;
   // Mutable Fields
   string _fileText;
public:
   TextFileLinesMaker();
   virtual ~TextFileLinesMaker();
   virtual string MakeFileText(size_t numberOfLines, size_t numberOfCharactersPerLine, bool generateRandomLetters) const;
private:
   static string ReplicateLineNTimes(const string& line, size_t n);
};
