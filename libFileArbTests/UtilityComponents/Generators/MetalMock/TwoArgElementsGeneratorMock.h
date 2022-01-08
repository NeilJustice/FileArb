#pragma once
#include "libFileArb/UtilityComponents/Generators/TwoArgElementsGenerator.h"

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class TwoArgElementsGeneratorMock : public Metal::Mock<TwoArgElementsGenerator<ReturnType, ClassType, Arg1Type, Arg2Type>>
   {
   public:
      METALMOCK_NONVOID4_CONST(ReturnType, GenerateNElements, size_t, const ClassType*, Arg1Type, Arg2Type)
   };
}
