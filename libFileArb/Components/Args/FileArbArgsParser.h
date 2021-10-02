#pragma once
class BytesStringConverter;
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
   unique_ptr<const DocoptParser> _docoptParser;
public:
   FileArbArgsParser();
   virtual ~FileArbArgsParser();
   virtual FileArbArgs ParseArgs(const vector<string>& stringArgs) const;
private:
   static ProgramMode DetermineProgramMode(
      bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, bool isCreateTextFileMode, bool isCreateTextFilesMode);
   static pair<string, string> GetFileNamePrefixAndFileExtension(
      bool isCreateBinaryFileMode, bool isCreateBinaryFilesMode, bool isCreateTextFileMode, bool isCreateTextFilesMode);
};
