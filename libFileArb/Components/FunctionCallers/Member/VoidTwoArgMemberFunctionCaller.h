#pragma once
#include <execution>

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller
   {
   public:
      virtual ~VoidTwoArgMemberFunctionCaller() = default;

      using ConstMemberFunctionType = void(ClassType::*)(Arg1Type, Arg2Type) const;
      using NonConstMemberFunctionType = void(ClassType::*)(Arg1Type, Arg2Type);
      using ConstMemberFunctionWithIndexType = void(ClassType::*)(size_t, Arg1Type, Arg2Type) const;

      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         Arg1Type arg1, Arg2Type arg2) const
      {
         (constClassPointer->*constMemberFunction)(arg1, arg2);
      }

      virtual void CallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         Arg1Type arg1, Arg2Type arg2) const
      {
         (nonConstClassPointer->*nonConstMemberFunction)(arg1, arg2);
      }

      virtual void CallConstMemberFunctionNTimes(
         size_t numberOfCalls,
         const ClassType* constClassPointer,
         ConstMemberFunctionWithIndexType constMemberFunction,
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
         ConstMemberFunctionWithIndexType constMemberFunction,
         Arg1Type arg1, Arg2Type arg2) const
      {
         vector<size_t> callIndexElements(numberOfCalls);
         std::iota(callIndexElements.begin(), callIndexElements.end(), 0ULL);
         const auto constMemberFunctionBoundWithArg1AndArg2Bound = std::bind(constMemberFunction, constClassPointer, std::placeholders::_1, arg1, arg2);
         for_each(std::execution::par_unseq, callIndexElements.cbegin(), callIndexElements.cend(), constMemberFunctionBoundWithArg1AndArg2Bound);
      }
   };
}
