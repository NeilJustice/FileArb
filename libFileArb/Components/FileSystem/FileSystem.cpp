#include "pch.h"
#include "libFileArb/Components/Exception/ErrnoTranslator.h"
#include "libFileArb/Components/FileSystem/ErrorCodeTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystem.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"
#include "libFileArb/Components/Time/Stopwatch.h"

#ifdef __linux__
int* GetErrno()
{
   return &errno;
}
#endif

FileSystem::FileSystem()
   : _call_fopen(::fopen)
   , _call_fclose(::fclose)
#ifdef __linux__
   , _call_errno(GetErrno)
#elif _WIN32
   , _call_errno(::_errno)
   , _call_fs_create_directories(static_cast<bool(*)(const fs::path&, error_code&)>(fs::create_directories))
#endif
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

FILE* FileSystem::OpenFile(const fs::path& filePath, const char* mode) const
{
   FILE* const file = _call_fopen(filePath.string().c_str(), mode);
   if (file == nullptr)
   {
      const int errnoValue = *_call_errno();
      ErrnoTranslator errnoTranslator;
      const string errnoReadable = errnoTranslator.ToReadable(errnoValue);
      throw runtime_error("fopen() returned nullptr. filePath=\"" + filePath.string() +
         "\". fileOpenMode=\"" + string(mode) + "\". errno=" + to_string(errnoValue) + " (" + errnoReadable + ").");
   }
   return file;
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
