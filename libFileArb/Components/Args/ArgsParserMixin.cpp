#include "pch.h"
#include "libFileArb/Components/Args/ArgsParserMixin.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"

ArgsParserMixin::ArgsParserMixin()
   // Base Constant Components
   : p_docoptParser(make_unique<DocoptParser>())
{
}

ArgsParserMixin::~ArgsParserMixin()
{
}
