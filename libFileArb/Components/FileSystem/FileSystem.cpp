#include "pch.h"
#include "libFileArb/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"
#include "libFileArb/Components/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"

#if defined __linux__ || defined __APPLE__
int* GetErrno()
{
   return &errno;
}
#endif

FileSystem::FileSystem()
   // Function Pointers
#if defined __linux__ || defined __APPLE__
   : _call_errno(GetErrno)
   , _call_fopen(fopen)
#elif _WIN32
   : _call_errno(_errno)
   , _call_fopen_s(fopen_s)
#endif
   , _call_fclose(fclose)
   , _call_fs_create_directories_as_assignable_function_overload_pointer(fs::create_directories)
   , _call_fwrite(fwrite)
   // Function Callers
   , _caller_OpenFile(make_unique<_caller_OpenFileType>())
   // Constant Components
   , _asserter(make_unique<Asserter>())
   , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
{
   _call_fs_create_directories = _call_fs_create_directories_as_assignable_function_overload_pointer;
}

FileSystem::~FileSystem()
{
}

void FileSystem::CreateTextFile(const fs::path& filePath, string_view text) const
{
   CreateBinaryOrTextFile(filePath, "w", text.data(), text.size());
}

void FileSystem::CreateBinaryFile(const fs::path& filePath, const char* bytes, size_t bytesSize) const
{
   CreateBinaryOrTextFile(filePath, "wb", bytes, bytesSize);
}

#if defined __linux__ || defined __APPLE__

FILE* FileSystem::OpenFile(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* openedFile = _call_fopen(filePath.string().c_str(), fileOpenMode);
   if (openedFile == nullptr)
   {
      const int errnoValue = *_call_errno();
      const string errnoDescription = _errorCodeTranslator->GetErrnoDescription(errnoValue);
      const string exceptionMessage = String::Concat(
         "fopen(filePath.string().c_str(), fileOpenMode) returned nullptr. ",
         "filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
         "\". errno=", errnoValue, " (", errnoDescription, ").");
      throw runtime_error(exceptionMessage);
   }
   return openedFile;
}

#elif _WIN32

FILE* FileSystem::OpenFile(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* openedFile = nullptr;
   const errno_t fopensReturnValue = _call_fopen_s(&openedFile, filePath.string().c_str(), fileOpenMode);
   if (fopensReturnValue != 0)
   {
      const int errnoValue = *_call_errno();
      const string errnoDescription = _errorCodeTranslator->GetErrnoDescription(errnoValue);
      const string exceptionMessage = String::Concat(
         "fopen_s(&openedFile, filePath.string().c_str(), fileOpenMode) returned non-0: ", fopensReturnValue,
         ". filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
         "\". errno=", errnoValue, " (", errnoDescription, ").");
      throw runtime_error(exceptionMessage);
   }
   return openedFile;
}

#endif

void FileSystem::CreateBinaryOrTextFile(
   const fs::path& filePath, const char* fileOpenMode, const char* bytes, size_t bytesSize) const
{
   const fs::path parentDirectoryPath = filePath.parent_path();
   _call_fs_create_directories(parentDirectoryPath);
   FILE* const filePointer = _caller_OpenFile->CallConstMemberFunction(this, &FileSystem::OpenFile, filePath, fileOpenMode);
   const size_t numberOfBytesWritten = _call_fwrite(bytes, 1, bytesSize, filePointer);
   _asserter->ThrowIfSizeTValuesNotEqual(numberOfBytesWritten, bytesSize, "fwrite unexpectedly did not return bytesSize");
   const int fcloseReturnValue = _call_fclose(filePointer);
   if (fcloseReturnValue != 0)
   {
      const int errnoValue = *_call_errno();
      throw FileCloseException(filePath, errnoValue);
   }
}
