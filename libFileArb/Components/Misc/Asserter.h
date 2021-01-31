#pragma once

class Asserter
{
public:
   virtual void ThrowIfIntsNotEqual(int expectedInt, int actualInt, string_view message) const;
   virtual void ThrowIfSizeTValuesNotEqual(size_t expectedSizeT, size_t actualSizeT, string_view message) const;
   virtual ~Asserter() = default;
};
