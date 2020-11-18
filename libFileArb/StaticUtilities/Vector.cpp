#include "pch.h"
#include "libFileArb/StaticUtilities/Vector.h"

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
