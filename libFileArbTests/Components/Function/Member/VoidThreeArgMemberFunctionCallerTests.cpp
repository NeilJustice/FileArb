#include "pch.h"
#include "libFileArb/Components/Function/Member/VoidThreeArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, Arg1Type, Arg2Type, Arg3Type)
AFACT(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
EVIDENCE

struct Class
{
   vector<tuple<size_t, Arg1Type, Arg2Type, Arg3Type>> functionArguments;

   void NonConstTwoArgMemberFunction(size_t callIndex, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
   {
      functionArguments.push_back(make_tuple(callIndex, arg1, arg2, arg3));
   }
};

Utils::VoidThreeArgMemberFunctionCaller<Class, Arg1Type, Arg2Type, Arg3Type> _voidThreeArgMemberFunctionCaller;
Class _classInstance;

TEST(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidThreeArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(
      0, &Class::NonConstTwoArgMemberFunction, &_classInstance, Arg1Type{}, Arg2Type{}, Arg3Type{});
   IS_EMPTY(_classInstance.functionArguments);
}

TEST(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   const Arg3Type arg3 = ZenUnit::Random<Arg3Type>();
   //
   _voidThreeArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(
      2, &Class::NonConstTwoArgMemberFunction, &_classInstance, arg1, arg2, arg3);
   //
   vector<tuple<size_t, Arg1Type, Arg2Type, Arg3Type>> expectedFunctionArguments;
   expectedFunctionArguments.push_back(make_tuple(0, arg1, arg2, arg3));
   expectedFunctionArguments.push_back(make_tuple(1, arg1, arg2, arg3));
   VECTORS_ARE_EQUAL(expectedFunctionArguments, _classInstance.functionArguments);
}

RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, int, double, char)
THEN_RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, string, char, int)
