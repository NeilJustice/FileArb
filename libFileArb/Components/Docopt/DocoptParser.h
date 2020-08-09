#pragma once
#include "libFileArb/Components/Docopt/docopt.h"
class DocoptParserTests;

namespace Utils
{
   class DocoptParser
   {
      friend class ::DocoptParserTests;
   private:
      function<map<string, docopt::Value>(string, const vector<string>&, bool help, string, bool)> _call_docopt_docopt;
      function<unsigned(const map<string, docopt::Value>&, const string&)> _call_StaticGetRequiredUnsigned;
   public:
      DocoptParser();
      virtual ~DocoptParser();
      virtual map<string, docopt::Value> ParseArgs(const string& usage, const vector<string>& argv) const;
      virtual string GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual unsigned GetRequiredUnsigned(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual bool GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual bool GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual string GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual size_t GetProgramModeSpecificRequiredSizeT(
         const map<string, docopt::Value>& docoptArgs,
         const string& argumentName,
         int programMode,
         const vector<int>& programModesThatRequiresArgument) const;
   private:
      static unsigned StaticGetRequiredUnsigned(const map<string, docopt::Value>& docoptArgs, const string& argName);
   };
}
