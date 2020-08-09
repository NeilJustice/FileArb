#include "pch.h"
#include "libFileArb/Components/Misc/ReleaseAssert.h"
#include "libFileArb/Utilities/DataStructure/Vector.h"

namespace Utils
{
   vector<string> Vector::FromArgcArgv(int argc, char** argv)
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
}
