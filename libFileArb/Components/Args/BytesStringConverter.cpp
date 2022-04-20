#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"
#include <regex>

size_t BytesStringConverter::ConvertBytesStringToNumberOfBytes(const string& bytesString) const
{
   const string bytesStringAsLowercase = Utils::String::ToLowercase(bytesString);
   if (regex_match(bytesStringAsLowercase, regex("^\\d+b$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t bytes = Utils::String::ToSizeT(bytesStringSubstring);
      return bytes;
   }
   else if (regex_match(bytesStringAsLowercase, regex("^\\d+k$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t kilobytes = Utils::String::ToSizeT(bytesStringSubstring);
      const size_t bytes = kilobytes * 1024;
      return bytes;
   }
   else if (regex_match(bytesStringAsLowercase, regex("^\\d+m$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t megabytes = Utils::String::ToSizeT(bytesStringSubstring);
      const size_t bytes = megabytes * 1024 * 1024;
      return bytes;
   }
   else if (regex_match(bytesStringAsLowercase, regex("^\\d+g$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t gigabytes = Utils::String::ToSizeT(bytesStringSubstring);
      const size_t bytes = gigabytes * 1024 * 1024 * 1024;
      return bytes;
   }
   else if (regex_match(bytesStringAsLowercase, regex("^\\d+$")))
   {
      const size_t bytes = Utils::String::ToSizeT(bytesString);
      return bytes;
   }
   const string exceptionMessage = Utils::String::ConcatStrings(
      "BytesStringConverter::ConvertBytesStringToNumberOfBytes(string_view bytesString) called with invalid bytesString: \"", bytesString, "\"");
   throw invalid_argument(exceptionMessage);
}
