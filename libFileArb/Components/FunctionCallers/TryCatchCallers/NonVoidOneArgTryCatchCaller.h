#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename ArgumentType>
   class NonVoidOneArgTryCatchCaller
   {
   public:
      using NonConstMemberFunctionType = int (ClassType::*)(ArgumentType);
      using ExceptionHandlerFunctionType = int (ClassType::*)(const exception&, ArgumentType);

      virtual int TryCatchCallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         ArgumentType argument,
         ExceptionHandlerFunctionType exceptionHandlerMemberFunction) const
      {
         try
         {
            int exitCode = (nonConstClassPointer->*nonConstMemberFunction)(argument);
            return exitCode;
         }
         catch (const exception& ex)
         {
            int exceptionHandlerExitCode = (nonConstClassPointer->*exceptionHandlerMemberFunction)(ex, argument);
            return exceptionHandlerExitCode;
         }
      }

      virtual ~NonVoidOneArgTryCatchCaller() = default;
   };
}
