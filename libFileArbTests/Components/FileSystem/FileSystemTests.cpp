#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"

TESTS(FileSystemTests)
AFACT(DefaultConstructor_NewsComponents_SetsFunctionPointers)
AFACT(OpenFile_FileCannotBeOpened_ThrowsRuntimeError)
FACTS(CloseFile_fcloseReturnValueIsNot0_ThrowsFileCloseException)
AFACT(CloseFile_fcloseReturnValueIs0_Returns)
EVIDENCE

FileSystem _fileSystem;
METALMOCK_NONVOID1_FREE(int, fclose, FILE*)
METALMOCK_NONVOID0_FREE(int*, _errno)
METALMOCK_NONVOID2_NAMESPACED_FREE(bool, fs, create_directories, const fs::path&, error_code&)

STARTUP
{
   _fileSystem._call_fclose = BIND_1ARG_METALMOCK_OBJECT(fcloseMock);
   _fileSystem._call_errno = BIND_0ARG_METALMOCK_OBJECT(_errnoMock);
   _fileSystem._call_fs_create_directories = BIND_2ARG_METALMOCK_OBJECT(create_directoriesMock);
}

TEST(DefaultConstructor_NewsComponents_SetsFunctionPointers)
{
   FileSystem fileSystem;
   fileSystem._call_errno(); // Code coverage for GetErrno on Linux
   STD_FUNCTION_TARGETS(::fclose, fileSystem._call_fclose);
#ifdef __linux__
   STD_FUNCTION_TARGETS(GetErrno, fileSystem._call_errno);
#elif _WIN32
   STD_FUNCTION_TARGETS(::_errno, fileSystem._call_errno);
   using create_directories_overload = bool(*)(const fs::path&, error_code&);
   STD_FUNCTION_TARGETS_OVERLOAD(
      create_directories_overload, fs::create_directories, fileSystem._call_fs_create_directories);
#endif
}

TEST(OpenFile_FileCannotBeOpened_ThrowsRuntimeError)
{
   int errnoValue = ZenUnit::RandomBetween<int>(0, 10);
   _errnoMock.Return(&errnoValue);

   const fs::path filePathThatDoesNotExist = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = "r";
   //
   ErrnoTranslator errnoTranslator;
   const string expectedErrnoDescription = errnoTranslator.ToReadable(errnoValue);
   const string expectedExceptionMessage = String::Concat(
      "fopen() returned nullptr. filePath=\"", filePathThatDoesNotExist.string(),
      "\". fileOpenMode=\"", fileOpenMode, "\". errno=", errnoValue, " (", expectedErrnoDescription, ").");
   THROWS_EXCEPTION(_fileSystem.OpenFile(filePathThatDoesNotExist, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   METALMOCK(_errnoMock.CalledOnce());
}

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
   FILE* const file = nullptr;
   //
   _fileSystem.CloseFile(filePath, file);
   //
   METALMOCK(fcloseMock.CalledOnceWith(file));
}

RUN_TESTS(FileSystemTests)
