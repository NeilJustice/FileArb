#pragma once
#include "libFileArb/Components/FunctionCallers/Member/VoidFourArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   class VoidFourArgMemberFunctionCallerMock : public Metal::Mock<VoidFourArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
   public:
      using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const;
      METALMOCK_VOID6_CONST(CallConstMemberFunction, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type, Arg4Type)

      using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type, Arg4Type);
      METALMOCK_VOID6_CONST(CallNonConstMemberFunction, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type, Arg4Type)
   };
}
