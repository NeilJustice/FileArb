#pragma once

class Exception
{
public:
   static string GetClassNameAndMessage(const exception* ex);
   Exception() = delete;
};
