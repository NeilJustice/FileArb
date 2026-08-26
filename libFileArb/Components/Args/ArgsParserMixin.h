#pragma once
class DocoptParser;

class ArgsParserMixin
{
   friend class ArgsParserMixinTests;
protected:
   // Base Constant Components
   unique_ptr<const DocoptParser> p_docoptParser;
public:
   ArgsParserMixin();
   virtual ~ArgsParserMixin();
};
