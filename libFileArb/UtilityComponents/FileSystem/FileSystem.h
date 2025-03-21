#pragma once
class FileSystemTests;

#if defined __linux__
int* GetErrno();
#endif

namespace Utils
{
   class Asserter;
   class ErrorCodeTranslator;

   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMemberFunctionCaller;

   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgMemberFunctionCaller;

   class FileSystem
   {
   private:
      friend class ::FileSystemTests;
      // Function Pointers
      std::function<int*()> _call_errno;
   #if defined __linux__
      std::function<FILE*(const char*, const char*)> _call_fopen;
   #elif _WIN32
      std::function<errno_t(FILE**, const char*, const char*)> _call_fopen_s;
   #endif
      std::function<int(FILE*)> _call_fclose;
      using CreateDirectoriesOverloadType = bool(*)(const fs::path&);
      bool(*_call_fs_create_directories_as_assignable_function_overload_pointer)(const fs::path&);
      std::function<bool(const fs::path&)> _call_fs_create_directories;
      function<size_t(const void*, size_t, size_t, FILE*)> _call_fwrite;

      using GetCurrentPathOverloadType = fs::path(*)();
      fs::path(*_call_get_fs_current_path_as_assignable_function_overload_pointer)();
      function<fs::path()> _call_get_fs_current_path;
      // Function Callers
      using _caller_CreateBinaryOrTextFileType = Utils::VoidFourArgMemberFunctionCaller<FileSystem, const fs::path&, const char*, const char*, size_t>;
      unique_ptr<const _caller_CreateBinaryOrTextFileType> _caller_CreateBinaryOrTextFile;

      using _caller_OpenFileType = Utils::NonVoidTwoArgMemberFunctionCaller<shared_ptr<FILE>, FileSystem, const fs::path&, const char*>;
      unique_ptr<const _caller_OpenFileType> _caller_OpenFile;
      // Constant Callers
      unique_ptr<const Asserter> _asserter;
      unique_ptr<const ErrorCodeTranslator> _errorCodeTranslator;
   public:
      FileSystem();
      virtual ~FileSystem();
      virtual void CreateTextFile(const fs::path& filePath, string_view text) const;
      virtual void CreateFileWithBytes(const fs::path& filePath, string_view bytesString) const;
      virtual fs::path GetCurrentPath() const;
   private:
      void CreateBinaryOrTextFile(const fs::path& filePath, const char* fileOpenMode, const char* bytes, size_t bytesSize) const;
      shared_ptr<FILE> OpenFile(const fs::path& filePath, const char* fileOpenMode) const;
   };
}
