#include "pch.h"
#include "libFileArb/Components/FileArbProgram.h"
#include "libFileArbTests/Components/Args/MetalMock/ArgsParserMock.h"
#include "libFileArbTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libFileArbTests/Components/FunctionCallers/TryCatchCallers/MetalMock/NonVoidOneArgTryCatchCallerMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileArbSubProgramFactoryMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileArbSubProgramMock.h"
#include "libFileArbTests/Components/SubPrograms/MetalMock/FileCreatorMock.h"
#include "libFileArbTests/Components/Time/MetalMock/StopwatchMock.h"
#include "libFileArbTests/Components/Vector/MetalMock/VectorHelperMock.h"

TESTS(FileArbProgramTests)
AFACT(DefaultConstructor_SetsFunctionPointer_NewsComponents)
AFACT(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
AFACT(Main_ArgcIsNot1_TryCatchCallsRunWithStringArgs_PrintsDuration_PrintsExitCode_ReturnsSubProgramExitCode)
AFACT(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
AFACT(ExceptionHandler_PrintsExceptionClassNameAndMessageInRed_Returns1)
EVIDENCE

FileArbProgram _fileArbProgram;
// Function Callers
METALMOCK_NONVOID1_STATIC_OR_FREE(string, _call_Exception_GetClassNameAndMessage, const exception*)
// Constant Components
ArgsParserMock* _argsParserMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::NonVoidOneArgTryCatchCallerMock<int, FileArbProgram, const vector<string>&>* _nonVoidOneArgTryCatchCallerMock = nullptr;
Utils::StopwatchMock* _stopwatchMock = nullptr;
Utils::VectorHelperMock* _vectorHelperMock = nullptr;
// Mutable Components
FileArbSubProgramFactoryMock* _fileArbSubProgramFactoryMock = nullptr;
FileCreatorMock* _fileCreatorMock = nullptr;

STARTUP
{
   // Function Callers
   _fileArbProgram._call_Utils_Exception_ClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(_call_Exception_GetClassNameAndMessageMock);
   // Constant Components
   _fileArbProgram._argsParser.reset(_argsParserMock = new ArgsParserMock);
   _fileArbProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   _fileArbProgram._nonVoidOneArgTryCatchCaller.reset(_nonVoidOneArgTryCatchCallerMock = new Utils::NonVoidOneArgTryCatchCallerMock<int, FileArbProgram, const vector<string>&>);
   _fileArbProgram._fileArbSubProgramFactory.reset(_fileArbSubProgramFactoryMock = new FileArbSubProgramFactoryMock);
   _fileArbProgram._vectorHelper.reset(_vectorHelperMock = new Utils::VectorHelperMock);
   // Mutable Components
   _fileArbProgram._fileCreator.reset(_fileCreatorMock = new FileCreatorMock);
   _fileArbProgram._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionPointer_NewsComponents)
{
   const FileArbProgram fileArbProgram;
   // Function Callers
   STD_FUNCTION_TARGETS(Utils::Exception::GetClassNameAndMessage, fileArbProgram._call_Utils_Exception_ClassNameAndMessage);
}

TEST(Main_ArgcIs1_WritesCommandLineUsage_Returns0)
{
   _consoleMock->NakedWriteLineMock.Expect();
   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() }; // NOLINT
   //
   const int exitCode = _fileArbProgram.Main(1, const_cast<char**>(argv));
   //
   METALMOCK(_consoleMock->NakedWriteLineMock.CalledOnceWith(FileArbArgs::CommandLineUsage));
   ARE_EQUAL(0, exitCode);
}

TEST(Main_ArgcIsNot1_TryCatchCallsRunWithStringArgs_PrintsDuration_PrintsExitCode_ReturnsSubProgramExitCode)
{
   _stopwatchMock->StartMock.Expect();

   const vector<string> stringArgs = _vectorHelperMock->FromArgcArgvMock.ReturnRandom();

   int subProgramExitCode = _nonVoidOneArgTryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.ReturnRandom();

   const string runtimeInSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->ThreadIdWriteLineMock.Expect();

   const string exePath = ZenUnit::Random<string>();
   const string fileArbIniPath = ZenUnit::Random<string>();
   const int argc = ZenUnit::RandomNotEqualTo<int>(1);
   const char* argv[] = { exePath.c_str(), fileArbIniPath.c_str() }; // NOLINT
   //
   const int returnedSubProgramExitCode = _fileArbProgram.Main(argc, const_cast<char**>(argv));
   //
   const string expectedDurationLine = Utils::String::ConcatValues("TotalDuration: ", runtimeInSeconds, " seconds");
   const string expectedExitCodeLine = Utils::String::ConcatValues("ExitCode: ", subProgramExitCode);
   METALMOCK(_consoleMock->ThreadIdWriteLineMock.CalledNTimes(2));

   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(

   METALMOCKTHEN(_vectorHelperMock->FromArgcArgvMock.CalledOnceWith(argc, const_cast<char**>(argv)))).Then( // NOLINT

   METALMOCKTHEN(_nonVoidOneArgTryCatchCallerMock->TryCatchCallNonConstMemberFunctionMock.CalledOnceWith(
      &_fileArbProgram, &FileArbProgram::Run, stringArgs,
      &FileArbProgram::ExceptionHandler))).Then(

   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(

   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledWith(expectedDurationLine))).Then(

   METALMOCKTHEN(_consoleMock->ThreadIdWriteLineMock.CalledWith(expectedExitCodeLine)));
   ARE_EQUAL(subProgramExitCode, returnedSubProgramExitCode);
}

TEST(Run_ParsesArgs_GetsFileArbSubProgramForProgramMode_RunsFileArbSubProgram_ReturnsExitCodeFromSubProgram)
{
   const FileArbArgs args = _argsParserMock->ParseStringArgsMock.ReturnRandom();

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
   METALMOCKTHEN(_argsParserMock->ParseStringArgsMock.CalledOnceWith(stringArgs)).Then(
   METALMOCKTHEN(_fileArbSubProgramFactoryMock->NewFileArbSubProgramMock.CalledOnceWith(args.programMode))).Then(
   METALMOCKTHEN(fileArbSubProgramMock->RunMock.CalledOnceWith(args)));
   ARE_EQUAL(exitCode, returnedExitCode);
}

TEST(ExceptionHandler_PrintsExceptionClassNameAndMessageInRed_Returns1)
{
   const string exceptionClassNameAndMessage = ZenUnit::Random<string>();
   _call_Exception_GetClassNameAndMessageMock.Return(exceptionClassNameAndMessage);

   _consoleMock->ThreadIdWriteLineWithColorMock.Expect();
   const exception ex;
   const vector<string> args = { ZenUnit::Random<string>() };
   //
   int exitCode = _fileArbProgram.ExceptionHandler(ex, args);
   //
   const string expectedExceptionErrorMessage = "Error: Exception thrown: " + exceptionClassNameAndMessage;
   METALMOCK(_call_Exception_GetClassNameAndMessageMock.CalledOnceWith(&ex));
   METALMOCK(_consoleMock->ThreadIdWriteLineWithColorMock.CalledOnceWith(expectedExceptionErrorMessage, Color::Red));
   ARE_EQUAL(1, exitCode);
}

RUN_TESTS(FileArbProgramTests)
