#pragma once
#include "libFileArb/Components/Exception/TryCatchCaller.h"

namespace Utils
{
   template<typename ClassType, typename ArgumentType>
   class TryCatchCallerMock : public Zen::Mock<TryCatchCaller<ClassType, ArgumentType>>
   {
   public:
      using MemberFunctionType = int (ClassType::*)(ArgumentType);
      using ExceptionHandlerType = int (ClassType::*)(const exception&, ArgumentType);
      METALMOCK_NONVOID4_CONST(int, TryCatchCall, ClassType*, MemberFunctionType, ArgumentType, ExceptionHandlerType)
   };
}
