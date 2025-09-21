#pragma once
#include "libFileArb/Components/ForEachers/TwoArgMemberFunctionForEacher.h"

namespace Utils
{
   template<typename ClassType, typename ElementType, typename Arg2Type>
   class TwoArgMemberFunctionForEacherMock : public Metal::Mock<TwoArgMemberFunctionForEacher<ClassType, ElementType, Arg2Type>>
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type) const;
      using NonConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type);

      METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElement, const vector<ElementType>&, const ClassType*, ConstMemberFunctionType, Arg2Type)
      METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElementInParallel, const vector<ElementType>&, const ClassType*, ConstMemberFunctionType, Arg2Type)
      METALMOCK_VOID5_CONST(CallConstMemberFunctionWithEachElementOptionallyInParallel,
         const vector<ElementType>&,
         const ClassType*,
         ConstMemberFunctionType,
         Arg2Type,
         bool)

      METALMOCK_VOID4_CONST(CallNonConstMemberFunctionWithEachElement, const vector<ElementType>&, ClassType*, NonConstMemberFunctionType, Arg2Type)
      METALMOCK_VOID4_CONST(CallNonConstMemberFunctionWithEachElementInParallel, const vector<ElementType>&, ClassType*, NonConstMemberFunctionType, Arg2Type)
      METALMOCK_VOID5_CONST(CallNonConstMemberFunctionWithEachElementOptionallyInParallel,
         const vector<ElementType>&,
         ClassType*,
         NonConstMemberFunctionType,
         Arg2Type,
         bool)
   };
}
