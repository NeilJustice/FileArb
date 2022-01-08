#pragma once

namespace Utils
{
   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class TwoArgElementsGenerator
   {
   public:
      virtual ~TwoArgElementsGenerator() = default;

      using ConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type) const;

      virtual vector<ReturnType> GenerateNElements(
         size_t n,
         const ClassType* constClassInstance,
         ConstMemberFunctionType constMemberFunction,
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         vector<ReturnType> elements(n);
         for (size_t i = 0; i < n; ++i)
         {
            elements[i] = (constClassInstance->*constMemberFunction)(arg1, arg2);
         }
         return elements;
      }
   };
}
