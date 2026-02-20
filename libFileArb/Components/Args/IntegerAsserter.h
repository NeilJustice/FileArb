#pragma once
class IntegerAsserterTests;

namespace Utils
{
   class IntegerAsserter
   {
      friend class ::IntegerAsserterTests;
   public:
      virtual ~IntegerAsserter() = default;

      virtual void ThrowIfIntsAreNotEqual(
         int expectedInt, int actualInt,
         string_view argsText,
         string_view callingFunctionName) const;
   };
}
