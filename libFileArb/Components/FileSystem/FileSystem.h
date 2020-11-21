#pragma once
class Asserter;
class ErrorCodeTranslator;
class FileSystemTests;

#ifdef __linux__
int* GetErrno();
#endif

class FileSystem
{
   friend class ::FileSystemTests;
private:
   // Function Callers
   std::function<errno_t(FILE**, const char*, const char*)> _call_fopen_s;
   std::function<int(FILE*)> _call_fclose;
   std::function<int* ()> _call_errno;
   using create_directories_FunctionOverloadType = bool(*)(const fs::path&, error_code&);
   std::function<bool(const fs::path&, error_code&)> _call_fs_create_directories;
   // Constant Callers
   unique_ptr<const Asserter> _asserter;
   unique_ptr<const ErrorCodeTranslator> _errorCodeTranslator;
public:
   FileSystem();
   virtual ~FileSystem();
   virtual void CreateTextFile(const fs::path& filePath, string_view text) const;
   virtual void CreateBinaryFile(const fs::path& filePath, const char* bytes, size_t bytesSize) const;
private:
   virtual FILE* OpenFile(const fs::path& filePath, const char* fileOpenMode) const;
   virtual void CloseFile(const fs::path& filePath, FILE* filePointer) const;
   virtual void CreateBinaryOrTextFile(
      const fs::path& filePath, bool trueBinaryFalseText, const char* bytes, size_t bytesSize) const;
};
