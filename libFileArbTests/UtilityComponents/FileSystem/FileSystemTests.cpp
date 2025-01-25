#include "pch.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArbTests/UtilityComponents/Misc/MetalMock/AsserterMock.h"
#include "libFileArbTests/UtilityComponents/ErrorHandling/MetalMock/ErrorCodeTranslatorMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "libFileArbTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidFourArgMemberFunctionCallerMock.h"

TESTS(FileSystemTests)
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
// Behavior Functions
AFACT(CreateTextFile_CallsCreateBinaryOrTextFileWithTextFileArguments)
AFACT(CreateFileWithBytes_CallsCreateBinaryOrTextFileWithBinaryFileArguments)
// Private Functions
AFACT(CreateBinaryOrTextFile_CreatesParentDirectoryOfFilePath_CreatesFileWithSpecifiedBytes)
AFACT(GetCurrentPath_ReturnsResultOfCallingFilesystemCurrentPath)
#if defined __linux__
AFACT(OpenFile_FOpenReturnsNullptr_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
AFACT(OpenFile_FOpenReturnsNonNullptr_ReturnsOpenedFile)
#elif _WIN32
AFACT(OpenFile_FOpenSReturns0_ReturnsOpenedFile)
AFACT(OpenFile_FOpenSReturnsNon0_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
#endif
EVIDENCE

Utils::FileSystem _fileSystem;
// Function Pointers
METALMOCK_NONVOID0_STATIC_OR_FREE(int*, _call_errno)
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_fclose, FILE*)
#if defined __linux__
METALMOCK_NONVOID2_STATIC_OR_FREE(FILE*, _call_fopen, const char*, const char*)
#elif _WIN32
METALMOCK_NONVOID3_STATIC_OR_FREE(errno_t, _call_fopen_s, FILE**, const char*, const char*)
#endif
METALMOCK_NONVOID1_STATIC_OR_FREE(bool, _call_fs_create_directories, const fs::path&)
METALMOCK_NONVOID4_STATIC_OR_FREE(size_t, _call_fwrite, const void*, size_t, size_t, FILE*)
METALMOCK_NONVOID0_STATIC_OR_FREE(fs::path, _call_get_fs_current_path)
// Function Callers
using _caller_CreateBinaryOrTextFileMockType = Utils::VoidFourArgMemberFunctionCallerMock<Utils::FileSystem, const fs::path&, const char*, const char*, size_t>;
_caller_CreateBinaryOrTextFileMockType* _caller_CreateBinaryOrTextFileMock = nullptr;

using _caller_OpenFileMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<shared_ptr<FILE>, Utils::FileSystem, const fs::path&, const char*>;
_caller_OpenFileMockType* _caller_OpenFileMock = nullptr;
// Constant Components
Utils::AsserterMock* _asserterMock = nullptr;
Utils::ErrorCodeTranslatorMock* _errorCodeTranslatorMock = nullptr;

STARTUP
{
   // Function Pointers
   _fileSystem._call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
   _fileSystem._call_fclose = BIND_1ARG_METALMOCK_OBJECT(_call_fcloseMock);
#if defined __linux__
   _fileSystem._call_fopen = BIND_2ARG_METALMOCK_OBJECT(_call_fopenMock);
#elif _WIN32
   _fileSystem._call_fopen_s = BIND_3ARG_METALMOCK_OBJECT(_call_fopen_sMock);
#endif
   _fileSystem._call_fs_create_directories = BIND_1ARG_METALMOCK_OBJECT(_call_fs_create_directoriesMock);
   _fileSystem._call_fwrite = BIND_4ARG_METALMOCK_OBJECT(_call_fwriteMock);
   _fileSystem._call_get_fs_current_path = BIND_0ARG_METALMOCK_OBJECT(_call_get_fs_current_pathMock);
   // Function Callers
   _fileSystem._caller_CreateBinaryOrTextFile.reset(_caller_CreateBinaryOrTextFileMock = new _caller_CreateBinaryOrTextFileMockType);
   _fileSystem._caller_OpenFile.reset(_caller_OpenFileMock = new _caller_OpenFileMockType);
   // Constant Components
   _fileSystem._asserter.reset(_asserterMock = new Utils::AsserterMock);
   _fileSystem._errorCodeTranslator.reset(_errorCodeTranslatorMock = new Utils::ErrorCodeTranslatorMock);
}

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   Utils::FileSystem fileSystem{};
   // Function Pointers
   STD_FUNCTION_TARGETS(fclose, fileSystem._call_fclose);
#if defined __linux__
   STD_FUNCTION_TARGETS(GetErrno, fileSystem._call_errno);
   STD_FUNCTION_TARGETS(fopen, fileSystem._call_fopen);
#elif _WIN32
   STD_FUNCTION_TARGETS(_errno, fileSystem._call_errno);
   STD_FUNCTION_TARGETS(fopen_s, fileSystem._call_fopen_s);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::CreateDirectoriesOverloadType, fs::create_directories, fileSystem._call_fs_create_directories);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::GetCurrentPathOverloadType, fs::current_path, fileSystem._call_get_fs_current_path);
