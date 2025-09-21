#include "pch.h"
#include "libFileArb/Components/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, Arg1Type, Arg2Type, Arg3Type)
AFACT(CallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(CallConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
EVIDENCE

#if defined __linux__
VoidThreeArgMemberFunctionCallerTests()
{
}
#endif

class TestingClass
{
public:
   mutable vector<tuple<size_t, Arg1Type, Arg2Type, Arg3Type>> functionArguments;

   void ConstTwoArgMemberFunction(size_t callIndex, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      functionArguments.push_back(make_tuple(callIndex, arg1, arg2, arg3));
   }
};

const Utils::VoidThreeArgMemberFunctionCaller<TestingClass, Arg1Type, Arg2Type, Arg3Type> _voidThreeArgMemberFunctionCaller;
const TestingClass _constClassInstance;

TEST(CallConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidThreeArgMemberFunctionCaller.CallConstMemberFunctionNTimes(
      0ULL, &_constClassInstance, &TestingClass::ConstTwoArgMemberFunction, Arg1Type{}, Arg2Type{}, Arg3Type{});
   IS_EMPTY(_constClassInstance.functionArguments);
}

TEST(CallConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   const Arg3Type arg3 = ZenUnit::Random<Arg3Type>();
   //
   _voidThreeArgMemberFunctionCaller.CallConstMemberFunctionNTimes(
      2ULL, &_constClassInstance, &TestingClass::ConstTwoArgMemberFunction, arg1, arg2, arg3);
   //
   const vector<tuple<size_t, Arg1Type, Arg2Type, Arg3Type>> expectedFunctionArguments =
   {
      { make_tuple(0ULL, arg1, arg2, arg3) },
      { make_tuple(1ULL, arg1, arg2, arg3) }
   };
   VECTORS_ARE_EQUAL(expectedFunctionArguments, _constClassInstance.functionArguments);
}

RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, int, double, char)
THEN_RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, string, char, int)
