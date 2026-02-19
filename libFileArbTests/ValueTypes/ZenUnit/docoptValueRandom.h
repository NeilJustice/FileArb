#pragma once
#include "libFileArb/docopt/docopt.h"

namespace ZenUnit
{
   template<>
   inline docopt::value Random()
   {
      const long randomLong = ZenUnit::Random<long>();
      if (randomLong % 2 == 0)
      {
         docopt::value randomLongDocoptValue(randomLong);
         return randomLongDocoptValue;
      }
      const string randomString = ZenUnit::Random<string>();
      docopt::value randomStringDocoptValue(randomString);
      return randomStringDocoptValue;
   }
}
