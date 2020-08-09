#include "pch.h"
#include "libFileArb/Components/Exception/Exception.h"
#include "libFileArb/Components/FileArb/FileArbArgsParser.h"
#include "libFileArb/Components/FileArb/FileArbProgram.h"
#include "libFileArb/Utilities/DataStructure/Vector.h"
#include "libFileArb/ValueTypes/FileArbArgs.h"
#include "libFileArbTests/Components/FileArb/ZenMock/FileArbArgsParserMock.h"
#include "libFileArbTests/Components/SubPrograms/ZenMock/FileArbSubProgramFactoryMock.h"
#include "libFileArbTests/Components/SubPrograms/ZenMock/FileArbSubProgramMock.h"
#include "libFileArbTests/Components/SubPrograms/ZenMock/FileCreatorMock.h"
#include "libFileArbTests/Components/Console/ZenMock/ConsoleMock.h"
#include "libFileArbTests/Components/Exception/ZenMock/TryCatchCallerMock.h"
#include "libFileArbTests/Components/Time/ZenMock/StopwatchMock.h"

TESTS(FileArbProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
FACTS(Main_ArgcIsNot1_CallsTryCatchCallRunWithStringVectorOfArgs_PrintsProgramRuntimeInMilliseconds_ReturnsExitCode)
AFACT(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
AFACT(ExceptionHandler_PrintsExceptionClassNameAndWhat_Returns1)
EVIDENCE

FileArbProgram _fileArbProgram;
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::TryCatchCallerMock<FileArbProgram, const vector<string>&>* _tryCatchCallerMock = nullptr;
Utils::StopwatchMock* _stopwatchMock = nullptr;
FileArbArgsParserMock* _argsParserMock = nullptr;
FileArbSubProgramFactoryMock* _fileArbSubProgramFactoryMock = nullptr;
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   _fileArbProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileArbProgram._tryCatchCaller.reset(_tryCatchCallerMock = new Utils::TryCatchCallerMock<FileArbProgram, const vector<string>&>);
   _fileArbProgram._argsParser.reset(_argsParserMock = new FileArbArgsParserMock);
   _fileArbProgram._fileArbSubProgramFactory.reset(_fileArbSubProgramFactoryMock = new FileArbSubProgramFactoryMock);
   _fileArbProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
   _fileArbProgram._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   FileArbProgram fileArbProgram;
   STD_FUNCTION_TARGETS(Utils::Exception::ClassNameAndWhat, fileArbProgram._call_Utils_Exception_ClassNameAndWhat);
   STD_FUNCTION_TARGETS(Utils::Vector::FromArgcArgv, fileArbProgram._call_Utils_Vector_FromArgcArgv);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._console);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._tryCatchCaller);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._argsParser);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._fileArbSubProgramFactory);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._fileCreator);
   DELETE_TO_ASSERT_NEWED(fileArbProgram._stopwatch);
}

TEST(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
{
   _consoleMock->WriteLineMock_string.Expect();
   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() };
   //
   const int exitCode = _fileArbProgram.Main(1, const_cast<char**>(argv));
   //
   ZENMOCK(_consoleMock->WriteLineMock_string.CalledOnceWith(FileArbArgs::CommandLineUsage));
   ARE_EQUAL(0, exitCode);
}

TEST1X1(Main_ArgcIsNot1_CallsTryCatchCallRunWithStringVectorOfArgs_PrintsProgramRuntimeInMilliseconds_ReturnsExitCode,
   int argc,
   -1,
   0,
   2,
   3)
{
   _stopwatchMock->StartMock.Expect();

   ZENMOCK_NONVOID2_STATIC(vector<string>, Utils::Vector, FromArgcArgv, int, char**);
   _fileArbProgram._call_Utils_Vector_FromArgcArgv = BIND_2ARG_ZENMOCK_OBJECT(FromArgcArgvMock);

   const vector<string> vectorArgs{ ZenUnit::Random<string>(), ZenUnit::Random<string>() };
   FromArgcArgvMock.Return(vectorArgs);

   int tryCatchCallReturnValue = ZenUnit::Random<int>();
   _tryCatchCallerMock->TryCatchCallMock.Return(tryCatchCallReturnValue);

   const string runtimeInSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineMock_string.Expect();

   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() };
   //
   const int exitCode = _fileArbProgram.Main(argc, const_cast<char**>(argv));
   //
   ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
   ZENMOCK(FromArgcArgvMock.CalledOnceWith(argc, const_cast<char**>(argv)));
   ZENMOCK(_tryCatchCallerMock->TryCatchCallMock.CalledOnceWith(
      &_fileArbProgram, &FileArbProgram::Run, vectorArgs, &FileArbProgram::ExceptionHandler));
   ZENMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedDurationLine = "[FileArb] Duration: " + runtimeInSeconds + " seconds";
   const string expectedExitCodeLine = "[FileArb] ExitCode: " + to_string(exitCode);
   ZENMOCK(_consoleMock->WriteLineMock_string.CalledAsFollows(
   {
      { expectedDurationLine },
      { expectedExitCodeLine }
   }));
   ARE_EQUAL(tryCatchCallReturnValue, exitCode);
}

TEST(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
{
   const FileArbArgs args = _argsParserMock->ParseArgsMock.ReturnRandom();
   _argsParserMock->PrintPreambleMock.Expect();

   shared_ptr<FileArbSubProgramMock> fileArbSubProgramMock = make_shared<FileArbSubProgramMock>();
   const int exitCode = fileArbSubProgramMock->RunMock.ReturnRandom();
   _fileArbSubProgramFactoryMock->NewFileArbSubProgramMock.Return(fileArbSubProgramMock);

   const vector<string> stringArgs =
   {
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>(),
      ZenUnit::Random<string>()
   };
   //
   const int returnedExitCode = _fileArbProgram.Run(stringArgs);
   //
   ZENMOCK(_argsParserMock->ParseArgsMock.CalledOnceWith(stringArgs));
   ZENMOCK(_argsParserMock->PrintPreambleMock.CalledOnceWith(args));
   ZENMOCK(_fileArbSubProgramFactoryMock->NewFileArbSubProgramMock.CalledOnceWith(args.programMode));
   ZENMOCK(fileArbSubProgramMock->RunMock.CalledOnceWith(args));
   ARE_EQUAL(exitCode, returnedExitCode);
}

TEST(ExceptionHandler_PrintsExceptionClassNameAndWhat_Returns1)
{
   ZENMOCK_NONVOID1_STATIC(string, Utils::Exception, ClassNameAndWhat, const exception*);
   const string exceptionTypeNameAndWhat = ZenUnit::Random<string>();
   ClassNameAndWhatMock.Return(exceptionTypeNameAndWhat);
   _fileArbProgram._call_Utils_Exception_ClassNameAndWhat = BIND_1ARG_ZENMOCK_OBJECT(ClassNameAndWhatMock);

   _consoleMock->WriteLineMock_string.Expect();
   const exception ex;
   const vector<string> args = { ZenUnit::Random<string>() };
   //
   int exitCode = _fileArbProgram.ExceptionHandler(ex, args);
   //
   ZENMOCK(ClassNameAndWhatMock.CalledOnceWith(&ex));
   const string expectedErrorMessage = "FileArb error: FileArb threw an exception:\n" + exceptionTypeNameAndWhat;
   ZENMOCK(_consoleMock->WriteLineMock_string.CalledOnceWith(expectedErrorMessage));
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(FileArbProgramTests)
