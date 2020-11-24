#pragma once

template<typename ClassType, typename ArgumentType>
class TryCatchCaller
{
public:
   virtual int TryCatchCall(
      ClassType* classPointer,
      int (ClassType::* nonConstMemberFunction)(ArgumentType),
      ArgumentType argument,
      int (ClassType::* exceptionHandlerMemberFunction)(const exception&, ArgumentType)) const
   {
      try
      {
         const int exitCode = (classPointer->*nonConstMemberFunction)(argument);
         return exitCode;
      }
      catch (const exception& ex)
      {
         const int exceptionHandlerExitCode = (classPointer->*exceptionHandlerMemberFunction)(ex, argument);
         return exceptionHandlerExitCode;
      }
   }

   virtual ~TryCatchCaller() = default;
};
