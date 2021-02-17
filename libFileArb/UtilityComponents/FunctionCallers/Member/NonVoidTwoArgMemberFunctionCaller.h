#pragma once

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller
{
public:
   virtual ReturnType CallConstMemberFunction(
      const ClassType* constClassPointer,
      ReturnType(ClassType::* constMemberFunction)(Arg1Type, Arg2Type) const,
      Arg1Type arg1,
      Arg2Type arg2) const
   {
      ReturnType returnValue = (constClassPointer->*constMemberFunction)(arg1, arg2);
      return returnValue;
   }

   virtual ~NonVoidTwoArgMemberFunctionCaller() = default;
};
