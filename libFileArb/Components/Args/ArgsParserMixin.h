#pragma once
class BytesStringConverter;
class DocoptParser;

class ArgsParserMixin
{
   friend class ArgsParserMixinTests;
protected:
   // Base Constant Components
   unique_ptr<const BytesStringConverter> p_bytesStringConverter;
   unique_ptr<const DocoptParser> p_docoptParser;
public:
   ArgsParserMixin();
   virtual ~ArgsParserMixin();
};
