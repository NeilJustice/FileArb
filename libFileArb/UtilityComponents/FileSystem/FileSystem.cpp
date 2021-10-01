#include "pch.h"
#include "libFileArb/UtilityComponents/Misc/Asserter.h"
#include "libFileArb/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/UtilityComponents/FileSystem/FCloseDeleter.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystem.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystemExceptions.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidFourArgMemberFunctionCaller.h"

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
   , _caller_CreateBinaryOrTextFile(make_unique<_caller_CreateBinaryOrTextFileType>())
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

// Behavior Functions

void FileSystem::CreateFileWithText(const fs::path& filePath, string_view text) const
{
   _caller_CreateBinaryOrTextFile->CallConstMemberFunction(
      this, &FileSystem::CreateBinaryOrTextFile, filePath, "w", text.data(), text.size());
}

void FileSystem::CreateFileWithBytes(const fs::path& filePath, const char* bytes, size_t bytesSize) const
{
   _caller_CreateBinaryOrTextFile->CallConstMemberFunction(
      this, &FileSystem::CreateBinaryOrTextFile, filePath, "wb", bytes, bytesSize);
}

// Private Functions

void FileSystem::CreateBinaryOrTextFile(const fs::path& filePath, const char* fileOpenMode, const char* bytes, size_t bytesSize) const
{
   const fs::path parentDirectoryPath = filePath.parent_path();
   _call_fs_create_directories(parentDirectoryPath);
   const shared_ptr<FILE> filePointer = _caller_OpenFile->CallConstMemberFunction(this, &FileSystem::OpenFile, filePath, fileOpenMode);
   const size_t numberOfBytesWritten = _call_fwrite(bytes, 1, bytesSize, filePointer.get());
   _asserter->ThrowIfSizeTValuesNotEqual(numberOfBytesWritten, bytesSize, "fwrite unexpectedly did not return bytesSize");
}

#if defined __linux__ || defined __APPLE__

shared_ptr<FILE> FileSystem::OpenFile(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* rawFilePointer = _call_fopen(filePath.string().c_str(), fileOpenMode);
   if (rawFilePointer == nullptr)
   {
      const int errnoValue = *_call_errno();
      const string errnoDescription = _errorCodeTranslator->GetErrnoDescription(errnoValue);
      const string exceptionMessage = String::ConcatValues(
         "fopen(filePath.string().c_str(), fileOpenMode) returned nullptr. ",
         "filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
         "\". errno=", errnoValue, " (", errnoDescription, ").");
      throw runtime_error(exceptionMessage);
   }
   shared_ptr<FILE> autoClosingFilePointer(rawFilePointer, FCloseDeleter());
   return autoClosingFilePointer;
}

#elif _WIN32

shared_ptr<FILE> FileSystem::OpenFile(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* rawFilePointer = nullptr;
   const errno_t fopensReturnValue = _call_fopen_s(&rawFilePointer, filePath.string().c_str(), fileOpenMode);
   if (fopensReturnValue != 0)
   {
      const int errnoValue = *_call_errno();
      const string errnoDescription = _errorCodeTranslator->GetErrnoDescription(errnoValue);
      const string exceptionMessage = String::ConcatValues(
         "fopen_s(&openedFile, filePath.string().c_str(), fileOpenMode) returned non-0: ", fopensReturnValue,
         ". filePath=\"", filePath.string(), "\". fileOpenMode=\"", fileOpenMode,
         "\". errno=", errnoValue, " (", errnoDescription, ").");
      throw runtime_error(exceptionMessage);
   }
   shared_ptr<FILE> autoClosingFilePointer(rawFilePointer, FCloseDeleter());
   return autoClosingFilePointer;
}

#endif
