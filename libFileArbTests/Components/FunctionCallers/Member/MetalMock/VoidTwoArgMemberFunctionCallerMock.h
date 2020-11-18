#pragma once
#include "libFileArb/Components/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCallerMock : public Metal::Mock<VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
{
public:
   using NonConstTwoArgMemberFunctionType = void (ClassType::*)(size_t, Arg1Type, Arg2Type);

   METALMOCK_VOID5_CONST(CallNonConstMemberFunctionNTimes,
      size_t, NonConstTwoArgMemberFunctionType, ClassType*, Arg1Type, Arg2Type)

   METALMOCK_VOID5_CONST(ParallelCallNonConstMemberFunctionNTimes,
      size_t, NonConstTwoArgMemberFunctionType, ClassType*, Arg1Type, Arg2Type)
};
