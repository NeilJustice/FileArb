#include "pch.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/Exception/TryCatchCaller.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"
#include "libFileArb/Components/FileArb/FileArbProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/Components/Time/Stopwatch.h"

FileArbProgram::FileArbProgram()
   // Function Callers
   : _call_Utils_Exception_ClassNameAndMessage(Exception::GetClassNameAndMessage)
   , _call_Utils_Vector_FromArgcArgv(Vector::FromArgcArgv)
   // Constant Components
   , _console(make_unique<Console>())
   , _tryCatchCaller(make_unique<TryCatchCaller<FileArbProgram, const vector<string>&>>())
   , _argsParser(make_unique<FileArbArgsParser>())
   , _fileArbSubProgramFactory(make_unique<FileArbSubProgramFactory>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
   , _stopwatch(make_unique<Stopwatch>())
{
}

FileArbProgram::~FileArbProgram()
{
}

int FileArbProgram::Main(int argc, char* argv[])
{
   if (argc == 1)
   {
      _console->WriteLine(FileArbArgs::CommandLineUsage);
      return 0;
   }
   _stopwatch->Start();
   const vector<string> stringArgs = _call_Utils_Vector_FromArgcArgv(argc, argv);
   const int exitCode = _tryCatchCaller->TryCatchCall(
      this, &FileArbProgram::Run, stringArgs, &FileArbProgram::ExceptionHandler);
   const string runtimeInSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string durationLine = "[FileArb] Duration: " + runtimeInSeconds + " seconds";
   _console->WriteLine(durationLine);
   const string exitCodeLine = "[FileArb] ExitCode: " + to_string(exitCode);
   _console->WriteLine(exitCodeLine);
   return exitCode;
}

int FileArbProgram::Run(const vector<string>& stringArgs)
{
   const FileArbArgs args = _argsParser->ParseArgs(stringArgs);
   _argsParser->PrintPreamble(args);
   const shared_ptr<FileArbSubProgram> fileArbSubProgram = _fileArbSubProgramFactory->NewFileArbSubProgram(args.programMode);
   const int exitCode = fileArbSubProgram->Run(args);
   return exitCode;
}

int FileArbProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/)
{
   const string exceptionTypeNameAndWhat = _call_Utils_Exception_ClassNameAndMessage(&ex);
   const string exceptionErrorMessage = "[FileArb] Error: Exception thrown: " + exceptionTypeNameAndWhat;
   _console->WriteLine(exceptionErrorMessage);
   return 1;
}
