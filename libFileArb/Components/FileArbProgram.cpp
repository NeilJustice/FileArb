#include "pch.h"
#include "libFileArb/Components/Args/FileArbArgsParser.h"
#include "libFileArb/Components/FileArbProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArb/UtilityComponents/Console/Console.h"
#include "libFileArb/UtilityComponents/FunctionCallers/TryCatchCallers/NonVoidOneArgTryCatchCaller.h"
#include "libFileArb/UtilityComponents/Time/Stopwatch.h"

FileArbProgram::FileArbProgram()
   // Function Pointers
   : _call_Utils_Exception_ClassNameAndMessage(Exception::GetClassNameAndMessage)
   , _call_Utils_Vector_FromArgcArgv(Vector::FromArgcArgv)
   // Constant Components
   , _console(make_unique<Utils::Console>())
   , _nonVoidOneArgTryCatchCaller(make_unique<NonVoidOneArgTryCatchCaller<int, FileArbProgram, const vector<string>&>>())
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
      _console->NakedWriteLine(FileArbArgs::CommandLineUsage);
      return 0;
   }
   _stopwatch->Start();
   const vector<string> stringArgs = _call_Utils_Vector_FromArgcArgv(argc, argv);
   const int subProgramExitCode = _nonVoidOneArgTryCatchCaller->TryCatchCallNonConstMemberFunction(
      this, &FileArbProgram::Run, stringArgs, &FileArbProgram::ExceptionHandler);
   const string runtimeInSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string durationLine = String::ConcatStrings("Duration: ", runtimeInSeconds, " seconds");
   _console->ThreadIdWriteLine(durationLine);
   const string exitCodeLine = String::ConcatValues("ExitCode: ", subProgramExitCode);
   _console->ThreadIdWriteLine(exitCodeLine);
   return subProgramExitCode;
}

int FileArbProgram::Run(const vector<string>& stringArgs)
{
   const FileArbArgs args = _argsParser->ParseArgs(stringArgs);
   const string runningMessage = "Running: " + args.commandLine;
   _console->ThreadIdWriteLine(runningMessage);
   const shared_ptr<FileArbSubProgram> fileArbSubProgram = _fileArbSubProgramFactory->NewFileArbSubProgram(args.programMode);
   const int exitCode = fileArbSubProgram->Run(args);
   return exitCode;
}

int FileArbProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/)
{
   const string exceptionTypeNameAndWhat = _call_Utils_Exception_ClassNameAndMessage(&ex);
   const string exceptionErrorMessage = "Error: Exception thrown: " + exceptionTypeNameAndWhat;
   _console->ThreadIdWriteLineColor(exceptionErrorMessage, Color::Red);
   return 1;
}
