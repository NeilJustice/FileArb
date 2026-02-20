#include "pch.h"
#include "libFileArb/Components/Vector/VectorHelper.h"

TESTS(VectorHelperTests)
AFACT(FromArgcArgv_ReturnsArgsVector)
AFACT(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
AFACT(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
FACTS(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator)
EVIDENCE

Utils::VectorHelper _vectorHelper;

TEST(FromArgcArgv_ReturnsArgsVector)
{
   const array<const char*, 1> chars1 { "ExePath" };
   const vector<string> expectedArgsA { "ExePath" };
   VECTORS_ARE_EQUAL(expectedArgsA, _vectorHelper.FromArgcArgv(1, const_cast<char**>(chars1.data())));

   const array<const char*, 2> chars2 { "ExePath", "Arg1" };
   const vector<string> expectedArgsB { "ExePath", "Arg1" };
   VECTORS_ARE_EQUAL(expectedArgsB, _vectorHelper.FromArgcArgv(2, const_cast<char**>(chars2.data())));

   const array<const char*, 3> chars3 { "ExePath", "Arg1", "Arg2" };
   const vector<string> expectedArgsC { "ExePath", "Arg1", "Arg2" };
   VECTORS_ARE_EQUAL(expectedArgsC, _vectorHelper.FromArgcArgv(3, const_cast<char**>(chars3.data())));
}

TEST(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
{
   const vector<string> emptyVector;
   IS_EMPTY_STRING(_vectorHelper.Join(emptyVector, ' '));
   IS_EMPTY_STRING(_vectorHelper.Join(emptyVector, ','));
}

TEST(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
{
   const vector<string> nonEmptyStringVector = { "hello" };
   ARE_EQUAL("hello", _vectorHelper.Join(nonEmptyStringVector, ' '));
   ARE_EQUAL("hello", _vectorHelper.Join(nonEmptyStringVector, ','));
}

TEST3X3(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator,
   const string& expectedJoinedVector, const vector<string>& vec, char separator,
   "1 2", vector<string>{ "1", "2" }, ' ',
   "1,2", vector<string>{ "1", "2" }, ',',
   "1 2 3", vector<string>{ "1", "2", "3" }, ' ',
   "1,2,3", vector<string>{ "1", "2", "3" }, ',')
{
   const string joinedVector = _vectorHelper.Join(vec, separator);
   ARE_EQUAL(expectedJoinedVector, joinedVector);
}

RUN_TESTS(VectorHelperTests)
