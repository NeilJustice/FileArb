#pragma once
namespace Utils
{
   class Console;
   class FileSystem;
   class PreamblePrinter;
   class VectorHelper;
}
class BytesStringConverter;
class CreateBinaryFileArgsParser;
class CreateBinaryFilesArgsParser;
class CreateTextFileArgsParser;
class CreateTextFilesArgsParser;
class DocoptParser;
class ProgramModeDeterminer;
struct FileArbArgs;

class ArgsParser
{
private:
   friend class ArgsParserTests;
   // Function Pointers
   function<void(int)> _call_exit;
   // Constant Components
   unique_ptr<const BytesStringConverter> _bytesStringConverter;
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const CreateBinaryFileArgsParser> _createBinaryFileArgsParser;
   unique_ptr<const CreateTextFileArgsParser> _createTextFileArgsParser;
   unique_ptr<const CreateBinaryFilesArgsParser> _createBinaryFilesArgsParser;
   unique_ptr<const CreateTextFilesArgsParser> _createTextFilesArgsParser;
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const Utils::PreamblePrinter> _preamblePrinter;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
   unique_ptr<const Utils::VectorHelper> _vectorHelper;
public:
   ArgsParser();
   virtual ~ArgsParser();

   virtual FileArbArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
