#include "pch.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
#include "libFileArb/Utilities/DataStructure/Map.h"
#include "libFileArb/Utilities/DataStructure/Vector.h"

namespace Utils
{
   DocoptParser::DocoptParser()
      : _call_docopt_docopt(docopt::docopt)
      , _call_StaticGetRequiredUnsigned(StaticGetRequiredUnsigned)
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
      const map<string, docopt::Value> argPairs = _call_docopt_docopt(usage, argvWithoutFirstArgument, true, "", false);
      return argPairs;
   }

   string DocoptParser::GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
   {
      const docopt::Value docoptValue = Map::At(docoptArgs, argName);
      const string& stringArg = docoptValue.AsString();
      return stringArg;
   }

   unsigned DocoptParser::GetRequiredUnsigned(const map<string, docopt::Value>& docoptArgs, const string& argName) const
   {
      return StaticGetRequiredUnsigned(docoptArgs, argName);
   }

   unsigned DocoptParser::StaticGetRequiredUnsigned(const map<string, docopt::Value>& docoptArgs, const string& argName)
   {
      const docopt::Value docoptValue = Map::At(docoptArgs, argName);
      const size_t docoptValueHash = docoptValue.Hash();
      const size_t kindEmptyHashValue = std::hash<void*>()(nullptr);
      if (docoptValueHash == kindEmptyHashValue)
      {
         const string exceptionMessage = "For argument [" + argName + "], a required unsigned value was not specified";
         throw invalid_argument(exceptionMessage);
      }
      const long longValue = docoptValue.AsLong();
      if (longValue < 0)
      {
         const string exceptionMessage = "For argument [" + argName + "], invalid negative value: " + to_string(longValue);
         throw invalid_argument(exceptionMessage);
      }
      const unsigned unsignedValue = static_cast<unsigned>(longValue);
      return unsignedValue;
   }

   bool DocoptParser::GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
   {
      const docopt::Value docoptValue = Map::At(docoptArgs, argName);
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
         const unsigned argumentValueAsUnsigned = _call_StaticGetRequiredUnsigned(docoptArgs, argumentName);
         const size_t argumentValueAsSizeT = static_cast<size_t>(argumentValueAsUnsigned);
         return argumentValueAsSizeT;
      }
      return 0;
   }
}
