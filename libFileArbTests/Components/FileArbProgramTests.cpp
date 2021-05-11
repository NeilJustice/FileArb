#include "pch.h"
#include "libFileArb/Components/Args/FileArbArgsParser.h"
#include "libFileArb/Components/FileArbProgram.h"
#include "libFileArb/StaticUtilities/Vector.h"
#include "libFileArbTests/Components/Args/MetalMock/FileArbArgsParserMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileArbSubProgramFactoryMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileArbSubProgramMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/UtilityComponents/Exception/MetalMock/TryCatchCallerMock.h"
#include "libFileArbTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(FileArbProgramTests)
AFACT(DefaultConstructor_SetsFunctionPointer_NewsComponents)
AFACT(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
FACTS(Main_ArgcIsNot1_TryCatchCallsRunWithStringArgs_PrintsDuration_PrintsExitCode_ReturnsSubProgramExitCode)
AFACT(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
AFACT(ExceptionHandler_PrintsExceptionClassNameAndMessageInRed_Returns1)
EVIDENCE

FileArbProgram _fileArbProgram;
// Function Callers
METALMOCK_NONVOID2_STATIC(vector<string>, Vector, FromArgcArgv, int, char**)
METALMOCK_NONVOID1_STATIC(string, Exception, GetClassNameAndMessage, const exception*)
// Constant Components
ConsoleMock* _consoleMock = nullptr;
TryCatchCallerMock<FileArbProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;
FileArbArgsParserMock* _argsParserMock = nullptr;
// Mutable Components
FileArbSubProgramFactoryMock* _fileArbSubProgramFactoryMock = nullptr;
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Function Callers
   _fileArbProgram._call_Utils_Vector_FromArgcArgv = BIND_2ARG_METALMOCK_OBJECT(FromArgcArgvMock);
   _fileArbProgram._call_Utils_Exception_ClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(GetClassNameAndMessageMock);
   // Constant Components
   _fileArbProgram._console.reset(_consoleMock = new ConsoleMock);
   _fileArbProgram._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMock<FileArbProgram, const vector<string>&>);
   _fileArbProgram._argsParser.reset(_argsParserMock = new FileArbArgsParserMock);
   _fileArbProgram._fileArbSubProgramFactory.reset(_fileArbSubProgramFactoryMock = new FileArbSubProgramFactoryMock);
   // Mutable Components
   _fileArbProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
   _fileArbProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionPointer_NewsComponents)
{
   FileArbProgram fileArbProgram;
   // Function Callers
   STD_FUNCTION_TARGETS(Exception::GetClassNameAndMessage, fileArbProgram._call_Utils_Exception_ClassNameAndMessage);
   STD_FUNCTION_TARGETS(Vector::FromArgcArgv, fileArbProgram._call_Utils_Vector_FromArgcArgv);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileArbProgram._console);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._tryCatchCaller);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._argsParser);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._fileArbSubProgramFactory);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._fileCreator);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._stopwatch);
}

TEST(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() };
   //
   const int exitCode = _fileArbProgram.Main(1, const_cast<char**>(argv));
   //
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(FileArbArgs::CommandLineUsage));
   ARE_EQUAL(0, exitCode);
}

TEST1X1(Main_ArgcIsNot1_TryCatchCallsRunWithStringArgs_PrintsDuration_PrintsExitCode_ReturnsSubProgramExitCode,
   int argc,
   -1,
   0,
   2,
   3)
{
   const vector<string> stringArgs{ ZenUnit::Random<string>(), ZenUnit::Random<string>() };
   FromArgcArgvMock.Return(stringArgs);

   int subProgramExitCode = _tryCatchCallerMock->TryCatchCallMock.ReturnRandom();

   const string runtimeInSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() };
   //
   const int returnedSubProgramExitCode = _fileArbProgram.Main(argc, const_cast<char**>(argv));
   //
   METALMOCK(FromArgcArgvMock.CalledOnceWith(argc, const_cast<char**>(argv)));
   METALMOCK(_tryCatchCallerMock->TryCatchCallMock.CalledOnceWith(
      &_fileArbProgram, &FileArbProgram::Run, stringArgs, &FileArbProgram::ExceptionHandler));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());

   const string expectedDurationLine = String::ConcatValues("Duration: ", runtimeInSeconds, " seconds");
   const string expectedExitCodeLine = String::ConcatValues("ExitCode: ", subProgramExitCode);
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { expectedDurationLine },
      { expectedExitCodeLine }
   }));

   ARE_EQUAL(subProgramExitCode, returnedSubProgramExitCode);
}

TEST(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
{
   _stopwatchMock->StartMock.Expect();

   const FileArbArgs args = _argsParserMock->ParseArgsMock.ReturnRandom();

   shared_ptr<FileArbSubProgramMock> fileArbSubProgramMock = make_shared<FileArbSubProgramMock>();
   const int exitCode = fileArbSubProgramMock->RunMock.ReturnRandom();
   _fileArbSubProgramFactoryMock->NewFileArbSubProgramMock.Return(fileArbSubProgramMock);

   _consoleMock->WriteLineMock.Expect();

   const vector<string> stringArgs =
   {
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>()
   };
   //
   const int returnedExitCode = _fileArbProgram.Run(stringArgs);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_argsParserMock->ParseArgsMock.CalledOnceWith(stringArgs));
   METALMOCK(_fileArbSubProgramFactoryMock->NewFileArbSubProgramMock.CalledOnceWith(args.programMode));
   METALMOCK(fileArbSubProgramMock->RunMock.CalledOnceWith(args));
   const string expectedRunningMessage = "Running: " + args.commandLine;
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningMessage));
   ARE_EQUAL(exitCode, returnedExitCode);
}

TEST(ExceptionHandler_PrintsExceptionClassNameAndMessageInRed_Returns1)
{
   const string exceptionClassNameAndMessage = ZenUnit::Random<string>();
   GetClassNameAndMessageMock.Return(exceptionClassNameAndMessage);

   _consoleMock->WriteLineColorMock.Expect();
   const exception ex;
   const vector<string> args = { ZenUnit::Random<string>() };
   //
   int exitCode = _fileArbProgram.ExceptionHandler(ex, args);
   //
   METALMOCK(GetClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedExceptionErrorMessage = "Error: Exception thrown: " + exceptionClassNameAndMessage;
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedExceptionErrorMessage, Color::Red));
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(FileArbProgramTests)
