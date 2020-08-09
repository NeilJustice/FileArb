#pragma once
#include "libFileArb/ValueTypes/FileArbArgs.h"
namespace docopt
{
   struct value;
}
namespace Utils
{
   class Console;
   class DocoptParser;
}

class FileArbArgsParser
{
   friend class FileArbArgsParserTests;
private:
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::DocoptParser> _docoptParser;
   function<ProgramMode(bool, bool)> _call_DetermineProgramMode;
   function<string(bool, bool)> _call_DetermineFileExtension;
public:
   FileArbArgsParser();
   virtual ~FileArbArgsParser();
   virtual FileArbArgs ParseArgs(const vector<string>& stringArgs) const;
   virtual void PrintPreamble(const FileArbArgs& args) const;
private:
   static ProgramMode DetermineProgramMode(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode);
   static string DetermineFileExtension(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode);
};
