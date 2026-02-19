#include "pch.h"
#include "libFileArb/Components/Args/ArgsParser.h"
#include "libFileArb/Components/FileArbProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/StaticUtilities/Exception.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArb/Components/Console/Console.h"
#include "libFileArb/Components/FunctionCallers/TryCatchCallers/NonVoidOneArgTryCatchCaller.h"
#include "libFileArb/Components/Time/Stopwatch.h"

FileArbProgram::FileArbProgram()
   // Function Pointers
   : _call_Utils_Exception_ClassNameAndMessage(Utils::Exception::GetClassNameAndMessage)
   , _call_Utils_Vector_FromArgcArgv(Utils::Vector::FromArgcArgv)
   // Constant Components
   , _console(make_unique<Utils::Console>())
   , _nonVoidOneArgTryCatchCaller(make_unique<Utils::NonVoidOneArgTryCatchCaller<int, FileArbProgram, const vector<string>&>>())
   , _argsParser(make_unique<ArgsParser>())
   , _fileArbSubProgramFactory(make_unique<FileArbSubProgramFactory>())
   // Mutable Components
   , _fileCreator(make_unique<FileCreator>())
   , _stopwatch(make_unique<Utils::Stopwatch>())
{
}

FileArbProgram::~FileArbProgram()
{
}

int FileArbProgram::Main(int argc, char* argv[]) // NOLINT
{
   if (argc == 1)
   {
      _console->NakedWriteLine(FileArbArgs::CommandLineUsage);
      return 0;
   }
   _stopwatch->Start();
   const vector<string> stringArgs = _call_Utils_Vector_FromArgcArgv(argc, argv);

   int exitCode = _nonVoidOneArgTryCatchCaller->TryCatchCallNonConstMemberFunction(
      this, &FileArbProgram::Run, stringArgs,
      &FileArbProgram::ExceptionHandler);

   const string runtimeInSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string durationLine = Utils::String::ConcatStrings("TotalDuration: ", runtimeInSeconds, " seconds");
   _console->ThreadIdWriteLine(durationLine);
   const string exitCodeLine = Utils::String::ConcatValues("ExitCode: ", exitCode);
   _console->ThreadIdWriteLine(exitCodeLine);
   return exitCode;
}

int FileArbProgram::Run(const vector<string>& stringArgs)
{
   const FileArbArgs args = _argsParser->ParseStringArgs(stringArgs);
   const shared_ptr<FileArbSubProgram> fileArbSubProgram = _fileArbSubProgramFactory->NewFileArbSubProgram(args.programMode);
   int exitCode = fileArbSubProgram->Run(args);
   return exitCode;
}

int FileArbProgram::ExceptionHandler(const exception& ex, const vector<string>& /*stringArgs*/)
{
   const string exceptionTypeNameAndWhat = _call_Utils_Exception_ClassNameAndMessage(&ex);
   const string exceptionErrorMessage = "Error: Exception thrown: " + exceptionTypeNameAndWhat;
   _console->ThreadIdWriteLineWithColor(exceptionErrorMessage, Color::Red);
   return 1;
}
