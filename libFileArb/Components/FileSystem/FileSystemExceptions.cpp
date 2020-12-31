#include "pch.h"
#include "libFileArb/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libFileArb/Components/FileSystem/FileSystemExceptions.h"

string MakeFileSystemExceptionMessage(const fs::path& filePath, int errnoValue)
{
   ErrorCodeTranslator errorCodeTranslator;
   const string errnoDescription = errorCodeTranslator.GetErrnoDescription(errnoValue);
   const string exceptionWhat = String::Concat(filePath.string(), ". Reason: ", errnoDescription, ". errno=", errnoValue);
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
   const string exceptionWhat = filePath.string() + "(" + to_string(lineNumber) + "):\n" + reason;
   return exceptionWhat;
}
