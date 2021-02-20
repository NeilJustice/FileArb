#include "pch.h"
#include "libFileArb/UtilityComponents/Exception/TryCatchCaller.h"

template<typename ArgumentType, typename ExceptionType>
TEMPLATE_TESTS(TryCatchCallerTests, ArgumentType, ExceptionType)
AFACT(TryCatchCall_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
AFACT(TryCatchCall_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
EVIDENCE

class Class
{
public:
   bool doThrowException = false;
   vector<ArgumentType> calls;
   int exitCode = 0;

   string exceptionWhat;
   vector<pair<string, ArgumentType>> exceptionHandlerCalls;
   int exceptionHandlerExitCode = 0;

   Class()
      : doThrowException(false)
   {
      exitCode = ZenUnit::Random<int>();
      exceptionWhat = ZenUnit::Random<string>();
      exceptionHandlerExitCode = ZenUnit::Random<int>();
   }

   int NonConstMemberFunction(ArgumentType argument)
   {
      calls.push_back(argument);
      if (doThrowException)
      {
         throw ExceptionType(exceptionWhat.c_str());
      }
      return exitCode;
   }

   int ExceptionHandlerMemberFunction(const exception& ex, ArgumentType argument)
   {
      const string exceptionClassNameAndMessage = Exception::GetClassNameAndMessage(&ex);
      exceptionHandlerCalls.emplace_back(exceptionClassNameAndMessage, argument);
      return exceptionHandlerExitCode;
   }
};

Class classInstance;
TryCatchCaller<Class, ArgumentType> _tryCatchCaller;

TEST(TryCatchCall_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   classInstance.doThrowException = false;
   //
   const int exitCode = _tryCatchCaller.TryCatchCall(
      &classInstance, &Class::NonConstMemberFunction, argument, &Class::ExceptionHandlerMemberFunction);
   //
   VECTORS_ARE_EQUAL({ argument }, classInstance.calls);
   ARE_EQUAL(classInstance.exitCode, exitCode);
}

TEST(TryCatchCall_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   classInstance.doThrowException = true;
   //
   const int exitCode = _tryCatchCaller.TryCatchCall(
      &classInstance, &Class::NonConstMemberFunction, argument, &Class::ExceptionHandlerMemberFunction);
   //
   VECTORS_ARE_EQUAL({ argument }, classInstance.calls);
   const ExceptionType ex(classInstance.exceptionWhat.c_str());
   const string exceptionClassNameAndMessage = Exception::GetClassNameAndMessage(&ex);
   const vector<pair<string, ArgumentType>> expectedExceptionHandlerCalls =
   {
      { exceptionClassNameAndMessage, argument }
   };
   VECTORS_ARE_EQUAL(expectedExceptionHandlerCalls, classInstance.exceptionHandlerCalls);
   ARE_EQUAL(classInstance.exceptionHandlerExitCode, exitCode);
}

RUN_TEMPLATE_TESTS(TryCatchCallerTests, int, invalid_argument)
THEN_RUN_TEMPLATE_TESTS(TryCatchCallerTests, string, runtime_error)
