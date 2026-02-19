#pragma once
class LineReplicator;
class RandomStringMaker;

class TextFileTextMaker
{
   friend class TextFileTextMakerTests;
private:
   // Constant Components
   unique_ptr<const LineReplicator> _lineReplicator;
   unique_ptr<const RandomStringMaker> _randomStringMaker;
   // Mutable Fields
   string _fileText;
public:
   TextFileTextMaker();
   virtual ~TextFileTextMaker();

   virtual string MakeNonRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const;
   virtual string MakeRandomFileText(size_t numberOfLines, size_t numberOfCharactersPerLine) const;
};
