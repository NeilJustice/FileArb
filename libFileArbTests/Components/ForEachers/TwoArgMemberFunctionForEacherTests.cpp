#include "pch.h"
#include "libFileArb/Components/ForEachers/TwoArgMemberFunctionForEacher.h"

template<typename ClassType, typename ElementType, typename Arg2Type>
class TwoArgMemberFunctionForEacherSelfMocked : public Metal::Mock<Utils::TwoArgMemberFunctionForEacher<ClassType, ElementType, Arg2Type>>
{
public:
   using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type) const;
   using NonConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type);

   METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElement, const vector<ElementType>&, const ClassType*, ConstMemberFunctionType, Arg2Type)
   METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElementInParallel, const vector<ElementType>&, const ClassType*, ConstMemberFunctionType, Arg2Type)

   METALMOCK_VOID4_CONST(CallNonConstMemberFunctionWithEachElement, const vector<ElementType>&, ClassType*, NonConstMemberFunctionType, Arg2Type)
   METALMOCK_VOID4_CONST(CallNonConstMemberFunctionWithEachElementInParallel, const vector<ElementType>&, ClassType*, NonConstMemberFunctionType, Arg2Type)
};

template<typename ElementType, typename Arg2Type>
TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, ElementType, Arg2Type)
AFACT(CallConstMemberFunctionWithEachElement_EmptyCollection_DoesNotCallFunction)
AFACT(CallConstMemberFunctionWithEachElement_OneItemCollection_CallsThisPointerBoundFunctionOnce)
AFACT(CallConstMemberFunctionWithEachElement_TwoItemCollection_CallsThisPointerBoundFunctionTwice)
AFACT(CallConstMemberFunctionWithEachElementInParallel_EmptyCollection_DoesNotCallConstMemberFunction)
AFACT(CallConstMemberFunctionWithEachElementInParallel_TwoItemCollection_CallsConstMemberFunctionWithEachElementInParallel)
AFACT(CallConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsFalse_CallsConstMemberFunctionWithEachElementSequentially)
AFACT(CallConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsTrue_CallsConstMemberFunctionWithEachElementInParallel)
AFACT(CallNonConstMemberFunctionWithEachElement_EmptyCollection_DoesNotCallFunction)
AFACT(CallNonConstMemberFunctionWithEachElement_OneItemCollection_CallsThisPointerBoundFunctionOnce)
AFACT(CallNonConstMemberFunctionWithEachElement_TwoItemCollection_CallsThisPointerBoundFunctionTwice)
AFACT(CallNonConstMemberFunctionWithEachElementInParallel_EmptyCollection_DoesNotCallNonConstMemberFunction)
AFACT(CallNonConstMemberFunctionWithEachElementInParallel_TwoItemCollection_CallsNonConstMemberFunctionWithEachElementInParallel)
AFACT(CallNonConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsFalse_CallsNonConstMemberFunctionWithEachElementSequentially)
AFACT(CallNonConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsTrue_CallsNonConstMemberFunctionWithEachElementInParallel)
AFACT(ConstAndNonConstTwoArgFunction_CodeCoverage)
EVIDENCE

#ifdef __linux__
TwoArgMemberFunctionForEacherTests()
{
}
#endif

class Class
{
public:
   mutable vector<pair<ElementType, Arg2Type>> functionCalls;
   mutable mutex functionCallsMutex;

   virtual void ConstMemberFunction(const ElementType& element, Arg2Type arg2) const
   {
      scoped_lock<mutex> functionCallsLock(functionCallsMutex);
      functionCalls.emplace_back(element, arg2);
   }

   virtual void NonConstMemberFunction(const ElementType& element, Arg2Type arg2)
   {
      scoped_lock<mutex> functionCallsLock(functionCallsMutex);
      functionCalls.emplace_back(element, arg2);
   }

   virtual ~Class() = default;
};

