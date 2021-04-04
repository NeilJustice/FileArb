#include "pch.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, Arg1Type, Arg2Type)
AFACT(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
AFACT(ParallelCallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(ParallelCallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwiceInParallel)
EVIDENCE

struct Class
{
   vector<tuple<size_t, Arg1Type, Arg2Type>> functionArguments;

   void NonConstTwoArgMemberFunction(size_t callIndex, Arg1Type arg1, Arg2Type arg2)
   {
      functionArguments[callIndex] = make_tuple(callIndex, arg1, arg2);
   }
};

VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> _voidTwoArgMemberFunctionCaller;
Class _classInstance;

TEST(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidTwoArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(
      0ULL, &Class::NonConstTwoArgMemberFunction, &_classInstance, Arg1Type{}, Arg2Type{});
   IS_EMPTY(_classInstance.functionArguments);
}

TEST(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
{
   _classInstance.functionArguments.resize(2);
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _voidTwoArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(
      2ull, &Class::NonConstTwoArgMemberFunction, &_classInstance, arg1, arg2);
   //
   vector<tuple<size_t, Arg1Type, Arg2Type>> expectedFunctionArguments;
   expectedFunctionArguments.push_back(make_tuple(0ull, arg1, arg2));
   expectedFunctionArguments.push_back(make_tuple(1ull, arg1, arg2));
   VECTORS_ARE_EQUAL(expectedFunctionArguments, _classInstance.functionArguments);
}

TEST(ParallelCallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidTwoArgMemberFunctionCaller.ParallelCallNonConstMemberFunctionNTimes(
      0ULL, &Class::NonConstTwoArgMemberFunction, &_classInstance, Arg1Type{}, Arg2Type{});
   IS_EMPTY(_classInstance.functionArguments);
}

TEST(ParallelCallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwiceInParallel)
{
   _classInstance.functionArguments.resize(2);
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _voidTwoArgMemberFunctionCaller.ParallelCallNonConstMemberFunctionNTimes(
      2ULL, &Class::NonConstTwoArgMemberFunction, &_classInstance, arg1, arg2);
   //
   vector<tuple<size_t, Arg1Type, Arg2Type>> expectedFunctionArguments;
   expectedFunctionArguments.push_back(make_tuple(0ull, arg1, arg2));
   expectedFunctionArguments.push_back(make_tuple(1ull, arg1, arg2));
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFunctionArguments, _classInstance.functionArguments);
}

RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, size_t)
THEN_RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, string, string)
