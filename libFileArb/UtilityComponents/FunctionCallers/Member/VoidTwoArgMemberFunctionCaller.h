#pragma once
#pragma once
#if defined __GNUG__ && !defined __clang__
#include <parallel/algorithm>
#include <parallel/settings.h>
#endif

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller
   {
   public:
      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer,
         void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
         Arg1Type arg1, Arg2Type arg2) const
      {
         (constClassPointer->*constMemberFunction)(arg1, arg2);
      }

      virtual void CallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         void (ClassType::*constMemberFunction)(Arg1Type, Arg2Type),
         Arg1Type arg1, Arg2Type arg2) const
      {
         (nonConstClassPointer->*constMemberFunction)(arg1, arg2);
      }

      virtual void CallConstMemberFunctionNTimes(
         size_t numberOfCalls,
         const ClassType* constClassPointer,
         void (ClassType::*constMemberFunction)(size_t, Arg1Type, Arg2Type) const,
         Arg1Type arg1, Arg2Type arg2) const
      {
         for (size_t callIndex = 0; callIndex < numberOfCalls; ++callIndex)
         {
            (constClassPointer->*constMemberFunction)(callIndex, arg1, arg2);
         }
      }

      virtual void ParallelCallConstMemberFunctionNTimes(
         size_t numberOfCalls,
         const ClassType* constClassPointer,
         void (ClassType::*constMemberFunction)(size_t, Arg1Type, Arg2Type) const,
         Arg1Type arg1, Arg2Type arg2) const
      {
         vector<size_t> callIndexElements(numberOfCalls);
         std::iota(callIndexElements.begin(), callIndexElements.end(), 0ULL);
   #if defined __GNUG__ && !defined __clang__
         __gnu_parallel::_Settings settings;
         settings.algorithm_strategy = __gnu_parallel::force_parallel;
         __gnu_parallel::_Settings::set(settings);
         const auto constMemberFunctionBoundWithArg1AndArg2Bound =
            std::bind(constMemberFunction, constClassPointer, std::placeholders::_1, arg1, arg2);
         __gnu_parallel::for_each(callIndexElements.cbegin(), callIndexElements.cend(),
            constMemberFunctionBoundWithArg1AndArg2Bound);
   #else
         const auto constMemberFunctionBoundWithArg1AndArg2Bound =
            std::bind(constMemberFunction, constClassPointer, std::placeholders::_1, arg1, arg2);
         std::for_each(std::execution::par_unseq, callIndexElements.cbegin(), callIndexElements.cend(),
            constMemberFunctionBoundWithArg1AndArg2Bound);
   #endif
      }

      virtual ~VoidTwoArgMemberFunctionCaller() = default;
   };
}
