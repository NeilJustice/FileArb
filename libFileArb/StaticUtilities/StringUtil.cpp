#include "pch.h"
#include "libFileArb/StaticUtilities/StringUtil.h"
#ifdef __linux__
#include <charconv>
#endif

namespace Utils
{
   bool Utils::String::ContainsSubstring(string_view stringView, string_view substring)
   {
      const bool strContainsSubstring = strstr(stringView.data(), substring.data()) != nullptr;
      return strContainsSubstring;
   }

   bool Utils::String::CaseInsensitiveContainsSubstring(string_view stringView, string_view substring)
   {
      const string lowercaseStr = ToLowercase(stringView);
      const string lowercaseSubstring = ToLowercase(substring);
      const bool strContainsSubstring = ContainsSubstring(lowercaseStr, lowercaseSubstring);
      return strContainsSubstring;
   }

   string Utils::String::ToLowercase(string_view str)
   {
      string lowercaseString;
      const size_t strSize = str.size();
      lowercaseString.resize(strSize);
      for (size_t i = 0; i < strSize; ++i)
      {
         const int c = static_cast<int>(str[i]);
         const char lowercaseCharacter = static_cast<char>(tolower(c));
         lowercaseString[i] = lowercaseCharacter;
      }
      return lowercaseString;
   }

   size_t Utils::String::ToSizeT(string_view str)
   {
      size_t sizeTValue{};
      const from_chars_result fromCharsResult = from_chars(str.data(), str.data() + str.size(), sizeTValue, 10);
      if (fromCharsResult.ec != errc{})
      {
         const string exceptionMessage = Utils::String::ConcatStrings(
            "String::ToSizeT(string_view str) called with str not converted to size_t: \"", str, "\"");
         throw invalid_argument(exceptionMessage);
      }
      return sizeTValue;
   }
}
