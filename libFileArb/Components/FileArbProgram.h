#pragma once
namespace Utils
{
   class Console;
   template<typename ReturnType, typename ClassType, typename ArgumentType>
   class NonVoidOneArgTryCatchCaller;
   class Stopwatch;
   class VectorHelper;
}
class FileArbArgsParser;
class FileArbSubProgramFactory;
class FileCreator;

class FileArbProgram
{
private:
   friend class FileArbProgramTests;
   // Function Pointers
   function<string(const exception*)> _call_Utils_Exception_ClassNameAndMessage;
   // Function Callers
   using _nonVoidOneArgTryCatchCallerType = Utils::NonVoidOneArgTryCatchCaller<
      int,
      FileArbProgram,
      const vector<string>&>;
   unique_ptr<const _nonVoidOneArgTryCatchCallerType> _nonVoidOneArgTryCatchCaller;
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const FileArbArgsParser> _fileArbArgsParser;
   unique_ptr<const FileArbSubProgramFactory> _fileArbSubProgramFactory;
   unique_ptr<const Utils::VectorHelper> _vectorHelper;
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