class ClassMock : public Metal::Mock<Class>
{
public:
   METALMOCK_VOID2_CONST(ConstMemberFunction, const ElementType&, Arg2Type)
   METALMOCK_VOID2(NonConstMemberFunction, const ElementType&, Arg2Type)
};

Utils::TwoArgMemberFunctionForEacher<Class, ElementType, Arg2Type> _twoArgMemberFunctionForEacher;
TwoArgMemberFunctionForEacherSelfMocked<Class, ElementType, Arg2Type> _twoArgMemberFunctionForEacherSelfMocked;
ClassMock _classMock;
const Class _constClassInstance;
Class _nonConstClassInstance;

TEST(CallConstMemberFunctionWithEachElement_EmptyCollection_DoesNotCallFunction)
{
   const vector<ElementType> elements{};
   const ClassMock classInstance{};
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      elements, &classInstance, &Class::ConstMemberFunction, arg2);
}

TEST(CallConstMemberFunctionWithEachElement_OneItemCollection_CallsThisPointerBoundFunctionOnce)
{
   const vector<ElementType> elements = { ZenUnit::Random<ElementType>() };
   _classMock.ConstMemberFunctionMock.Expect();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      elements, &_classMock, &Class::ConstMemberFunction, arg2);
   //
   _classMock.ConstMemberFunctionMock.CalledOnceWith(elements[0], arg2);
}

TEST(CallConstMemberFunctionWithEachElement_TwoItemCollection_CallsThisPointerBoundFunctionTwice)
{
   const vector<ElementType> elements = { ZenUnit::Random<ElementType>(), ZenUnit::Random<ElementType>() };
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   _classMock.ConstMemberFunctionMock.Expect();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      elements, &_classMock, &Class::ConstMemberFunction, arg2);
   //
   METALMOCK(_classMock.ConstMemberFunctionMock.CalledNTimes(2));
   METALMOCKTHEN(_classMock.ConstMemberFunctionMock.CalledWith(elements[0], arg2)).Then(
   METALMOCKTHEN(_classMock.ConstMemberFunctionMock.CalledWith(elements[1], arg2)));
}

TEST(CallConstMemberFunctionWithEachElementInParallel_EmptyCollection_DoesNotCallConstMemberFunction)
{
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElementInParallel(
      {}, &_constClassInstance, &Class::ConstMemberFunction, arg2);
}

TEST(CallConstMemberFunctionWithEachElementInParallel_TwoItemCollection_CallsConstMemberFunctionWithEachElementInParallel)
{
   const vector<ElementType> elements =
   {
      ZenUnit::Random<ElementType>(),
      ZenUnit::Random<ElementType>()
   };
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElementInParallel(
      elements, &_constClassInstance, &Class::ConstMemberFunction, arg2);
   //
   const vector<pair<ElementType, Arg2Type>> expectedFunctionCalls =
   {
      { elements[0], arg2 },
      { elements[1], arg2 }
   };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFunctionCalls, _constClassInstance.functionCalls);
}

TEST(CallConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsFalse_CallsConstMemberFunctionWithEachElementSequentially)
{
   _twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementMock.Expect();
   const vector<ElementType> elements = ZenUnit::RandomVector<ElementType>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementOptionallyInParallel(
      elements, &_constClassInstance, &Class::ConstMemberFunction, arg2, false);
   //
   METALMOCK(_twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      elements, &_constClassInstance, &Class::ConstMemberFunction, arg2));
}

TEST(CallConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsTrue_CallsConstMemberFunctionWithEachElementInParallel)
{
   _twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementInParallelMock.Expect();
   const vector<ElementType> elements = ZenUnit::RandomVector<ElementType>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementOptionallyInParallel(
      elements, &_constClassInstance, &Class::ConstMemberFunction, arg2, true);
   //
   METALMOCK(_twoArgMemberFunctionForEacherSelfMocked.CallConstMemberFunctionWithEachElementInParallelMock.CalledOnceWith(
      elements, &_constClassInstance, &Class::ConstMemberFunction, arg2));
}

