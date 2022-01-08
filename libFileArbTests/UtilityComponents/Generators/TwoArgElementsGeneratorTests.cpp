#include "pch.h"
#include "libFileArb/UtilityComponents/Generators/TwoArgElementsGenerator.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(TwoArgElementsGeneratorTests, ReturnType, Arg1Type, Arg2Type)
AFACT(GenerateNElements_NIs0_DoesNotCallConstMemberFunction)
EVIDENCE

class Class
{
public:
   ReturnType ConstMemberFunction(Arg1Type, Arg2Type) const
   {
      return ReturnType{};
   }
};

Utils::TwoArgElementsGenerator<int, Class, int, int> _twoArgElementsGenerator;
const Class _constClassInstance;

TEST(GenerateNElements_NIs0_DoesNotCallConstMemberFunction)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   const vector<ReturnType> elements = _twoArgElementsGenerator.GenerateNElements(0, &_constClassInstance, &Class::ConstMemberFunction, arg1, arg2);
   //
   IS_EMPTY(elements);
}

RUN_TEMPLATE_TESTS(TwoArgElementsGeneratorTests, int, int, int)
