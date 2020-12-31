#include "pch.h"
#include "libFileArb/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"

#if defined __linux__ || defined __APPLE__
int* GetErrno()
{
   return &errno;
}
#endif

FileSystem::FileSystem()
   // Function Callers
   : _call_fclose(::fclose)
#if defined __linux__ || defined __APPLE__
   , _call_errno(GetErrno)
   , _call_fopen(::fopen)
#elif _WIN32
   , _call_errno(::_errno)
   , _call_fopen_s(::fopen_s)
   , _call_fs_create_directories(static_cast<create_directories_FunctionOverloadType>(fs::create_directories))
#endif
   // Constant Components
   , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::CreateTextFile(const fs::path& filePath, string_view text) const
{
   CreateBinaryOrTextFile(filePath, false, text.data(), text.size());
}

void FileSystem::CreateBinaryFile(const fs::path& filePath, const char* bytes, size_t bytesSize) const
{
   CreateBinaryOrTextFile(filePath, true, bytes, bytesSize);
}

FILE* FileSystem::OpenFile(const fs::path& filePath, const char* fileOpenMode) const
{
#if defined __linux__ || defined __APPLE__
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
#elif _WIN32
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
#endif
}

void FileSystem::CloseFile(const fs::path& filePath, FILE* filePointer) const
{
   const int fcloseReturnValue = _call_fclose(filePointer);
   if (fcloseReturnValue != 0)
   {
      const int errnoValue = *_call_errno();
      throw FileCloseException(filePath, errnoValue);
   }
}

void FileSystem::CreateBinaryOrTextFile(
   const fs::path& filePath, bool trueBinaryFalseText, const char* bytes, size_t bytesSize) const
{
   const fs::path parentDirectoryPath = filePath.parent_path();
   fs::create_directories(parentDirectoryPath);
   FILE* const file = OpenFile(filePath, trueBinaryFalseText ? "wb" : "w");
#ifdef _WIN32
   const size_t numberOfBytesWritten = _fwrite_nolock(bytes, 1, bytesSize, file);
#else
   const size_t numberOfBytesWritten = fwrite(bytes, 1, bytesSize, file);
#endif
   release_assert(numberOfBytesWritten == bytesSize);
   CloseFile(filePath, file);
}
