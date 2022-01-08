#include "pch.h"
#include "libFileArb/UtilityComponents/Generators/TwoArgElementsGenerator.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(TwoArgElementsGeneratorTests, ReturnType, Arg1Type, Arg2Type)
AFACT(GenerateNElements_NIs0_DoesNotCallConstMemberFunction)
AFACT(GenerateNElements_NIs1_GeneratesAndReturns1ElementWithConstMemberFunction)
AFACT(GenerateNElements_NIs2_GeneratesAndReturns2Element2WithConstMemberFunction)
EVIDENCE

class Class
{
public:
   virtual ~Class() = default;

   virtual ReturnType ConstMemberFunction(Arg1Type, Arg2Type) const
   {
      return ReturnType{}; // LCOV_EXCL_LINE
   }
};

class ClassMock : public Metal::Mock<Class>
{
public:
   METALMOCK_NONVOID2_CONST(ReturnType, ConstMemberFunction, Arg1Type, Arg2Type)
};

Utils::TwoArgElementsGenerator<int, ClassMock, int, int> _twoArgElementsGenerator;
ClassMock _classMock;

TEST(GenerateNElements_NIs0_DoesNotCallConstMemberFunction)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   const vector<ReturnType> elements = _twoArgElementsGenerator.GenerateNElements(0, &_classMock, &Class::ConstMemberFunction, arg1, arg2);
   //
   IS_EMPTY(elements);
}

TEST(GenerateNElements_NIs1_GeneratesAndReturns1ElementWithConstMemberFunction)
{
   const ReturnType generatedElement1 = _classMock.ConstMemberFunctionMock.ReturnRandom();
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   const vector<ReturnType> elements = _twoArgElementsGenerator.GenerateNElements(1, &_classMock, &ClassMock::ConstMemberFunction, arg1, arg2);
   //
   METALMOCK(_classMock.ConstMemberFunctionMock.CalledOnceWith(arg1, arg2));
   const vector<ReturnType> expectedReturnValue =
   {
      generatedElement1
   };
   VECTORS_ARE_EQUAL(expectedReturnValue, elements);
}

TEST(GenerateNElements_NIs2_GeneratesAndReturns2Element2WithConstMemberFunction)
{
   const ReturnType generatedElement1 = ZenUnit::Random<ReturnType>();
   const ReturnType generatedElement2 = ZenUnit::Random<ReturnType>();
   _classMock.ConstMemberFunctionMock.ReturnValues(generatedElement1, generatedElement2);
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   const vector<ReturnType> elements = _twoArgElementsGenerator.GenerateNElements(2, &_classMock, &ClassMock::ConstMemberFunction, arg1, arg2);
   //
   METALMOCK(_classMock.ConstMemberFunctionMock.CalledNTimesWith(2, arg1, arg2));
   const vector<ReturnType> expectedReturnValue =
   {
      generatedElement1,
      generatedElement2
   };
   VECTORS_ARE_EQUAL(expectedReturnValue, elements);
}

RUN_TEMPLATE_TESTS(TwoArgElementsGeneratorTests, int, int, int)
