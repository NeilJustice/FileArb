#pragma once

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller
{
public:
   virtual void CallNonConstMemberFunctionNTimes(
      size_t numberOfCalls,
      void (ClassType::*nonConstMemberFunction)(size_t, Arg1Type, Arg2Type),
      ClassType* nonConstClassPointer, Arg1Type arg1, Arg2Type arg2) const
   {
      for (size_t callIndex = 0; callIndex < numberOfCalls; ++callIndex)
      {
         (nonConstClassPointer->*nonConstMemberFunction)(callIndex, arg1, arg2);
      }
   }

   virtual void ParallelCallNonConstMemberFunctionNTimes(
      size_t numberOfCalls,
      void (ClassType::*nonConstMemberFunction)(size_t, Arg1Type, Arg2Type),
      ClassType* nonConstClassPointer, Arg1Type arg1, Arg2Type arg2) const
   {
      vector<size_t> callIndexElements(numberOfCalls);
      std::iota(callIndexElements.begin(), callIndexElements.end(), 0ull);
      const auto nonConstMemberFunctionBoundWithArg1AndArg2Bound =
         std::bind(nonConstMemberFunction, nonConstClassPointer, std::placeholders::_1, arg1, arg2);
      std::for_each(
         std::execution::par_unseq,
         callIndexElements.cbegin(),
         callIndexElements.cend(),
         nonConstMemberFunctionBoundWithArg1AndArg2Bound);
   }

   virtual ~VoidTwoArgMemberFunctionCaller() = default;
};
