#include "pch.h"
#include "libFileArb/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/UtilityComponents/FileSystem/FileSystemExceptions.h"

namespace Utils
{
   string MakeFileSystemExceptionMessage(const fs::path& filePath, int errnoValue)
   {
      Utils::ErrorCodeTranslator errorCodeTranslator{};
      const string errnoDescription = errorCodeTranslator.GetErrnoDescription(errnoValue);
      string exceptionWhat = Utils::String::ConcatValues(filePath.string(), ". Reason: ", errnoDescription, ". errno=", errnoValue);
   #ifdef _WIN32
      _set_errno(0);
   #endif
      return exceptionWhat;
   }

   FileOpenException::FileOpenException(const fs::path& filePath, int errnoValue)
      : runtime_error(MakeFileSystemExceptionMessage(filePath, errnoValue))
   {
   }

   FileCloseException::FileCloseException(const fs::path& filePath, int errnoValue)
      : runtime_error(MakeFileSystemExceptionMessage(filePath, errnoValue))
   {
   }

   FileCreateException::FileCreateException(const fs::path& filePath, int errnoValue)
      : runtime_error(MakeFileSystemExceptionMessage(filePath, errnoValue))
   {
   }

   FileMalformedException::FileMalformedException(const fs::path& filePath, const std::string& reason)
      : runtime_error(filePath.string() + ":\n" + reason)
   {
   }

   FileMalformedException::FileMalformedException(const fs::path& filePath, size_t lineNumber, const string& reason)
      : runtime_error(MakeExceptionMessage(filePath, lineNumber, reason))
   {
   }

   string FileMalformedException::MakeExceptionMessage(const fs::path& filePath, size_t lineNumber, const std::string& reason)
   {
      string exceptionMessage = Utils::String::ConcatValues(filePath.string(), "(", lineNumber, "):\n", reason);
      return exceptionMessage;
   }
}
