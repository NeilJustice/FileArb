#include "pch.h"
#include "libFileArb/StaticUtilities/StringUtil.h"

bool String::ContainsSubstring(string_view stringView, string_view substring)
{
   const bool strContainsSubstring = ::strstr(stringView.data(), substring.data()) != nullptr;
   return strContainsSubstring;
}

bool String::CaseInsensitiveContainsSubstring(string_view stringView, string_view substring)
{
   const string lowercaseStr = String::ToAllLowercase(stringView);
   const string lowercaseSubstring = String::ToAllLowercase(substring);
   const bool strContainsSubstring = ContainsSubstring(lowercaseStr, lowercaseSubstring);
   return strContainsSubstring;
}

string String::ToAllLowercase(string_view str)
{
   string lowercaseString;
   const size_t strSize = str.size();
   lowercaseString.resize(strSize);
   for (size_t i = 0; i < strSize; ++i)
   {
      const int c = static_cast<int>(str[i]);
      const char lowercaseCharacter = static_cast<char>(::tolower(c));
      lowercaseString[i] = lowercaseCharacter;
   }
   return lowercaseString;
}
