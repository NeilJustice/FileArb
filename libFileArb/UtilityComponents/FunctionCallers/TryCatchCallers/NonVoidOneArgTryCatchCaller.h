#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename ArgumentType>
   class NonVoidOneArgTryCatchCaller
   {
   public:
      virtual int TryCatchCallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         int (ClassType::*nonConstMemberFunction)(ArgumentType),
         ArgumentType argument,
         int (ClassType::*exceptionHandlerMemberFunction)(const exception&, ArgumentType)) const
      {
         try
         {
            const int exitCode = (nonConstClassPointer->*nonConstMemberFunction)(argument);
            return exitCode;
         }
         catch (const exception& ex)
         {
            const int exceptionHandlerExitCode = (nonConstClassPointer->*exceptionHandlerMemberFunction)(ex, argument);
            return exceptionHandlerExitCode;
         }
      }

      virtual ~NonVoidOneArgTryCatchCaller() = default;
   };
}