TEST(CallNonConstMemberFunctionWithEachElement_EmptyCollection_DoesNotCallFunction)
{
   const vector<ElementType> elements{};
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallNonConstMemberFunctionWithEachElement(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2);
}

TEST(CallNonConstMemberFunctionWithEachElement_OneItemCollection_CallsThisPointerBoundFunctionOnce)
{
   const vector<ElementType> elements =
   {
      ZenUnit::Random<ElementType>()
   };
   _classMock.NonConstMemberFunctionMock.Expect();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallNonConstMemberFunctionWithEachElement(
      elements, &_classMock, &Class::NonConstMemberFunction, arg2);
   //
   _classMock.NonConstMemberFunctionMock.CalledOnceWith(elements[0], arg2);
}

TEST(CallNonConstMemberFunctionWithEachElement_TwoItemCollection_CallsThisPointerBoundFunctionTwice)
{
   const vector<ElementType> elements =
   {
      ZenUnit::Random<ElementType>(),
      ZenUnit::Random<ElementType>()
   };
   _classMock.NonConstMemberFunctionMock.Expect();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallNonConstMemberFunctionWithEachElement(
      elements, &_classMock, &Class::NonConstMemberFunction, arg2);
   //
   METALMOCK(_classMock.NonConstMemberFunctionMock.CalledNTimes(2));
   METALMOCKTHEN(_classMock.NonConstMemberFunctionMock.CalledWith(elements[0], arg2)).Then(
   METALMOCKTHEN(_classMock.NonConstMemberFunctionMock.CalledWith(elements[1], arg2)));
}

TEST(CallNonConstMemberFunctionWithEachElementInParallel_EmptyCollection_DoesNotCallNonConstMemberFunction)
{
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallNonConstMemberFunctionWithEachElementInParallel(
      {}, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2);
}

TEST(CallNonConstMemberFunctionWithEachElementInParallel_TwoItemCollection_CallsNonConstMemberFunctionWithEachElementInParallel)
{
   const ElementType element1 = ZenUnit::Random<ElementType>();
   const ElementType element2 = ZenUnit::Random<ElementType>();
   const vector<ElementType> elements =
   {
      element1,
      element2
   };
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallNonConstMemberFunctionWithEachElementInParallel(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2);
   //
   const vector<pair<ElementType, Arg2Type>> expectedFunctionCalls =
   {
      { element1, arg2 },
      { element2, arg2 }
   };
   INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedFunctionCalls, _nonConstClassInstance.functionCalls);
}

TEST(CallNonConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsFalse_CallsNonConstMemberFunctionWithEachElementSequentially)
{
   _twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementMock.Expect();
   const vector<ElementType> elements = ZenUnit::RandomVector<ElementType>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementOptionallyInParallel(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2, false);
   //
   METALMOCK(_twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementMock.CalledOnceWith(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2));
}

TEST(CallNonConstMemberFunctionWithEachElementOptionallyInParallel_ParallelIsTrue_CallsNonConstMemberFunctionWithEachElementInParallel)
{
   _twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementInParallelMock.Expect();
   const vector<ElementType> elements = ZenUnit::RandomVector<ElementType>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementOptionallyInParallel(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2, true);
   //
   METALMOCK(_twoArgMemberFunctionForEacherSelfMocked.CallNonConstMemberFunctionWithEachElementInParallelMock.CalledOnceWith(
      elements, &_nonConstClassInstance, &Class::NonConstMemberFunction, arg2));
}

TEST(ConstAndNonConstTwoArgFunction_CodeCoverage)
{
   Class classType{};
   classType.ConstMemberFunction(ElementType{}, Arg2Type{});
   classType.NonConstMemberFunction(ElementType{}, Arg2Type{});
};

RUN_TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, int, int)
THEN_RUN_TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, double, char)
