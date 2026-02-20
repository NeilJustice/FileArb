#include "pch.h"
#include "libFileArb/Components/Vector/VectorHelper.h"

namespace Utils
{
   vector<string> VectorHelper::FromArgcArgv(int argc, char** argv) const
   {
      release_assert(argc >= 1);
      release_assert(argv != nullptr);
      vector<string> args;
      args.reserve(static_cast<size_t>(argc));
      std::for_each(argv, argv + argc, [&](char* arg)
      {
         args.emplace_back(arg);
      });
      return args;
   }

   string VectorHelper::Join(const vector<string>& vec, char separator) const
   {
      const size_t vectorSize = vec.size();
      if (vectorSize == 0)
      {
         return std::string();
      }
      ostringstream oss;
      for (size_t i = 0; i < vectorSize; ++i)
      {
         const string& element = vec[i];
         oss << element;
         if (i < vectorSize - 1)
         {
            oss << separator;
         }
      }
      string joinedVectorString = oss.str();
      return joinedVectorString;
   }
}
