#pragma once

class BytesStringConverter
{
public:
   virtual ~BytesStringConverter() = default;
   virtual size_t ConvertBytesStringToBytes(string_view bytesString) const;
};
