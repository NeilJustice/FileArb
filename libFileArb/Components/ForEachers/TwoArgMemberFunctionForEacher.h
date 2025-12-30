#pragma once
#include <execution>

namespace Utils
{
   template<typename ClassType, typename ElementType, typename Arg2Type>
   class TwoArgMemberFunctionForEacher
   {
   public:
      virtual ~TwoArgMemberFunctionForEacher() = default;

      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type) const;
      using NonConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type);

      virtual void CallConstMemberFunctionWithEachElement(
         const vector<ElementType>& elements,
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         Arg2Type arg2) const
      {
         for (const ElementType& element : elements)
         {
            (constClassPointer->*constMemberFunction)(element, arg2);
         }
      }

      virtual void CallConstMemberFunctionWithEachElementInParallel(
         const vector<ElementType>& elements,
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         Arg2Type arg2) const
      {
         const auto boundConstMemberFunction = bind(constMemberFunction, constClassPointer, placeholders::_1, arg2);
         for_each(execution::par_unseq, elements.cbegin(), elements.cend(), boundConstMemberFunction);
      }

      virtual void CallConstMemberFunctionWithEachElementOptionallyInParallel(
         const vector<ElementType>& elements,
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         Arg2Type arg2,
         bool parallel) const
      {
         if (parallel)
         {
            CallConstMemberFunctionWithEachElementInParallel(elements, constClassPointer, constMemberFunction, arg2);
         }
         else
         {
            CallConstMemberFunctionWithEachElement(elements, constClassPointer, constMemberFunction, arg2);
         }
      }

      virtual void CallNonConstMemberFunctionWithEachElement(
         const vector<ElementType>& elements,
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         Arg2Type arg2) const
      {
         for (const ElementType& element : elements)
         {
            (nonConstClassPointer->*nonConstMemberFunction)(element, arg2);
         }
      }

      virtual void CallNonConstMemberFunctionWithEachElementInParallel(
         const vector<ElementType>& elements,
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         Arg2Type arg2) const
      {
         const auto boundNonConstMemberFunction = bind(nonConstMemberFunction, nonConstClassPointer, placeholders::_1, arg2);
         for_each(execution::par_unseq, elements.cbegin(), elements.cend(), boundNonConstMemberFunction);
      }

      virtual void CallNonConstMemberFunctionWithEachElementOptionallyInParallel(
         const vector<ElementType>& elements,
         ClassType* nonConstClassPointer,
         NonConstMemberFunctionType nonConstMemberFunction,
         Arg2Type arg2,
         bool parallel) const
      {
         if (parallel)
         {
            CallNonConstMemberFunctionWithEachElementInParallel(elements, nonConstClassPointer, nonConstMemberFunction, arg2);
         }
         else
         {
            CallNonConstMemberFunctionWithEachElement(elements, nonConstClassPointer, nonConstMemberFunction, arg2);
         }
      }
   };
}
