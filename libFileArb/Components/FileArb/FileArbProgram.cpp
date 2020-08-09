#include "pch.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"
#include "libFileArb/Components/FileArb/FileArbProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgram.h"
#include "libFileArb/Components/SubPrograms/FileArbSubProgramFactory.h"
#include "libFileArb/Components/SubPrograms/FileCreator.h"
#include "libFileArb/Utilities/DataStructure/Vector.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"

FileArbProgram::FileArbProgram()
   : _call_Utils_Exception_ClassNameAndWhat(Utils::Exception::ClassNameAndWhat)
   , _call_Utils_Vector_FromArgcArgv(Utils::Vector::FromArgcArgv)
   , _console(make_unique<Utils::Console>())
   , _tryCatchCaller(make_unique<Utils::TryCatchCaller<FileArbProgram, const vector<string>&>>())
   , _argsParser(make_unique<FileArbArgsParser>())
   , _fileArbSubProgramFactory(make_unique<FileArbSubProgramFactory>())
   , _fileCreator(make_unique<FileCreator>())
   , _stopwatch(make_unique<Utils::Stopwatch>())
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
   const shared_ptr<FileArbSubProgram> fileArbSubProgram =
      _fileArbSubProgramFactory->NewFileArbSubProgram(args.programMode);
   const int exitCode = fileArbSubProgram->Run(args);
   return exitCode;
}

int FileArbProgram::ExceptionHandler(const exception& ex, const vector<string>& stringArgs)
{
   const string exceptionTypeNameAndWhat = _call_Utils_Exception_ClassNameAndWhat(&ex);
   const string errorMessage = "FileArb error: FileArb threw an exception:\n" + exceptionTypeNameAndWhat;
   _console->WriteLine(errorMessage);
   return 1;
}
