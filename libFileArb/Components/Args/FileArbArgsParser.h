#pragma once
namespace docopt
{
   struct value;
}
class BytesStringConverter;
class Console;
class DocoptParser;

class FileArbArgsParser
{
private:
   friend class FileArbArgsParserTests;
   // Function Pointers
   function<ProgramMode(bool, bool, bool, bool)> _call_DetermineProgramMode;
   function<pair<string, string>(bool, bool, bool, bool)> _call_GetFileNamePrefixAndFileExtension;
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const Console> _console;
   unique_ptr<const DocoptParser> _docoptParser;
public:
   FileArbArgsParser();
   virtual ~FileArbArgsParser();
   virtual FileArbArgs ParseArgs(const vector<string>& stringArgs) const;
private:
   static ProgramMode DetermineProgramMode(
      bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode);
   static pair<string, string> GetFileNamePrefixAndFileExtension(
      bool isCreateTextFileMode, bool isCreateTextFilesMode, bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode);
};
