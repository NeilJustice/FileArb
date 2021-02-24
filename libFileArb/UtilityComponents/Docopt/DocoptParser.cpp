#include "pch.h"
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"
#include "libFileArb/StaticUtilities/Map.h"
#include "libFileArb/StaticUtilities/Vector.h"

DocoptParser::DocoptParser()
   // Function Pointers
   : _call_docopt(docopt::docopt)
   , _call_StaticGetRequiredSizeT(StaticGetRequiredSizeT)
   , _call_StaticGetRequiredString(StaticGetRequiredString)
{
}

DocoptParser::~DocoptParser()
{
}

map<string, docopt::Value> DocoptParser::ParseArgs(const string& usage, const vector<string>& argv) const
{
   if (argv.empty())
   {
      throw invalid_argument("argv cannot be empty");
   }
   const vector<string> argvWithoutFirstArgument(argv.data() + 1, argv.data() + argv.size());
   map<string, docopt::Value> argPairs = _call_docopt(usage, argvWithoutFirstArgument, true, "", false);
   return argPairs;
}

bool DocoptParser::GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const docopt::Value& docoptValue = Map::At(docoptArgs, argName);
   const bool boolValue = docoptValue.AsBool();
   return boolValue;
}

bool DocoptParser::GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const pair<bool, docopt::Value> didGetDocoptValueAndDocoptValue = Map::TryGetValue(docoptArgs, argName);
   if (!didGetDocoptValueAndDocoptValue.first)
   {
      return false;
   }
   const bool boolValue = didGetDocoptValueAndDocoptValue.second.AsBool();
   return boolValue;
}

string DocoptParser::GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   string stringValue = StaticGetRequiredString(docoptArgs, argName);
   return stringValue;
}

string DocoptParser::GetProgramModeSpecificRequiredString(
   const map<string, docopt::Value>& docoptArgs,
   const string& argName,
   int programMode,
   const vector<int>& programModesThatRequiresArgument) const
{
   const bool programModeIsContainedInProgramModesThatRequiresArgument = Vector::Contains(programModesThatRequiresArgument, programMode);
   if (programModeIsContainedInProgramModesThatRequiresArgument)
   {
      string stringValue = _call_StaticGetRequiredString(docoptArgs, argName);
      return stringValue;
   }
   return ""s;
}

string DocoptParser::GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const pair<bool, docopt::Value> didGetDocoptValueAndDocoptValue = Map::TryGetValue(docoptArgs, argName);
   if (!didGetDocoptValueAndDocoptValue.first)
   {
      return string();
   }
   const string& optionalStringValue = didGetDocoptValueAndDocoptValue.second.AsString();
   return optionalStringValue;
}

size_t DocoptParser::GetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const size_t sizeTValue = _call_StaticGetRequiredSizeT(docoptArgs, argName);
   return sizeTValue;
}

size_t DocoptParser::GetProgramModeSpecificRequiredSizeT(
   const map<string, docopt::Value>& docoptArgs,
   const string& argName,
   int programMode,
   const vector<int>& programModesThatRequiresArgument) const
{
   const bool programModeIsContainedInProgramModesThatRequiresArgument = Vector::Contains(programModesThatRequiresArgument, programMode);
   if (programModeIsContainedInProgramModesThatRequiresArgument)
   {
      const size_t sizeTValue = _call_StaticGetRequiredSizeT(docoptArgs, argName);
      return sizeTValue;
   }
   return 0;
}

// Private Functions

size_t DocoptParser::StaticGetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName)
{
   const docopt::Value& docoptValue = Map::At(docoptArgs, argName);
   const size_t sizeTValue = docoptValue.AsSizeT();
   return sizeTValue;
}

string DocoptParser::StaticGetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName)
{
   const docopt::Value& docoptValue = Map::At(docoptArgs, argName);
   if (docoptValue.IsString())
   {
      const string& stringArg = docoptValue.AsString();
      return stringArg;
   }
   throw invalid_argument("arg in map as a non-string: " + argName);
}
