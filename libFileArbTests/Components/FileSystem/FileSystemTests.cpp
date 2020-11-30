#include "pch.h"
#include "libFileArb/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"
#include "libFileArbTests/Components/ErrorHandling/MetalMock/ErrorCodeTranslatorMock.h"
#include "libFileArbTests/Components/Misc/MetalMock/AsserterMock.h"

TESTS(FileSystemTests)
AFACT(DefaultConstructor_NewsComponents_SetsFunctionPointers)
#ifdef __linux__
AFACT(OpenFile_FOpenReturnsNonNullptr_ReturnsOpenedFile)
AFACT(OpenFile_FOpenSReturnsNullptr_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
#elif _WIN32
AFACT(OpenFile_FOpenSReturns0_ReturnsOpenedFile)
AFACT(OpenFile_FOpenSReturnsNon0_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
#endif
FACTS(CloseFile_fcloseReturnValueIsNot0_ThrowsFileCloseException)
AFACT(CloseFile_fcloseReturnValueIs0_Returns)
EVIDENCE

FileSystem _fileSystem;
// Function Callers
#ifdef __linux__
METALMOCK_NONVOID2_FREE(FILE*, fopen, const char*, const char*)
#elif _WIN32
METALMOCK_NONVOID3_FREE(errno_t, fopen_s, FILE**, const char*, const char*)
#endif
METALMOCK_NONVOID1_FREE(int, fclose, FILE*)
METALMOCK_NONVOID0_FREE(int*, _errno)
METALMOCK_NONVOID2_NAMESPACED_FREE(bool, fs, create_directories, const fs::path&, error_code&)
// Constant Components
AsserterMock* _asserterMock = nullptr;
ErrorCodeTranslatorMock* _errorCodeTranslatorMock = nullptr;

STARTUP
{
   // Function Callers
#ifdef __linux__
   _fileSystem._call_fopen = BIND_2ARG_METALMOCK_OBJECT(fopenMock);
#elif _WIN32
   _fileSystem._call_fopen_s = BIND_3ARG_METALMOCK_OBJECT(fopen_sMock);
#endif
   _fileSystem._call_fclose = BIND_1ARG_METALMOCK_OBJECT(fcloseMock);
   _fileSystem._call_errno = BIND_0ARG_METALMOCK_OBJECT(_errnoMock);
   _fileSystem._call_fs_create_directories = BIND_2ARG_METALMOCK_OBJECT(create_directoriesMock);
   // Constant Components
   _fileSystem._errorCodeTranslator.reset(_errorCodeTranslatorMock = new ErrorCodeTranslatorMock);
}

TEST(DefaultConstructor_NewsComponents_SetsFunctionPointers)
{
   FileSystem fileSystem;
   // Function Callers
   STD_FUNCTION_TARGETS(fclose, fileSystem._call_fclose);
#ifdef __linux__
   STD_FUNCTION_TARGETS(GetErrno, fileSystem._call_errno);
   STD_FUNCTION_TARGETS(fopen, fileSystem._call_fopen);
#elif _WIN32
   STD_FUNCTION_TARGETS(_errno, fileSystem._call_errno);
   STD_FUNCTION_TARGETS(fopen_s, fileSystem._call_fopen_s);
   STD_FUNCTION_TARGETS_OVERLOAD(
      FileSystem::create_directories_FunctionOverloadType, fs::create_directories, fileSystem._call_fs_create_directories);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileSystem._errorCodeTranslator);

   fileSystem._call_errno(); // 100% code coverage for GetErrno() on Linux
}

struct fopen_CallHistory
{
   size_t numberOfCalls = 0;
   FILE* returnValue = nullptr;
   fs::path filePathArgument;
   const char* fileOpenModeArgument = nullptr;

   void RecordFunctionCall(const char* filePath, const char* fileOpenMode)
   {
      ++numberOfCalls;
      filePathArgument = filePath;
      fileOpenModeArgument = fileOpenMode;
   }

   void AssertCalledOnceWith(const fs::path& expectedFilePath, const char* expectedFileOpenMode)
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedFilePath, filePathArgument);
      ARE_EQUAL(expectedFileOpenMode, fileOpenModeArgument);
   }
} _fopen_CallHistory;

FILE* fopen_CallInsteadFunction(const char* filePath, const char* fileOpenMode)
{
   _fopen_CallHistory.RecordFunctionCall(filePath, fileOpenMode);
   return _fopen_CallHistory.returnValue;
}

#ifdef __linux__

TEST(OpenFile_FOpenReturnsNonNullptr_ReturnsOpenedFile)
{
   FILE openedFile;
   _fopen_CallHistory.returnValue = &openedFile;
   fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const FILE* const returnedOpenedFile = _fileSystem.OpenFile(filePath, fileOpenMode);
   //
   _fopen_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   ARE_EQUAL(&openedFile, returnedOpenedFile);
}

