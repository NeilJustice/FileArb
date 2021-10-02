#pragma once
#include "libFileArb/UtilityComponents/FunctionCallers/TryCatchCallers/NonVoidOneArgTryCatchCaller.h"

template<typename ReturnType, typename ClassType, typename ArgumentType>
class NonVoidOneArgTryCatchCallerMock : public Metal::Mock<NonVoidOneArgTryCatchCaller<ReturnType, ClassType, ArgumentType>>
{
public:
   using MemberFunctionType = int (ClassType::*)(ArgumentType);
   using ExceptionHandlerType = int (ClassType::*)(const exception&, ArgumentType);
   METALMOCK_NONVOID4_CONST(int, TryCatchCallNonConstMemberFunction, ClassType*, MemberFunctionType, ArgumentType, ExceptionHandlerType)
};
