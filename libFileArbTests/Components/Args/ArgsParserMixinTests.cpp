#include "pch.h"
#include "libFileArb/Components/Args/ArgsParserMixin.h"

TESTS(ArgsParserMixinTests)
AFACT(DefaultConstructor_NewsComponents)
EVIDENCE

TEST(DefaultConstructor_NewsComponents)
{
   ArgsParserMixin argsParserMixin;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(argsParserMixin.p_docoptParser);
}

RUN_TESTS(ArgsParserMixinTests)
