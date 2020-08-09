#pragma once

namespace Utils
{
   template<typename ClassType, typename ArgType>
   class VoidOneArgMemberFunctionCaller
   {
   public:
      virtual void CallNonConstMemberFunctionNTimes(
         size_t numberOfCalls,
         void (ClassType::*nonConstMemberFunction)(ArgType),
         ClassType* nonConstClassPointer,
         ArgType arg) const
      {
         for (size_t i = 0; i < numberOfCalls; ++i)
         {
            (nonConstClassPointer->*nonConstMemberFunction)(arg);
         }
      }

      virtual ~VoidOneArgMemberFunctionCaller() = default;
   };
}
