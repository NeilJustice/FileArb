#pragma once

class String
{
public:
   static bool ContainsSubstring(string_view stringView, string_view substring);
   static bool CaseInsensitiveContainsSubstring(string_view stringView, string_view substring);
   static string ToLowercase(string_view str);
   static size_t ToSizeT(string_view str);

   template<typename... Types>
   static string Concat(Types&&... values)
   {
      ostringstream oss;
      (oss << ... << forward<Types>(values));
      const string concatenatedValues = oss.str();
      return concatenatedValues;
   }

   String() = delete;
};