#endif
   STD_FUNCTION_TARGETS(fwrite, fileSystem._call_fwrite);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_CreateBinaryOrTextFile);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_OpenFile);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileSystem._asserter);
   DELETE_TO_ASSERT_NEWED(fileSystem._errorCodeTranslator);

   fileSystem._call_errno(); // 100% code coverage for GetErrno() on Linux
}

// Behavior Functions

TEST(CreateTextFile_CallsCreateBinaryOrTextFileWithTextFileArguments)
{
   _caller_CreateBinaryOrTextFileMock->CallConstMemberFunctionMock.Expect();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _fileSystem.CreateTextFile(filePath, text);
   //
   METALMOCK(_caller_CreateBinaryOrTextFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateBinaryOrTextFile, filePath, "w", text.data(), text.size()));
}

TEST(CreateFileWithBytes_CallsCreateBinaryOrTextFileWithBinaryFileArguments)
{
   _caller_CreateBinaryOrTextFileMock->CallConstMemberFunctionMock.Expect();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string bytesString = ZenUnit::Random<string>();
   //
   _fileSystem.CreateFileWithBytes(filePath, bytesString);
   //
   METALMOCK(_caller_CreateBinaryOrTextFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateBinaryOrTextFile, filePath, "wb", bytesString.data(), bytesString.size()));
}

TEST(GetCurrentPath_ReturnsResultOfCallingFilesystemCurrentPath)
{
   const fs::path currentPath = _call_get_fs_current_pathMock.ReturnRandom();
   //
   const fs::path returnedCurrentPath = _fileSystem.GetCurrentPath();
   //
   METALMOCK(_call_get_fs_current_pathMock.CalledOnce());
   ARE_EQUAL(currentPath, returnedCurrentPath);
}

// Private Functions

TEST(CreateBinaryOrTextFile_CreatesParentDirectoryOfFilePath_CreatesFileWithSpecifiedBytes)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_OpenFileMock->CallConstMemberFunctionMock.Return(filePointer);

   const size_t numberOfBytesWritten = _call_fwriteMock.ReturnRandom();

   _asserterMock->ThrowIfSizeTValuesNotEqualMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   const string bytes = ZenUnit::Random<string>();
   //
   _fileSystem.CreateBinaryOrTextFile(filePath, fileOpenMode, bytes.data(), bytes.size());
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   METALMOCK(_caller_OpenFileMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::OpenFile, filePath, fileOpenMode));
   METALMOCK(_call_fwriteMock.CalledOnceWith(bytes.data(), 1, bytes.size(), filePointer.get()));
   METALMOCK(_asserterMock->ThrowIfSizeTValuesNotEqualMock.CalledOnceWith(numberOfBytesWritten, bytes.size(), "fwrite unexpectedly did not return bytesSize"));
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

   void AssertCalledOnceWith(const fs::path& expectedFilePath, const char* expectedFileOpenMode) const
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedFilePath, filePathArgument);
      ARE_EQUAL(expectedFileOpenMode, fileOpenModeArgument);
   }
} _fopen_CallHistory;

#if defined __linux__

