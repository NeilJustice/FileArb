#pragma once

namespace Utils
{
   string MakeFileSystemExceptionMessage(const fs::path& filePath, int errnoValue);

   class FileOpenException : public std::runtime_error
   {
   public:
      FileOpenException(const fs::path& filePath, int errnoValue);
   };

   class FileCloseException : public std::runtime_error
   {
   public:
      FileCloseException(const fs::path& filePath, int errnoValue);
   };

   class FileCreateException : public std::runtime_error
   {
   public:
      FileCreateException(const fs::path& filePath, int errnoValue);
   };

   class FileMalformedException : public std::runtime_error
   {
   public:
      FileMalformedException(const fs::path& filePath, const std::string& reason);
      FileMalformedException(const fs::path& filePath, size_t lineNumber, const std::string& reason);
      static std::string MakeExceptionMessage(const fs::path& filePath, size_t lineNumber, const std::string& reason);
   };
}
