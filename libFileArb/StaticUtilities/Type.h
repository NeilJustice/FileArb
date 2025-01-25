#pragma once
#if defined __linux__
#include <atomic>
#include <cxxabi.h>
#endif

namespace Utils
{
   class Type
   {
   private:
      friend class TypeTests;
      static unordered_map<const char*, string> s_mangledToDemangledTypeNameCache;

   public:
      template<typename T>
      static const string* GetName(const T& variable)
      {
         const string* const typeName = TypeInfoToTypeName(typeid(variable));
         return typeName;
      }

      template<typename T>
      static const string* GetName()
      {
         const string* const typeName = TypeInfoToTypeName(typeid(T));
         return typeName;
      }

      Type() = delete;

   private:
      static const string* TypeInfoToTypeName(const type_info& typeInfo)
      {
         const char* const mangledTypeName = typeInfo.name();
         const unordered_map<const char*, string>::const_iterator
            findIter = s_mangledToDemangledTypeNameCache.find(mangledTypeName);
         if (findIter == s_mangledToDemangledTypeNameCache.end())
         {
            const string demangledTypeName = Demangle(mangledTypeName);
            const pair<unordered_map<const char*, string>::const_iterator, bool>
               emplaceResult = s_mangledToDemangledTypeNameCache.emplace(mangledTypeName, demangledTypeName);
            const string* const cachedDemangledTypeName = &emplaceResult.first->second;
            return cachedDemangledTypeName;
         }
         const string* const cachedDemangledTypeName = &findIter->second;
         return cachedDemangledTypeName;
      }

   #if defined __linux__
      static string Demangle(const char* mangledTypeName)
      {
         int demangleStatus = -1;
         unique_ptr<char, void (*)(void*)> demangledTypeNamePointer(
            abi::__cxa_demangle(mangledTypeName, nullptr, nullptr, &demangleStatus),
            free);
         release_assert(demangleStatus == 0);
         string demangledTypeName(demangledTypeNamePointer.get());
         return demangledTypeName;
      }
   #elif _WIN32
      static string Demangle(const char* mangledTypeName)
      {
         string mangledTypeNameString(mangledTypeName);
         release_assert(mangledTypeNameString.starts_with("class "));
         mangledTypeNameString.erase(0, 6);
         release_assert(!mangledTypeNameString.starts_with("class "));
         return mangledTypeNameString;
      }
   #endif
   };
}
