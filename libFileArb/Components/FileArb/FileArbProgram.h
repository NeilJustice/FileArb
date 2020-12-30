#pragma once
#include <functional>
#if defined __linux__ || defined __APPLE__
#include <memory>
#endif
class Console;
class Stopwatch;
template<typename ClassType, typename ArgumentType>
class TryCatchCaller;
class FileArbArgsParser;
class FileArbSubProgramFactory;
class FileCreator;

class FileArbProgram
{
   friend class FileArbProgramTests;
private:
   // Function Callers
   std::function<std::string(const std::exception*)> _call_Utils_Exception_ClassNameAndMessage;
   std::function<std::vector<std::string>(int, char**)> _call_Utils_Vector_FromArgcArgv;
   // Constant Components
   std::unique_ptr<const Console> _console;
   std::unique_ptr<const TryCatchCaller<FileArbProgram, const std::vector<std::string>&>> _tryCatchCaller;
   std::unique_ptr<const FileArbArgsParser> _argsParser;
   std::unique_ptr<const FileArbSubProgramFactory> _fileArbSubProgramFactory;
   // Mutable Components
   std::unique_ptr<FileCreator> _fileCreator;
   std::unique_ptr<Stopwatch> _stopwatch;
public:
   FileArbProgram();
   virtual ~FileArbProgram();
   int Main(int argc, char* argv[]);
private:
   int Run(const std::vector<std::string>& stringArgs);
   int ExceptionHandler(const std::exception& ex, const std::vector<std::string>& stringArgs);
};
