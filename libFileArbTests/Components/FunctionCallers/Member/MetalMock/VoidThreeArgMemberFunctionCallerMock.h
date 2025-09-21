#pragma once
#include "libFileArb/Components/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCallerMock : public Metal::Mock<VoidThreeArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      using ConstThreeArgMemberFunctionType = void (ClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type) const;
      METALMOCK_VOID6_CONST(CallConstMemberFunctionNTimes, size_t, const ClassType*, ConstThreeArgMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)
   };
}