FILE* fopen_CallInsteadFunction(const char* filePath, const char* fileOpenMode)
{
   _fopen_CallHistory.RecordFunctionCall(filePath, fileOpenMode);
   return _fopen_CallHistory.returnValue;
}

TEST(OpenFile_FOpenReturnsNullptr_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
{
   _fopen_CallHistory.returnValue = nullptr;
   _call_fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   int errnoValue = ZenUnit::Random<int>();
   _call_errnoMock.Return(&errnoValue);

   const string errnoDescription = _errorCodeTranslatorMock->GetErrnoDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "fopen(filePath.string().c_str(), fileOpenMode) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
      "\". errno=", errnoValue, " (", errnoDescription, ").");
   THROWS_EXCEPTION(_fileSystem.OpenFile(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   _fopen_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   METALMOCK(_call_errnoMock.CalledOnce());
   METALMOCK(_errorCodeTranslatorMock->GetErrnoDescriptionMock.CalledOnceWith(errnoValue));
}

TEST(OpenFile_FOpenReturnsNonNullptr_ReturnsOpenedFile)
{
   FILE* const rawFilePointer = tmpfile();
   _fopen_CallHistory.returnValue = rawFilePointer;

   _call_fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const shared_ptr<FILE> returnedOpenedFile = _fileSystem.OpenFile(filePath, fileOpenMode);
   //
   _fopen_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   ARE_EQUAL(rawFilePointer, returnedOpenedFile.get());
}

#elif _WIN32

struct fopen_s_CallHistory
{
   size_t numberOfCalls = 0;
   errno_t returnValue = 0;
   FILE** outRawFilePointerArgument = nullptr;
   FILE* outFileReturnValue = nullptr;
   fs::path filePathArgument;
   const char* fileOpenModeArgument = nullptr;

   void RecordFunctionCall(FILE** outRawFilePointer, const fs::path& filePath, const char* fileOpenMode)
   {
      ++numberOfCalls;
      outRawFilePointerArgument = outRawFilePointer;
      tmpfile_s(&outFileReturnValue);
      *outRawFilePointer = outFileReturnValue;
      filePathArgument = filePath;
      fileOpenModeArgument = fileOpenMode;
   }

   void AssertCalledOnceWith(const char* expectedFilePath, const char* expectedFileOpenMode)
   {
      ARE_EQUAL(1, numberOfCalls);
      IS_NOT_NULLPTR(outRawFilePointerArgument);
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
   _call_fopen_sMock.CallInstead(std::bind(&FileSystemTests::fopen_s_CallInsteadFunction, this, placeholders::_1, placeholders::_2, placeholders::_3));
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const shared_ptr<FILE> openedFile = _fileSystem.OpenFile(filePath, fileOpenMode);
   //
   _fopen_s_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   ARE_EQUAL(_fopen_s_CallHistory.outFileReturnValue, openedFile.get());
}

TEST(OpenFile_FOpenSReturnsNon0_ThrowsRuntimeErrorExceptionWithReadableErrnoValue)
{
   _fopen_s_CallHistory.returnValue = ZenUnit::RandomNon0<int>();
   _call_fopen_sMock.CallInstead(std::bind(&FileSystemTests::fopen_s_CallInsteadFunction, this, placeholders::_1, placeholders::_2, placeholders::_3));

   int errnoValue = ZenUnit::Random<int>();
   _call_errnoMock.Return(&errnoValue);

   const string errnoDescription = _errorCodeTranslatorMock->GetErrnoDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "fopen_s(&openedFile, filePath.string().c_str(), fileOpenMode) returned non-0: ", _fopen_s_CallHistory.returnValue,
      ". filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
      "\". errno=", errnoValue, " (", errnoDescription, ").");
   THROWS_EXCEPTION(_fileSystem.OpenFile(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   _fopen_s_CallHistory.AssertCalledOnceWith(filePath.string().c_str(), fileOpenMode);
   METALMOCK(_call_errnoMock.CalledOnce());
   METALMOCK(_errorCodeTranslatorMock->GetErrnoDescriptionMock.CalledOnceWith(errnoValue));
}

#endif

RUN_TESTS(FileSystemTests)
