#include "pch.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, Arg1Type, Arg2Type)
AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
AFACT(CallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(CallConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
AFACT(ParallelCallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(ParallelCallConstMemberFunctionNTimes_NIs2_CallsFunctionTwiceInParallel)
EVIDENCE

#if defined __linux__ || defined __APPLE__
VoidTwoArgMemberFunctionCallerTests()
{
}
#endif

class TestingClass
{
public:
   mutable vector<pair<Arg1Type, Arg2Type>> functionCalls;
   mutable vector<tuple<size_t, Arg1Type, Arg2Type>> functionCallsWithCallIndices;

   void ConstMemberFunction(Arg1Type arg1, Arg2Type arg2) const
   {
      functionCalls.emplace_back(arg1, arg2);
   }

   void NonConstMemberFunction(Arg1Type arg1, Arg2Type arg2)
   {
      functionCalls.emplace_back(arg1, arg2);
   }

   void ConstMemberFunctionWithCallIndex(size_t callIndex, Arg1Type arg1, Arg2Type arg2) const
   {
      functionCallsWithCallIndices[callIndex] = make_tuple(callIndex, arg1, arg2);
   }
};

const Utils::VoidTwoArgMemberFunctionCaller<TestingClass, Arg1Type, Arg2Type> _voidTwoArgMemberFunctionCaller;
const TestingClass _constClassInstance;
TestingClass _nonConstClassInstance;

TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
{
   _voidTwoArgMemberFunctionCaller.CallConstMemberFunction(
      &_constClassInstance, &TestingClass::ConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 });

   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _constClassInstance.functionCalls);


   _voidTwoArgMemberFunctionCaller.CallConstMemberFunction(
      &_constClassInstance, &TestingClass::ConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _constClassInstance.functionCalls);
}

TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
{
   _voidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
      &_nonConstClassInstance, &TestingClass::NonConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 });
   //
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _nonConstClassInstance.functionCalls);


   _voidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
      &_nonConstClassInstance, &TestingClass::NonConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _nonConstClassInstance.functionCalls);
}

TEST(CallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidTwoArgMemberFunctionCaller.CallConstMemberFunctionNTimes(
      0ULL, &_constClassInstance, &TestingClass::ConstMemberFunctionWithCallIndex, Arg1Type{}, Arg2Type{});
   IS_EMPTY(_constClassInstance.functionCallsWithCallIndices);
}

TEST(CallConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
{
   _constClassInstance.functionCallsWithCallIndices.resize(2);
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _voidTwoArgMemberFunctionCaller.CallConstMemberFunctionNTimes(
      2ULL, &_constClassInstance, &TestingClass::ConstMemberFunctionWithCallIndex, arg1, arg2);
   //
   const vector<tuple<size_t, Arg1Type, Arg2Type>> expectedFunctionArguments =
   {
      { make_tuple(0ULL, arg1, arg2) },
      { make_tuple(1ULL, arg1, arg2) }
   };
   VECTORS_ARE_EQUAL(expectedFunctionArguments, _constClassInstance.functionCallsWithCallIndices);
}

TEST(ParallelCallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidTwoArgMemberFunctionCaller.ParallelCallConstMemberFunctionNTimes(
      0ULL, &_constClassInstance, &TestingClass::ConstMemberFunctionWithCallIndex, Arg1Type{}, Arg2Type{});
   IS_EMPTY(_nonConstClassInstance.functionCallsWithCallIndices);
}

TEST(ParallelCallConstMemberFunctionNTimes_NIs2_CallsFunctionTwiceInParallel)
{
   _constClassInstance.functionCallsWithCallIndices.resize(2);
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _voidTwoArgMemberFunctionCaller.ParallelCallConstMemberFunctionNTimes(
      2ULL, &_constClassInstance, &TestingClass::ConstMemberFunctionWithCallIndex, arg1, arg2);
   //
   vector<tuple<size_t, Arg1Type, Arg2Type>> expectedFunctionArguments;
   expectedFunctionArguments.push_back(make_tuple(0ULL, arg1, arg2));
   expectedFunctionArguments.push_back(make_tuple(1ULL, arg1, arg2));
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFunctionArguments, _constClassInstance.functionCallsWithCallIndices);
}

RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, size_t)
THEN_RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, string, string)
