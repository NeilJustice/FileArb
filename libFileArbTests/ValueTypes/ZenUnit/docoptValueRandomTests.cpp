#include "pch.h"
#include "libFileArbTests/ValueTypes/ZenUnit/docoptValueRandom.h"

TESTS(docoptValueRandomTests)
AFACT(Random_ReturnsdocoptvalueWithAllNonDefaultFields)
EVIDENCE

TEST(Random_ReturnsdocoptvalueWithAllNonDefaultFields)
{
   const docopt::value randomDocoptValue = ZenUnit::Random<docopt::value>();
   IS_TRUE(randomDocoptValue.isLong() || randomDocoptValue.isString());
}

RUN_TESTS(docoptValueRandomTests)
