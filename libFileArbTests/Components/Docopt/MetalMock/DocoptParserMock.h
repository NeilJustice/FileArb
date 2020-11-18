#pragma once
#include "libFileArb/Components/Docopt/DocoptParser.h"

class DocoptParserMock : public Metal::Mock<DocoptParser>
{
public:
   using DocoptMapType = map<string, docopt::Value>;
   METALMOCK_NONVOID2_CONST(DocoptMapType, ParseArgs, const string&, const vector<string>&)
   METALMOCK_NONVOID2_CONST(string, GetRequiredString, const DocoptMapType&, const string&)
   METALMOCK_NONVOID2_CONST(unsigned, GetRequiredUnsigned, const DocoptMapType&, const string&)
   METALMOCK_NONVOID2_CONST(bool, GetRequiredBool, const DocoptMapType&, const string&)
   METALMOCK_NONVOID2_CONST(bool, GetOptionalBool, const DocoptMapType&, const string&)
   METALMOCK_NONVOID2_CONST(string, GetOptionalString, const DocoptMapType&, const string&)
   METALMOCK_NONVOID4_CONST(size_t, GetProgramModeSpecificRequiredSizeT, const DocoptMapType&, const string&, int, const vector<int>&)
};
