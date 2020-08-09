#include "pch.h"
#include "libFileArbTests/Components/Docopt/ZenUnit/docoptValueRandom.h"

TESTS(docoptValueRandomTests)
AFACT(Random_ReturnsdocoptvalueWithAllNonDefaultFields)
EVIDENCE

TEST(Random_ReturnsdocoptvalueWithAllNonDefaultFields)
{
   const docopt::Value randomDocoptValue = ZenUnit::Random<docopt::Value>();
   IS_TRUE(randomDocoptValue.IsLong() || randomDocoptValue.IsString());
}

RUN_TESTS(docoptValueRandomTests)
