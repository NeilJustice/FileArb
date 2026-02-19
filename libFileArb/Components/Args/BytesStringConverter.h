#pragma once

class BytesStringConverter
{
   friend class BytesStringConverterTests;
public:
   virtual ~BytesStringConverter() = default;

   virtual size_t ConvertBytesStringToNumberOfBytes(const string& bytesString) const;
};
