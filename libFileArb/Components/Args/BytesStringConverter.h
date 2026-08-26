#pragma once

class BytesStringConverter
{
public:
   virtual ~BytesStringConverter() = default;

   virtual size_t ConvertBytesStringToNumberOfBytes(const string& bytesString) const;
};
