#include "pch.h"
#include "libFileArb/UtilityComponents/FunctionCallers/TryCatchCallers/NonVoidOneArgTryCatchCaller.h"

template<typename ArgumentType, typename ExceptionType>
TEMPLATE_TESTS(NonVoidOneArgTryCatchCallerTests, ArgumentType, ExceptionType)
AFACT(TryCatchCallNonConstMemberFunction_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
AFACT(TryCatchCallNonConstMemberFunction_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
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
      , exitCode(ZenUnit::Random<int>())
      , exceptionWhat(ZenUnit::Random<string>())
      , exceptionHandlerExitCode(ZenUnit::Random<int>())
   {
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

NonVoidOneArgTryCatchCaller<int, Class, ArgumentType> _nonVoidOneArgTryCatchCaller;
Class _nonConstClassInstance;

TEST(TryCatchCallNonConstMemberFunction_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   _nonConstClassInstance.doThrowException = false;
   //
   const int exitCode = _nonVoidOneArgTryCatchCaller.TryCatchCallNonConstMemberFunction(
      &_nonConstClassInstance, &Class::NonConstMemberFunction, argument, &Class::ExceptionHandlerMemberFunction);
   //
   VECTORS_ARE_EQUAL({ argument }, _nonConstClassInstance.calls);
   ARE_EQUAL(_nonConstClassInstance.exitCode, exitCode);
}

TEST(TryCatchCallNonConstMemberFunction_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   _nonConstClassInstance.doThrowException = true;
   //
   const int exitCode = _nonVoidOneArgTryCatchCaller.TryCatchCallNonConstMemberFunction(
      &_nonConstClassInstance, &Class::NonConstMemberFunction, argument, &Class::ExceptionHandlerMemberFunction);
   //
   VECTORS_ARE_EQUAL({ argument }, _nonConstClassInstance.calls);
   const ExceptionType ex(_nonConstClassInstance.exceptionWhat.c_str());
   const string exceptionClassNameAndMessage = Exception::GetClassNameAndMessage(&ex);
   const vector<pair<string, ArgumentType>> expectedExceptionHandlerCalls =
   {
      { exceptionClassNameAndMessage, argument }
   };
   VECTORS_ARE_EQUAL(expectedExceptionHandlerCalls, _nonConstClassInstance.exceptionHandlerCalls);
   ARE_EQUAL(_nonConstClassInstance.exceptionHandlerExitCode, exitCode);
}

RUN_TEMPLATE_TESTS(NonVoidOneArgTryCatchCallerTests, int, invalid_argument)
THEN_RUN_TEMPLATE_TESTS(NonVoidOneArgTryCatchCallerTests, string, runtime_error)
