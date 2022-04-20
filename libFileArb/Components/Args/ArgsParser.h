#pragma once
namespace Utils
{
   class Console;
   class DocoptParser;
   class FileSystem;
}
class BytesStringConverter;
class CreateBinaryFileArgsParser;
class CreateBinaryFilesArgsParser;
class CreateTextFileArgsParser;
class CreateTextFilesArgsParser;

class ProgramModeDeterminer;

class ArgsParser
{
private:
   friend class ArgsParserTests;
   // Function Pointers
   function<ProgramMode(bool, bool, bool, bool)> _call_DetermineProgramMode;
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const CreateBinaryFileArgsParser> _createBinaryFileArgsParser;
   unique_ptr<const CreateTextFileArgsParser> _createTextFileArgsParser;
   unique_ptr<const CreateBinaryFilesArgsParser> _createBinaryFilesArgsParser;
   unique_ptr<const CreateTextFilesArgsParser> _createTextFilesArgsParser;
   unique_ptr<const Utils::DocoptParser> _docoptParser;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
public:
   ArgsParser();
   virtual ~ArgsParser();
   virtual FileArbArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