TEST(OpenFile_FOpenSReturnsNullptr_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
{
   _fopen_CallHistory.returnValue = nullptr;
   fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   int errnoValue = ZenUnit::Random<int>();
   _errnoMock.Return(&errnoValue);

   const string errnoDescription = _errorCodeTranslatorMock->GetErrnoDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = String::Concat(
      "fopen(filePath.string().c_str(), fileOpenMode) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
      "\". errno=", errnoValue, " (", errnoDescription, ").");
   THROWS_EXCEPTION(_fileSystem.OpenFile(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   _fopen_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   METALMOCK(_errnoMock.CalledOnce());
   METALMOCK(_errorCodeTranslatorMock->GetErrnoDescriptionMock.CalledOnceWith(errnoValue));
}

#elif _WIN32

struct fopen_s_CallHistory
{
   size_t numberOfCalls = 0;
   errno_t returnValue = 0;
   FILE** outFileArgument = nullptr;
   FILE* outFileReturnValue = nullptr;
   fs::path filePathArgument;
   const char* fileOpenModeArgument = nullptr;

   void RecordFunctionCall(FILE** outFile, const fs::path& filePath, const char* fileOpenMode)
   {
      ++numberOfCalls;
      outFileArgument = outFile;
      *outFile = outFileReturnValue;
      filePathArgument = filePath;
      fileOpenModeArgument = fileOpenMode;
   }

   void AssertCalledOnceWith(const char* expectedFilePath, const char* expectedFileOpenMode)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(outFileArgument);
      ARE_EQUAL(expectedFilePath, filePathArgument);
      ARE_EQUAL(expectedFileOpenMode, fileOpenModeArgument);
   }
} _fopen_s_CallHistory;

errno_t fopen_s_CallInsteadFunction(FILE** outFile, const char* filePath, const char* fileOpenMode)
{
   _fopen_s_CallHistory.RecordFunctionCall(outFile, filePath, fileOpenMode);
   return _fopen_s_CallHistory.returnValue;
}

TEST(OpenFile_FOpenSReturns0_ReturnsOpenedFile)
{
   fopen_sMock.CallInstead(std::bind(&FileSystemTests::fopen_s_CallInsteadFunction,
      this, placeholders::_1, placeholders::_2, placeholders::_3));
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const FILE* const openedFile = _fileSystem.OpenFile(filePath, fileOpenMode);
   //
   _fopen_s_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   ARE_EQUAL(_fopen_s_CallHistory.outFileReturnValue, openedFile);
}

TEST(OpenFile_FOpenSReturnsNon0_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
{
   _fopen_s_CallHistory.returnValue = ZenUnit::RandomNon0<int>();
   fopen_sMock.CallInstead(std::bind(&FileSystemTests::fopen_s_CallInsteadFunction,
      this, placeholders::_1, placeholders::_2, placeholders::_3));

   int errnoValue = ZenUnit::Random<int>();
   _errnoMock.Return(&errnoValue);

   const string errnoDescription = _errorCodeTranslatorMock->GetErrnoDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = String::Concat(
      "fopen_s(&openedFile, filePath.string().c_str(), fileOpenMode) returned non-0: ", _fopen_s_CallHistory.returnValue,
      ". filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
      "\". errno=", errnoValue, " (", errnoDescription, ").");
   THROWS_EXCEPTION(_fileSystem.OpenFile(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   _fopen_s_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   METALMOCK(_errnoMock.CalledOnce());
   METALMOCK(_errorCodeTranslatorMock->GetErrnoDescriptionMock.CalledOnceWith(errnoValue));
}

#endif

TEST1X1(CloseFile_fcloseReturnValueIsNot0_ThrowsFileCloseException,
   int fcloseReturnValue,
   -2,
   -1,
   1,
   2)
{
   fcloseMock.Return(fcloseReturnValue);

   int errnoValue = ZenUnit::Random<int>();
   _errnoMock.Return(&errnoValue);

   const fs::path filePath = ZenUnit::Random<fs::path>();
   FILE* const file = nullptr;
   //
   const string expectedExceptionWhat = MakeFileSystemExceptionMessage(filePath, errnoValue);
   THROWS_EXCEPTION(_fileSystem.CloseFile(filePath, file), FileCloseException, expectedExceptionWhat);
   //
   METALMOCK(fcloseMock.CalledOnceWith(file));
   METALMOCK(_errnoMock.CalledOnce());
}

TEST(CloseFile_fcloseReturnValueIs0_Returns)
{
   fcloseMock.Return(0);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   FILE file;
   //
   _fileSystem.CloseFile(filePath, &file);
   //
   METALMOCK(fcloseMock.CalledOnceWith(&file));
}

RUN_TESTS(FileSystemTests)
