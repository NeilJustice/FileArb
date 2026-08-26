#include "pch.h"
#include "libFileArb/Components/Args/ArgsParserMixin.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"

ArgsParserMixin::ArgsParserMixin()
   // Base Constant Components
   : p_bytesStringConverter(make_unique<BytesStringConverter>())
   , p_docoptParser(make_unique<DocoptParser>())
{
}

ArgsParserMixin::~ArgsParserMixin()
{
}
