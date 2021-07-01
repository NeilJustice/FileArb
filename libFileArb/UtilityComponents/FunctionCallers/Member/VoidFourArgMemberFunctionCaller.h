#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
class VoidFourArgMemberFunctionCaller
{
public:
   virtual void CallConstMemberFunction(
      const ClassType* constClassPointer,
      void (ClassType::* constMemberFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const,
      Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const
   {
      (constClassPointer->*constMemberFunction)(arg1, arg2, arg3, arg4);
   }

   virtual void CallNonConstMemberFunction(
      ClassType* nonConstClassPointer,
      void (ClassType::* nonConstMemberFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type),
      Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const
   {
      (nonConstClassPointer->*nonConstMemberFunction)(arg1, arg2, arg3, arg4);
   }

   virtual ~VoidFourArgMemberFunctionCaller() = default;
};
