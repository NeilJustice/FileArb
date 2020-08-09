#pragma once
#include "libFileArb/Components/Console/Console.h"

namespace Utils
{
   class ConsoleMock : public Zen::Mock<Console>
	{
   public:
		ZENMOCK_VOID1_CONST(Write, string_view, _string)
		ZENMOCK_VOID1_CONST(Write, int, _int)
		ZENMOCK_VOID0_CONST(WriteLine)
		ZENMOCK_VOID1_CONST(WriteLine, int, _int)
		ZENMOCK_VOID1_CONST(WriteLine, string_view, _string)
	};
}
