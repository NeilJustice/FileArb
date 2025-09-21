#pragma once
#include "libFileArb/Components/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCallerMock : public Metal::Mock<VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
   {
   public:
      using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type) const;
      using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type);
      METALMOCK_VOID4_CONST(CallConstMemberFunction, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type)
      METALMOCK_VOID4_CONST(CallNonConstMemberFunction, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type)

      using ConstIndexMemberFunctionType = void (ClassType::*)(size_t, Arg1Type, Arg2Type) const;
      METALMOCK_VOID5_CONST(CallConstMemberFunctionNTimes, size_t, const ClassType*, ConstIndexMemberFunctionType, Arg1Type, Arg2Type)
      METALMOCK_VOID5_CONST(ParallelCallConstMemberFunctionNTimes, size_t, const ClassType*, ConstIndexMemberFunctionType, Arg1Type, Arg2Type)
   };
}
