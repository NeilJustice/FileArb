#include "pch.h"
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"
#include "libFileArbTests/ValueTypes/ZenUnit/docoptValueRandom.h"

TESTS(DocoptParserTests)
AFACT(DefaultConstructor_NewsYearMonthParser)
AFACT(ParseArgs_ArgvVectorEmpty_ThrowsInvalidArgument)
AFACT(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
AFACT(GetRequiredBool_ArgNotInMap_ThrowsOutOfRangeException)
AFACT(GetRequiredBool_ArgInMap_ReturnsValue)
AFACT(GetOptionalBool_ArgNotInMap_ReturnsFalse)
AFACT(GetOptionalBool_ArgInMap_ReturnsTrue)
AFACT(GetRequiredString_ArgNotInMap_ThrowsOutOfRangeException)
AFACT(GetRequiredString_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
AFACT(GetRequiredString_ArgInMapAsStringValue_ReturnsValue)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeIsNotContainedWithinRequiredProgramModesVector_ReturnsEmptyString)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeIsContainedInRequiredProgramModesVector_ReturnsResultOfCallingStaticGetRequiredString)
AFACT(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
AFACT(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
AFACT(GetRequiredSizeT_ReturnsResultOfCallingStaticGetRequiredSizeT)
AFACT(StaticGetRequiredSizeT_ArgNotInMap_ThrowsOutOfRangeException)
AFACT(StaticGetRequiredSizeT_ArgInMapAsNonString_Returns0)
AFACT(StaticGetRequiredSizeT_ArgInMapAsNegative1_ReturnsSizeTMaxValue)
AFACT(StaticGetRequiredSizeT_ArgInMapAsSizeTValue_ReturnsSizeT)
AFACT(GetProgramModeSpecificRequiredSizeT_ProgramModeIsNotContainedWithinRequiredProgramModesVector_Returns0)
AFACT(GetProgramModeSpecificRequiredSizeT_ProgramModeIsContainedInRequiredProgramModesVector_ReturnsResultOfCallingStaticGetRequiredSizeT)
EVIDENCE

Time::DocoptParser _docoptParser;
// Function Pointers
using DocoptMapType = map<string, docopt::Value>;
METALMOCK_NONVOID5_FREE(DocoptMapType, _call_docopt, const string&, const vector<string>&, bool, const string&, bool)
METALMOCK_NONVOID2_STATIC(size_t, DocoptParser, _call_StaticGetRequiredSizeT, map<string COMMA docopt::Value>, const string&)
METALMOCK_NONVOID2_STATIC(string, DocoptParser, _call_StaticGetRequiredString, map<string COMMA docopt::Value>, const string&)

map<string, docopt::Value> _docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::Value>();
const string _argName = ZenUnit::Random<string>() + "_argName";
const string ExpectedKeyNotFoundWhat = "Key not found in map: [" + _argName + "]";

STARTUP
{
   // Function Pointers
   _docoptParser._call_docopt = BIND_5ARG_METALMOCK_OBJECT(_call_docoptMock);
   _docoptParser._call_StaticGetRequiredSizeT = BIND_2ARG_METALMOCK_OBJECT(_call_StaticGetRequiredSizeTMock);
   _docoptParser._call_StaticGetRequiredString = BIND_2ARG_METALMOCK_OBJECT(_call_StaticGetRequiredStringMock);
}

TEST(DefaultConstructor_NewsYearMonthParser)
{
   const Time::DocoptParser docoptParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt);
   STD_FUNCTION_TARGETS(Time::DocoptParser::StaticGetRequiredSizeT, docoptParser._call_StaticGetRequiredSizeT);
   STD_FUNCTION_TARGETS(Time::DocoptParser::StaticGetRequiredString, docoptParser._call_StaticGetRequiredString);
}

TEST(ParseArgs_ArgvVectorEmpty_ThrowsInvalidArgument)
{
   const string usage = ZenUnit::Random<string>();
   const vector<string> emptyArgv;
   //
   THROWS_EXCEPTION(const auto args = _docoptParser.ParseArgs(usage, emptyArgv),
      invalid_argument, "argv cannot be empty");
}

TEST(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
{
   const map<string, docopt::Value> docoptReturnValue = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _call_docoptMock.Return(docoptReturnValue);

   const string usage = ZenUnit::Random<string>();
   const vector<string> nonEmptyArgv(ZenUnit::RandomBetween<size_t>(1, 2));
   //
   const map<string, docopt::Value> docoptValues = _docoptParser.ParseArgs(usage, nonEmptyArgv);
   //
   const vector<string> expectedNonEmptyArgvWithoutFirstArgument(
      nonEmptyArgv.data() + 1, nonEmptyArgv.data() + nonEmptyArgv.size());
   METALMOCK(_call_docoptMock.CalledOnceWith(usage, expectedNonEmptyArgvWithoutFirstArgument, true, "", false));
   ARE_EQUAL(docoptReturnValue, docoptValues);
}

TEST(GetRequiredBool_ArgNotInMap_ThrowsOutOfRangeException)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredBool(_docoptArgs, _argName),
      out_of_range, ExpectedKeyNotFoundWhat);
}

TEST(GetRequiredBool_ArgInMap_ReturnsValue)
{
   const bool boolValue = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::Value(boolValue);
   //
   const bool returnedBoolValue = _docoptParser.GetRequiredBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(boolValue, returnedBoolValue);
}

