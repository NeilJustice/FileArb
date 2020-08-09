#include "pch.h"
#include "libFileArb/Components/Docopt/DocoptParser.h"
#include "libFileArbTests/Components/Docopt/ZenUnit/docoptValueRandom.h"

TESTS(DocoptParserTests)
AFACT(Constructor_SetsFunctionsToExpected)
AFACT(ParseArgs_ArgvVectorEmpty_Throws)
AFACT(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
AFACT(GetRequiredString_ArgNotInMap_Throws)
AFACT(GetRequiredString_ArgInMap_ReturnsValue)
AFACT(GetRequiredUnsigned_ArgNotInMap_ThrowsInvalidArgumentException)
AFACT(GetRequiredUnsigned_ArgInMapAsEmptyValue_ThrowsInvalidArgumentException)
FACTS(GetRequiredUnsigned_ArgInMapAsANegativeLong_ThrowsInvalidArgumentException)
AFACT(GetRequiredUnsigned_ArgInMapAsANonNegativeLong_ReturnsLongValueAsUnsignedValue)
AFACT(GetRequiredBool_ArgNotInMap_Throws)
AFACT(GetRequiredBool_ArgInMap_ReturnsValue)
AFACT(GetOptionalBool_ArgNotInMap_ReturnsFalse)
AFACT(GetOptionalBool_ArgInMap_ReturnsTrue)
AFACT(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
AFACT(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
AFACT(GetOptionalString_ArgInMapWithEmptyValue_ReturnsEmptyString)
FACTS(GetProgramModeSpecificRequiredSizeT_ProgramModeIsNotContainedWithinTheProgramModesVectorThatRequiresArgument_Returns0)
FACTS(GetProgramModeSpecificRequiredSizeT_ProgramModeIsTheProgramModeThatRequiresTheUnsigned_ReturnsResultOfCallingStaticGetRequiredUnsigned)
EVIDENCE

Utils::DocoptParser _docoptParser;
ZENMOCK_NONVOID5_FREE(map<string COMMA docopt::Value>, docopt, const string&, const vector<string>&, bool, const string&, bool)
ZENMOCK_NONVOID2_STATIC(unsigned, Utils::DocoptParser, StaticGetRequiredUnsigned, map<string COMMA docopt::Value>, const string&)

map<string, docopt::Value> _docoptArgs;
string _argName;
string _expectedKeyNotFoundExceptionMessage;

STARTUP
{
   _docoptParser._call_docopt_docopt = BIND_5ARG_ZENMOCK_OBJECT(docoptMock);
   _docoptParser._call_StaticGetRequiredUnsigned = BIND_2ARG_ZENMOCK_OBJECT(StaticGetRequiredUnsignedMock);

   _docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _argName = ZenUnit::Random<string>() + "_argName";
   _expectedKeyNotFoundExceptionMessage = "Key not found in map: [" + _argName + "]";
}

TEST(Constructor_SetsFunctionsToExpected)
{
   Utils::DocoptParser docoptParser;
   STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt_docopt);
   STD_FUNCTION_TARGETS(Utils::DocoptParser::StaticGetRequiredUnsigned, docoptParser._call_StaticGetRequiredUnsigned);
}

TEST(ParseArgs_ArgvVectorEmpty_Throws)
{
   const string usage = ZenUnit::Random<string>();
   const vector<string> emptyArgv;
   //
   THROWS_EXCEPTION(const auto args = _docoptParser.ParseArgs(usage, emptyArgv), invalid_argument, "argv cannot be empty");
}

TEST(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
{
   const map<string, docopt::Value> docoptReturnValue = ZenUnit::RandomMap<string, docopt::Value>();
   docoptMock.Return(docoptReturnValue);

   const string usage = ZenUnit::Random<string>();
   const vector<string> nonEmptyArgv(ZenUnit::RandomBetween<size_t>(1, 2));
   //
   const map<string, docopt::Value> docoptValues = _docoptParser.ParseArgs(usage, nonEmptyArgv);
   //
   const vector<string> expectedNonEmptyArgvWithoutFirstArgument(
      nonEmptyArgv.data() + 1, nonEmptyArgv.data() + nonEmptyArgv.size());
   ZENMOCK(docoptMock.CalledOnceWith(usage, expectedNonEmptyArgvWithoutFirstArgument, true, "", false));
   ARE_EQUAL(docoptReturnValue, docoptValues);
}

TEST(GetRequiredString_ArgNotInMap_Throws)
{
   THROWS_EXCEPTION(const string requiredStringValue = _docoptParser.GetRequiredString(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundExceptionMessage);
}

TEST(GetRequiredString_ArgInMap_ReturnsValue)
{
   const string stringValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value(stringValue);
   //
   const string returnedStringValue = _docoptParser.GetRequiredString(_docoptArgs, _argName);
   //
   ARE_EQUAL(stringValue, returnedStringValue);
}

TEST(GetRequiredUnsigned_ArgNotInMap_ThrowsInvalidArgumentException)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredUnsigned(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundExceptionMessage);
}

TEST(GetRequiredUnsigned_ArgInMapAsEmptyValue_ThrowsInvalidArgumentException)
{
   docopt::Value emptyValue;
   _docoptArgs[_argName] = emptyValue;
   //
   const string expectedExceptionMessage = "For argument [" + _argName + "], a required unsigned value was not specified";
   THROWS_EXCEPTION(_docoptParser.GetRequiredUnsigned(_docoptArgs, _argName),
      invalid_argument, expectedExceptionMessage);
}

TEST1X1(GetRequiredUnsigned_ArgInMapAsANegativeLong_ThrowsInvalidArgumentException,
   long invalidNegativeLongValue,
   -1,
   -2,
   -3)
{
   _docoptArgs[_argName] = docopt::Value(invalidNegativeLongValue);
   //
   const string expectedExceptionMessage = "For argument [" + _argName + "], invalid negative value: " + to_string(invalidNegativeLongValue);
   THROWS_EXCEPTION(_docoptParser.GetRequiredUnsigned(_docoptArgs, _argName),
      invalid_argument, expectedExceptionMessage);
}

TEST(GetRequiredUnsigned_ArgInMapAsANonNegativeLong_ReturnsLongValueAsUnsignedValue)
{
   const long nonNegativeLongValue = ZenUnit::RandomBetween<long>(0, numeric_limits<long>::max());
   _docoptArgs[_argName] = docopt::Value(nonNegativeLongValue);
   //
   const unsigned returnedUnsignedValue = _docoptParser.GetRequiredUnsigned(_docoptArgs, _argName);
   //
   ARE_EQUAL(static_cast<unsigned>(nonNegativeLongValue), returnedUnsignedValue);
}

TEST(GetRequiredBool_ArgNotInMap_Throws)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredBool(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundExceptionMessage);
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

TEST(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
{
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   ARE_EQUAL("", argValue);
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

TEST(GetOptionalString_ArgInMapWithEmptyValue_ReturnsEmptyString)
{
   _docoptArgs[_argName];
   ARE_EQUAL("", _docoptParser.GetOptionalString(_docoptArgs, _argName));
}

TEST2X2(GetProgramModeSpecificRequiredSizeT_ProgramModeIsNotContainedWithinTheProgramModesVectorThatRequiresArgument_Returns0,
   int programMode, const vector<int>& programModesThatRequiresArgument,
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{},
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{ static_cast<int>(ProgramMode::CreateBinaryFiles) },
   static_cast<int>(ProgramMode::CreateBinaryFiles), vector<int>{ static_cast<int>(ProgramMode::CreateTextFiles) })
{
   const string argumentName = ZenUnit::Random<string>();
   //
   const size_t argumentValue = _docoptParser.GetProgramModeSpecificRequiredSizeT(
      _docoptArgs, argumentName, programMode, programModesThatRequiresArgument);
   //
   ARE_EQUAL(0, argumentValue);
}

TEST2X2(GetProgramModeSpecificRequiredSizeT_ProgramModeIsTheProgramModeThatRequiresTheUnsigned_ReturnsResultOfCallingStaticGetRequiredUnsigned,
   int programMode, const vector<int>& programModesThatRequiresArgument,
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{ static_cast<int>(ProgramMode::CreateTextFiles) },
   static_cast<int>(ProgramMode::CreateBinaryFiles), vector<int>{ static_cast<int>(ProgramMode::CreateBinaryFiles) },
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{ static_cast<int>(ProgramMode::CreateBinaryFiles), static_cast<int>(ProgramMode::CreateTextFiles) })
{
   const unsigned argumentValueAsUnsigned = StaticGetRequiredUnsignedMock.ReturnRandom();
   const size_t argumentValueAsSizeT = static_cast<size_t>(argumentValueAsUnsigned);
   const string argumentName = ZenUnit::Random<string>();
   //
   const size_t argumentValue = _docoptParser.GetProgramModeSpecificRequiredSizeT(
      _docoptArgs, argumentName, programMode, programModesThatRequiresArgument);
   //
   ZENMOCK(StaticGetRequiredUnsignedMock.CalledOnceWith(_docoptArgs, argumentName));
   ARE_EQUAL(argumentValueAsSizeT, argumentValue);
}

RUN_TESTS(DocoptParserTests)
