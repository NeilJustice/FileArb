#include "pch.h"
#include "libFileArb/Components/Args/BytesStringConverter.h"

size_t BytesStringConverter::ConvertBytesStringToNumberOfBytes(const string& bytesString) const
{
   const string bytesStringAsLowercase = String::ToLowercase(bytesString);
   if (boost::regex_match(bytesStringAsLowercase, boost::regex("^\\d+b$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t bytes = String::ToSizeT(bytesStringSubstring);
      return bytes;
   }
   else if (boost::regex_match(bytesStringAsLowercase, boost::regex("^\\d+k$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t kilobytes = String::ToSizeT(bytesStringSubstring);
      const size_t bytes = kilobytes * 1024;
      return bytes;
   }
   else if (boost::regex_match(bytesStringAsLowercase, boost::regex("^\\d+m$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t megabytes = String::ToSizeT(bytesStringSubstring);
      const size_t bytes = megabytes * 1024 * 1024;
      return bytes;
   }
   else if (boost::regex_match(bytesStringAsLowercase, boost::regex("^\\d+g$")))
   {
      const string bytesStringSubstring = bytesString.substr(0, bytesString.size() - 1);
      const size_t gigabytes = String::ToSizeT(bytesStringSubstring);
      const size_t bytes = gigabytes * 1024 * 1024 * 1024;
      return bytes;
   }
   else if (boost::regex_match(bytesStringAsLowercase, boost::regex("^\\d+$")))
   {
      const size_t bytes = String::ToSizeT(bytesString);
      return bytes;
   }
   const string exceptionMessage = String::Concat(
      "BytesStringConverter::ConvertBytesStringToNumberOfBytes(string_view bytesString) called with invalid bytesString: \"", bytesString, "\"");
   throw invalid_argument(exceptionMessage);
}
