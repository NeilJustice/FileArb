#pragma once

class String
{
public:
   static bool ContainsSubstring(std::string_view stringView, std::string_view substring);
   static bool CaseInsensitiveContainsSubstring(std::string_view stringView, std::string_view substring);

   template<typename... Types>
   static std::string Concat(Types&&... values)
   {
      std::ostringstream oss;
      (oss << ... << std::forward<Types>(values));
      const std::string concatenatedValues = oss.str();
      return concatenatedValues;
   }

   String() = delete;
private:
   static std::string ToAllLowercase(std::string_view str);
};
