#include "pch.h"
#include "libFileArb/UtilityComponents/FunctionCallers/Member/VoidFourArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
TEMPLATE_TESTS(VoidFourArgMemberFunctionCallerTests, Arg1Type, Arg2Type, Arg3Type, Arg4Type)
AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
EVIDENCE

class Class
{
public:
   mutable vector<tuple<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> calls;

   void ConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const
   {
      calls.emplace_back(arg1, arg2, arg3, arg4);
   }

   void NonConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
   {
      calls.emplace_back(arg1, arg2, arg3, arg4);
   }
};

TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
{
   Class classInstance{};
   VoidFourArgMemberFunctionCaller<Class, Arg1Type, Arg2Type, Arg3Type, Arg4Type> voidFourArgMemberFunctionCaller;
   IS_EMPTY(classInstance.calls);
   //
   voidFourArgMemberFunctionCaller.CallConstMemberFunction(
      &classInstance, &Class::ConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 }, Arg4Type{ 4 });
   //
   vector<tuple<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> expectedCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 }, Arg4Type{ 4 } } };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);


   voidFourArgMemberFunctionCaller.CallConstMemberFunction(
      &classInstance, &Class::ConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 }, Arg4Type{ 6 });
   //
   expectedCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 }, Arg4Type{ 6 });
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
}

TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
{
   Class classInstance{};
   VoidFourArgMemberFunctionCaller<Class, Arg1Type, Arg2Type, Arg3Type, Arg4Type> voidFourArgMemberFunctionCaller;
   IS_EMPTY(classInstance.calls);
   //
   voidFourArgMemberFunctionCaller.CallNonConstMemberFunction(
      &classInstance, &Class::NonConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 }, Arg4Type{ 4 });
   //
   vector<tuple<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> expectedCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 }, Arg4Type{ 4 } } };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);


   voidFourArgMemberFunctionCaller.CallNonConstMemberFunction(
      &classInstance, &Class::NonConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 }, Arg4Type{ 6 });
   //
   expectedCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 }, Arg4Type{ 6 });
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
}

RUN_TEMPLATE_TESTS(VoidFourArgMemberFunctionCallerTests, int, char, unsigned, int)
THEN_RUN_TEMPLATE_TESTS(VoidFourArgMemberFunctionCallerTests, int, unsigned long long, char, int)
