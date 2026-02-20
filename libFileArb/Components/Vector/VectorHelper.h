#pragma once

namespace Utils
{
   class VectorHelper
   {
   public:
      virtual ~VectorHelper() = default;

      virtual vector<string> FromArgcArgv(int argc, char** argv) const;
      virtual string Join(const vector<string>& vec, char separator) const;
   };
}
