#pragma once
#include "libFileArb/Components/Function/Member/VoidTwoArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCallerMock : public Zen::Mock<VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
   {
   public:
      using NonConstTwoArgMemberFunctionType = void (ClassType::*)(size_t, Arg1Type, Arg2Type);

      ZENMOCK_VOID5_CONST(CallNonConstMemberFunctionNTimes,
         size_t, NonConstTwoArgMemberFunctionType, ClassType*, Arg1Type, Arg2Type)

      ZENMOCK_VOID5_CONST(ParallelCallNonConstMemberFunctionNTimes,
         size_t, NonConstTwoArgMemberFunctionType, ClassType*, Arg1Type, Arg2Type)
   };
}
