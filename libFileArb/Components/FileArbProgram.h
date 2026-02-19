#pragma once
namespace Utils
{
   class Console;
   template<typename ReturnType, typename ClassType, typename ArgumentType>
   class NonVoidOneArgTryCatchCaller;
   class Stopwatch;
}
class ArgsParser;
class FileArbSubProgramFactory;
class FileCreator;

class FileArbProgram
{
private:
   friend class FileArbProgramTests;
   // Function Pointers
   function<string(const exception*)> _call_Utils_Exception_ClassNameAndMessage;
   function<vector<string>(int, char**)> _call_Utils_Vector_FromArgcArgv;
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::NonVoidOneArgTryCatchCaller<int, FileArbProgram, const vector<string>&>> _nonVoidOneArgTryCatchCaller;
   unique_ptr<const ArgsParser> _argsParser;
   unique_ptr<const FileArbSubProgramFactory> _fileArbSubProgramFactory;
   // Mutable Components
   unique_ptr<FileCreator> _fileCreator;
   unique_ptr<Utils::Stopwatch> _stopwatch;
public:
   FileArbProgram();
   virtual ~FileArbProgram();

   int Main(int argc, char* argv[]);
private:
   int Run(const vector<string>& stringArgs);
   int ExceptionHandler(const exception& ex, const vector<string>& stringArgs);
};
