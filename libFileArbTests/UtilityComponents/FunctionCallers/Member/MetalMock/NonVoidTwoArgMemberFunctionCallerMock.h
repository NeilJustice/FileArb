#pragma once
#include "libFileArb/UtilityComponents/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMemberFunctionCallerMock : public Metal::Mock<NonVoidTwoArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type>>
   {
   public:
      using ConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type) const;
      METALMOCK_NONVOID4_CONST(ReturnType, CallConstMemberFunction, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type)
   };
}
