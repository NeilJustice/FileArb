#pragma once
#include "libFileArb/UtilityComponents/Docopt/docopt.h"
class DocoptParserTests;

namespace Utils
{
   class DocoptParser
   {
      friend class ::DocoptParserTests;
   private:
      // Function Pointers
      function<map<string, docopt::Value>(string, const vector<string>&, bool help, string, bool)> _call_docopt;
      function<size_t(const map<string, docopt::Value>&, const string&)> _call_StaticGetRequiredSizeT;
      function<string(const map<string, docopt::Value>&, const string&)> _call_StaticGetRequiredString;
   public:
      DocoptParser();
      DocoptParser(const DocoptParser&) = delete;
      virtual ~DocoptParser();
      virtual map<string, docopt::Value> ParseArgs(const string& usage, const vector<string>& argv) const;

      virtual bool GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual bool GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;

      virtual string GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual string GetProgramModeSpecificRequiredString(
         const map<string, docopt::Value>& docoptArgs,
         const string& argName,
         int programMode,
         const vector<int>& programModesThatRequiresArgument) const;
      virtual string GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;

      virtual size_t GetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
      virtual size_t GetProgramModeSpecificRequiredSizeT(
         const map<string, docopt::Value>& docoptArgs,
         const string& argName,
         int programMode,
         const vector<int>& programModesThatRequiresArgument) const;
   private:
      static size_t StaticGetRequiredSizeT(const map<string, docopt::Value>& docoptArgs, const string& argName);
      static string StaticGetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName);
   };
}
