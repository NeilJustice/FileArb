#pragma once
class FileSystemTests;

#ifdef __linux__
int* GetErrno();
#endif

class FileSystem
{
   friend class ::FileSystemTests;
private:
   std::function<FILE* (const char*, const char*)> _call_fopen;
   std::function<int(FILE*)> _call_fclose;
   std::function<int* ()> _call_errno;
   std::function<bool(const fs::path&, error_code&)> _call_fs_create_directories;
public:
   FileSystem();
   virtual ~FileSystem() = default;
   virtual void CreateTextFile(const fs::path& filePath, string_view text) const;
   virtual void CreateBinaryFile(const fs::path& filePath, const char* bytes, size_t bytesSize) const;
private:
   virtual FILE* OpenFile(const fs::path& filePath, const char* mode) const;
   virtual void CloseFile(const fs::path& filePath, FILE* filePointer) const;
   virtual void CreateBinaryOrTextFile(
      const fs::path& filePath, bool trueBinaryFalseText, const char* bytes, size_t bytesSize) const;
};
