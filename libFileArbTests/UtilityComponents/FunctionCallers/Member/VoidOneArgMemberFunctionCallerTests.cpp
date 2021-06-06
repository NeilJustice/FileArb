#include "pch.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ArgType>
TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, ArgType)
AFACT(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
AFACT(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
EVIDENCE

class Class
{
public:
   vector<ArgType> functionArguments;

   void NonConstMemberFunction(ArgType arg)
   {
      functionArguments.push_back(arg);
   }
};

VoidOneArgMemberFunctionCaller<Class, ArgType> _voidOneArgMemberFunctionCaller;
Class _classInstance;

TEST(CallNonConstMemberFunctionNTimes_NIs0_CallsFunctionZeroTimes)
{
   _voidOneArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(0, &Class::NonConstMemberFunction, &_classInstance, ArgType{});
   IS_EMPTY(_classInstance.functionArguments);
}

TEST(CallNonConstMemberFunctionNTimes_NIs2_CallsFunctionTwice)
{
   const ArgType arg = ZenUnit::Random<ArgType>();
   //
   _voidOneArgMemberFunctionCaller.CallNonConstMemberFunctionNTimes(2, &Class::NonConstMemberFunction, &_classInstance, arg);
   //
   vector<ArgType> expectedArgs;
   expectedArgs.push_back(arg);
   expectedArgs.push_back(arg);
   VECTORS_ARE_EQUAL(expectedArgs, _classInstance.functionArguments);
}

RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, string)
