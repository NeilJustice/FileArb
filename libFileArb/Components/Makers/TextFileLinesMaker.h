#pragma once
class LineReplicator;
class RandomStringMaker;

class TextFileLinesMaker
{
   friend class TextFileLinesMakerTests;
private:
   // Constant Components
   unique_ptr<const LineReplicator> _lineReplicator;
   unique_ptr<const RandomStringMaker> _randomStringMaker;
   // Mutable Fields
   string _fileText;
public:
   TextFileLinesMaker();
   virtual ~TextFileLinesMaker();
   virtual string MakeFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const;
   virtual string MakeRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const;
   virtual vector<string> MakeRandomFileTexts(size_t numberOfLines, size_t numberOfCharactersPerLine) const;
};
