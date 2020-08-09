#pragma once
#include "libFileArb/Components/Function/Member/VoidThreeArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCallerMock : public Zen::Mock<VoidThreeArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      using NonConstThreeArgMemberFunctionType = void (ClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type);
      METALMOCK_VOID6_CONST(CallNonConstMemberFunctionNTimes, size_t, NonConstThreeArgMemberFunctionType, ClassType*, Arg1Type, Arg2Type, Arg3Type)
   };
}