TEST(GetOptionalBool_ArgNotInMap_ReturnsFalse)
{
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   IS_FALSE(argValue);
}

TEST(GetOptionalBool_ArgInMap_ReturnsTrue)
{
   const bool argValueInMap = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::Value(argValueInMap);
   //
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

TEST(GetRequiredString_ArgNotInMap_ThrowsOutOfRangeException)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredString(_docoptArgs, _argName),
      out_of_range, ExpectedKeyNotFoundWhat);
}

TEST(GetRequiredString_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
{
   const string stringValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value();
   //
   THROWS_EXCEPTION(_docoptParser.GetRequiredString(_docoptArgs, _argName),
      invalid_argument, "arg in map as a non-string: " + _argName);
}

TEST(GetRequiredString_ArgInMapAsStringValue_ReturnsValue)
{
   const string stringValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value(stringValue);
   //
   const string returnedStringValue = _docoptParser.GetRequiredString(_docoptArgs, _argName);
   //
   ARE_EQUAL(stringValue, returnedStringValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeIsNotContainedWithinRequiredProgramModesVector_ReturnsEmptyString)
{
   const string argumentValue = _docoptParser.GetProgramModeSpecificRequiredString(_docoptArgs, _argName, 0, { 1, 2, 3 });
   ARE_EQUAL("", argumentValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeIsContainedInRequiredProgramModesVector_ReturnsResultOfCallingStaticGetRequiredString)
{
   const string staticGetRequiredStringReturnValue = _call_StaticGetRequiredStringMock.ReturnRandom();
   //
   const string argumentValue = _docoptParser.GetProgramModeSpecificRequiredString(_docoptArgs, _argName, 0, { 0 });
   //
   METALMOCK(_call_StaticGetRequiredStringMock.CalledOnceWith(_docoptArgs, _argName));
   ARE_EQUAL(staticGetRequiredStringReturnValue, argumentValue);
}

TEST(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
{
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   IS_EMPTY_STRING(argValue);
}

TEST(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
{
   const string argValueInMap = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value(argValueInMap);
   //
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

TEST(GetRequiredSizeT_ReturnsResultOfCallingStaticGetRequiredSizeT)
{
   const size_t sizeTValue = _call_StaticGetRequiredSizeTMock.ReturnRandom();
   //
   const size_t returnedSizeTValue = _docoptParser.GetRequiredSizeT(_docoptArgs, _argName);
   //
   METALMOCK(_call_StaticGetRequiredSizeTMock.CalledOnceWith(_docoptArgs, _argName));
   ARE_EQUAL(sizeTValue, returnedSizeTValue);
}

TEST(StaticGetRequiredSizeT_ArgNotInMap_ThrowsOutOfRangeException)
{
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredSizeT(_docoptArgs, _argName),
      out_of_range, ExpectedKeyNotFoundWhat);
}

TEST(StaticGetRequiredSizeT_ArgInMapAsNonString_Returns0)
{
   _docoptArgs[_argName] = docopt::Value();
   //
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredSizeT(_docoptArgs, _argName),
      invalid_argument, "AsSizeT() called with kind != Kind::String: " + to_string(static_cast<int>(docopt::Value::Kind::Empty)));
}

TEST(StaticGetRequiredSizeT_ArgInMapAsNegative1_ReturnsSizeTMaxValue)
{
   _docoptArgs[_argName] = docopt::Value("-1"s);
   //
   const size_t sizeTValue = Time::DocoptParser::StaticGetRequiredSizeT(_docoptArgs, _argName);
   //
   ARE_EQUAL(numeric_limits<size_t>::max(), sizeTValue);
}

TEST(StaticGetRequiredSizeT_ArgInMapAsSizeTValue_ReturnsSizeT)
{
   const size_t sizeTValue = ZenUnit::RandomBetween<size_t>(0, 3);
   _docoptArgs[_argName] = docopt::Value(to_string(sizeTValue));
   //
   const size_t returnedSizeTValue = Time::DocoptParser::StaticGetRequiredSizeT(_docoptArgs, _argName);
   //
   ARE_EQUAL(sizeTValue, returnedSizeTValue);
}

TEST(GetProgramModeSpecificRequiredSizeT_ProgramModeIsNotContainedWithinRequiredProgramModesVector_Returns0)
{
   const size_t argumentValue = _docoptParser.GetProgramModeSpecificRequiredSizeT(_docoptArgs, _argName, 0, { 1, 2, 3 });
   ARE_EQUAL(0, argumentValue);
}

TEST(GetProgramModeSpecificRequiredSizeT_ProgramModeIsContainedInRequiredProgramModesVector_ReturnsResultOfCallingStaticGetRequiredSizeT)
{
   const size_t staticGetRequiredSizeTReturnValue = _call_StaticGetRequiredSizeTMock.ReturnRandom();
   //
   const size_t argumentValue = _docoptParser.GetProgramModeSpecificRequiredSizeT(_docoptArgs, _argName, 0, { 0 });
   //
   METALMOCK(_call_StaticGetRequiredSizeTMock.CalledOnceWith(_docoptArgs, _argName));
   ARE_EQUAL(staticGetRequiredSizeTReturnValue, argumentValue);
}

RUN_TESTS(DocoptParserTests)
