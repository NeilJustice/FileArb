#pragma once
namespace docopt
{
   struct value;
}
class Console;
class DocoptParser;

class FileArbArgsParser
{
private:
   friend class FileArbArgsParserTests;
   // Function Pointers
   function<ProgramMode(bool, bool)> _call_DetermineProgramMode;
   function<string(bool, bool)> _call_DetermineFileExtension;
   // Constant Components
   unique_ptr<const Console> _console;
   unique_ptr<const DocoptParser> _docoptParser;
public:
   FileArbArgsParser();
   virtual ~FileArbArgsParser();
   virtual FileArbArgs ParseArgs(const vector<string>& stringArgs) const;
private:
   static ProgramMode DetermineProgramMode(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode);
   static string DetermineFileExtension(bool isCreateTextFilesMode, bool isCreateBinaryFilesMode);
};
