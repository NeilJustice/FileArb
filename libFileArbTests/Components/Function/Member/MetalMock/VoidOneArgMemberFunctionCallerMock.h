#pragma once
#include "libFileArb/Components/Function/Member/VoidOneArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename ArgType>
   class VoidOneArgMemberFunctionCallerMock : public Zen::Mock<VoidOneArgMemberFunctionCaller<ClassType, ArgType>>
   {
   public:
      using NonConstMemberFunctionType = void (ClassType::*)(ArgType);
      METALMOCK_VOID4_CONST(CallNonConstMemberFunctionNTimes, size_t, NonConstMemberFunctionType, ClassType*, ArgType)
      METALMOCK_VOID4_CONST(ParallelCallNonConstMemberFunctionNTimes, size_t, NonConstMemberFunctionType, ClassType*, ArgType)
   };
}
