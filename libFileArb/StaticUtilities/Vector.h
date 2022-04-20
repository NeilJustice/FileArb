#pragma once

namespace Utils
{
   class Vector
   {
   public:
      static std::vector<std::string> FromArgcArgv(int argc, char** argv);

      template<typename T>
      static std::string Join(const std::vector<T>& vec, char separator)
      {
         const size_t vectorSize = vec.size();
         if (vectorSize == 0)
         {
            return std::string();
         }
         std::ostringstream oss;
         for (size_t i = 0; i < vectorSize; ++i)
         {
            const T& element = vec[i];
            oss << element;
            if (i < vectorSize - 1)
            {
               oss << separator;
            }
         }
         std::string joinedVectorString = oss.str();
         return joinedVectorString;
      }

      template<typename T>
      static bool Contains(const std::vector<T>& v, const T& element)
      {
         const size_t size = v.size();
         for (size_t i = 0; i < size; ++i)
         {
            const T& vectorElement = v[i];
            if (vectorElement == element)
            {
               return true;
            }
         }
         return false;
      }

      Vector() = delete;
   };
}
