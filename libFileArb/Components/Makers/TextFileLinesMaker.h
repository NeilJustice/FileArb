#pragma once
namespace Utils
{
   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class TwoArgElementsGenerator;
}
class LineReplicator;
class RandomStringMaker;

class TextFileLinesMaker
{
   friend class TextFileLinesMakerTests;
private:
   // Function Callers
   using _twoArgElementsGenerator_MakeRandomFileTextType = Utils::TwoArgElementsGenerator<string, TextFileLinesMaker, size_t, size_t>;
   unique_ptr<const _twoArgElementsGenerator_MakeRandomFileTextType> _twoArgElementsGenerator_MakeRandomFileText;
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
   virtual vector<string> MakeRandomFileTexts(size_t totalNumberOfFiles, size_t numberOfLines, size_t numberOfCharactersPerLine) const;
};
