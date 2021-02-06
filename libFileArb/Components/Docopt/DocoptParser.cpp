#include "pch.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"

DocoptParser::DocoptParser()
   // Function Pointers
   : _call_docopt_docopt(docopt::docopt)
   , _call_StaticGetRequiredSizeT(StaticGetRequiredSizeT)
{
}

map<string, docopt::Value> DocoptParser::ParseArgs(const string& commandLineUsage, const vector<string>& argv) const
{
   if (argv.empty())
   {
      throw invalid_argument("argv cannot be empty");
   }
   const vector<string> argvWithoutFirstArgument(argv.data() + 1, argv.data() + argv.size());
   map<string, docopt::Value> argPairs = _call_docopt_docopt(commandLineUsage, argvWithoutFirstArgument, true, "", false);
   return argPairs;
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

bool DocoptParser::GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const docopt::Value docoptValue = Map::At(docoptArgs, argName);
   const bool boolValue = docoptValue.AsBool();
   return boolValue;
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

string DocoptParser::GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const docopt::Value docoptValue = Map::At(docoptArgs, argName);
   const string& stringArg = docoptValue.AsString();
   return stringArg;
}

string DocoptParser::GetProgramModeSpecificRequiredString(
   const map<string, docopt::Value>& docoptArgs,
   const string& argName,
   int fieldIsRequiredIfProgramModeIntEqualsThisValue,
   int programModeAsInt) const
{
   if (programModeAsInt == fieldIsRequiredIfProgramModeIntEqualsThisValue)
   {
      const docopt::Value docoptValue = Map::At(docoptArgs, argName);
      const string& stringValue = docoptValue.AsString();
      return stringValue;
   }
   return string();
}

size_t DocoptParser::GetProgramModeSpecificRequiredSizeT(
   const map<string, docopt::Value>& docoptArgs,
   const string& argumentName,
   int programMode,
   const vector<int>& programModesThatRequiresArgument) const
{
   const bool programModeIsContainedInProgramModesThatRequiresArgument =
      Vector::Contains(programModesThatRequiresArgument, programMode);
   if (programModeIsContainedInProgramModesThatRequiresArgument)
   {
      const size_t sizeTArgumentValue = _call_StaticGetRequiredSizeT(docoptArgs, argumentName);
      return sizeTArgumentValue;
   }
   return 0;
}

size_t DocoptParser::GetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const size_t requiredSizeTValue = StaticGetRequiredSizeT(docoptArgs, argName);
   return requiredSizeTValue;
}

// Private Functions

size_t DocoptParser::StaticGetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName)
{
   const docopt::Value docoptValue = Map::At(docoptArgs, argName);
   const size_t docoptValueHash = docoptValue.Hash();
   const size_t kindEmptyHashValue = std::hash<void*>()(nullptr);
   if (docoptValueHash == kindEmptyHashValue)
   {
      const string exceptionMessage = String::Concat("For argument [", argName, "], a required size_t value was not specified");
      throw invalid_argument(exceptionMessage);
   }
   const size_t sizeTValue = docoptValue.AsSizeT();
   return sizeTValue;
}
