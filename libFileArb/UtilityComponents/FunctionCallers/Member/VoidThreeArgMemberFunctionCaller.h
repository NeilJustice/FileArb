#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller
{
public:
   virtual void CallNonConstMemberFunctionNTimes(
      size_t numberOfCalls,
      void (ClassType::*nonConstMemberFunction)(size_t, Arg1Type, Arg2Type, Arg3Type),
      ClassType* nonConstClassPointer,
      Arg1Type arg1,
      Arg2Type arg2,
      Arg3Type arg3) const
   {
      for (size_t callIndex = 0; callIndex < numberOfCalls; ++callIndex)
      {
         (nonConstClassPointer->*nonConstMemberFunction)(callIndex, arg1, arg2, arg3);
      }
   }

   virtual ~VoidThreeArgMemberFunctionCaller() = default;
};
