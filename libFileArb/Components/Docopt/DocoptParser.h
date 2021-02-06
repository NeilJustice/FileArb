#pragma once
#include "libFileArb/Components/Docopt/docopt.h"
class DocoptParserTests;

class DocoptParser
{
   friend class ::DocoptParserTests;
private:
   // Function Pointers
   function<map<string, docopt::Value>(string, const vector<string>&, bool help, string, bool)> _call_docopt_docopt;
   function<size_t(const map<string, docopt::Value>&, const string&)> _call_StaticGetRequiredSizeT;
public:
   DocoptParser();
   virtual ~DocoptParser() = default;

   virtual map<string, docopt::Value> ParseArgs(const string& commandLineUsage, const vector<string>& argv) const;

   virtual bool GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual bool GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;

   virtual string GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual string GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual string GetProgramModeSpecificRequiredString(
      const map<string, docopt::Value>& docoptArgs,
      const string& argName,
      int fieldIsRequiredIfProgramModeIntEqualsThisValue,
      int programModeAsInt) const;

   virtual size_t GetProgramModeSpecificRequiredSizeT(
      const map<string, docopt::Value>& docoptArgs,
      const string& argumentName,
      int programMode,
      const vector<int>& programModesThatRequiresArgument) const;
   virtual size_t GetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
private:
   static size_t StaticGetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName);
};
