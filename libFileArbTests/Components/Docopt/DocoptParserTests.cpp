#include "pch.h"
#include "libFileArb/UtilityComponents/Docopt/DocoptParser.h"

TESTS(DocoptParserTests)
AFACT(DefaultConstructor_SetsFunctions)
AFACT(ParseArgs_ArgvVectorEmpty_ThrowsInvalidArgument)
AFACT(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
AFACT(GetOptionalBool_ArgNotInMap_ReturnsFalse)
AFACT(GetOptionalBool_ArgInMap_ReturnsValue)
AFACT(GetRequiredBool_ArgNotInMap_ThrowsOutOfRangeException)
AFACT(GetRequiredBool_ArgInMap_ReturnsValue)
AFACT(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
AFACT(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
AFACT(GetOptionalString_ArgInMapWithEmptyValue_ReturnsEmptyString)
AFACT(GetRequiredString_ArgNotInMap_ThrowsOutOfRangeException)
AFACT(GetRequiredString_ArgInMap_ReturnsValue)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgIsNotInMap_ThrowsOutOfRange)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)
FACTS(GetProgramModeSpecificRequiredSizeT_ProgramModeIsNotContainedWithinTheProgramModesVectorThatRequiresArgument_Returns0)
FACTS(GetProgramModeSpecificRequiredSizeT_ProgramModeIsTheProgramModeThatRequiresTheSizeT_ReturnsResultOfCallingStaticGetRequiredSizeT)
AFACT(GetRequiredSizeT_ArgNotInMap_ThrowsInvalidArgumentException)
AFACT(GetRequiredSizeT_ArgInMapAsEmptyValue_ThrowsInvalidArgumentException)
AFACT(GetRequiredSizeT_ArgInMapAsANon0SizeT_ReturnsSizeTValueAsSizeTValue)
EVIDENCE

DocoptParser _docoptParser;
// Function Pointers
METALMOCK_NONVOID5_FREE(map<string COMMA docopt::Value>, docopt, const string&, const vector<string>&, bool, const string&, bool)
METALMOCK_NONVOID2_STATIC(size_t, DocoptParser, StaticGetRequiredSizeT, map<string COMMA docopt::Value>, const string&)

map<string, docopt::Value> _docoptArgs;
string _argName;
string _expectedKeyNotFoundExceptionMessage;

STARTUP
{
   // Function Pointers
   _docoptParser._call_docopt_docopt = BIND_5ARG_METALMOCK_OBJECT(docoptMock);
   _docoptParser._call_StaticGetRequiredSizeT = BIND_2ARG_METALMOCK_OBJECT(StaticGetRequiredSizeTMock);

   _docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _argName = ZenUnit::Random<string>() + "_argName";
   _expectedKeyNotFoundExceptionMessage = "Key not found in map: [" + _argName + "]";
}

TEST(DefaultConstructor_SetsFunctions)
{
   const DocoptParser docoptParser;
   // Function Pointers
   STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt_docopt);
   STD_FUNCTION_TARGETS(DocoptParser::StaticGetRequiredSizeT, docoptParser._call_StaticGetRequiredSizeT);
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
   const map<string, docopt::Value> docoptReturnValue = ZenUnit::RandomMap<string, docopt::Value>();
   docoptMock.Return(docoptReturnValue);

   const string commandLineUsage = ZenUnit::Random<string>();
   const vector<string> nonEmptyArgv(ZenUnit::RandomBetween<size_t>(1, 2));
   //
   const map<string, docopt::Value> docoptValues = _docoptParser.ParseArgs(commandLineUsage, nonEmptyArgv);
   //
   const vector<string> expectedNonEmptyArgvWithoutFirstArgument(
      nonEmptyArgv.data() + 1, nonEmptyArgv.data() + nonEmptyArgv.size());
   METALMOCK(docoptMock.CalledOnceWith(commandLineUsage, expectedNonEmptyArgvWithoutFirstArgument, true, "", false));
   ARE_EQUAL(docoptReturnValue, docoptValues);
}

TEST(GetOptionalBool_ArgNotInMap_ReturnsFalse)
{
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   IS_FALSE(argValue);
}

TEST(GetOptionalBool_ArgInMap_ReturnsValue)
{
   const bool optionalBoolValue = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::Value(optionalBoolValue);
   //
   const bool returnedOptionalBoolValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(returnedOptionalBoolValue, optionalBoolValue);
}

TEST(GetRequiredBool_ArgNotInMap_ThrowsOutOfRangeException)
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

TEST(GetOptionalString_ArgInMapWithEmptyValue_ReturnsEmptyString)
{
   _docoptArgs[_argName] = docopt::Value(""s);
   IS_EMPTY_STRING(_docoptParser.GetOptionalString(_docoptArgs, _argName));
}

TEST(GetRequiredString_ArgNotInMap_ThrowsOutOfRangeException)
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

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
{
   const int programModeAsInt = ZenUnit::Random<int>();
   const int fieldIsRequiredIfProgramModeIntEqualsThisValue = ZenUnit::RandomNotEqualToValue<int>(programModeAsInt);
   //
   const string argValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, _argName, programModeAsInt, fieldIsRequiredIfProgramModeIntEqualsThisValue);
   //
   ARE_EQUAL(string(), argValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgIsNotInMap_ThrowsOutOfRange)
{
   const int programModeAsInt = ZenUnit::Random<int>();
   const int fieldIsRequiredIfProgramModeIntEqualsThisValue = programModeAsInt;
   //
   THROWS_EXCEPTION(_docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, _argName, programModeAsInt, fieldIsRequiredIfProgramModeIntEqualsThisValue),
      out_of_range, _expectedKeyNotFoundExceptionMessage);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)
{
   const int programModeAsInt = ZenUnit::Random<int>();
   const int fieldIsRequiredIfProgramModeIntEqualsThisValue = programModeAsInt;
   const string argValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = argValue;
   //
   const string returnedArgValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, _argName, programModeAsInt, fieldIsRequiredIfProgramModeIntEqualsThisValue);
   //
   ARE_EQUAL(argValue, returnedArgValue);
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

TEST2X2(GetProgramModeSpecificRequiredSizeT_ProgramModeIsTheProgramModeThatRequiresTheSizeT_ReturnsResultOfCallingStaticGetRequiredSizeT,
   int programMode, const vector<int>& programModesThatRequiresArgument,
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{ static_cast<int>(ProgramMode::CreateTextFiles) },
   static_cast<int>(ProgramMode::CreateBinaryFiles), vector<int>{ static_cast<int>(ProgramMode::CreateBinaryFiles) },
   static_cast<int>(ProgramMode::CreateTextFiles), vector<int>{ static_cast<int>(ProgramMode::CreateBinaryFiles), static_cast<int>(ProgramMode::CreateTextFiles) })
{
   const size_t argumentValueAsSizeT = StaticGetRequiredSizeTMock.ReturnRandom();
   const string argumentName = ZenUnit::Random<string>();
   //
   const size_t argumentValue = _docoptParser.GetProgramModeSpecificRequiredSizeT(
      _docoptArgs, argumentName, programMode, programModesThatRequiresArgument);
   //
   METALMOCK(StaticGetRequiredSizeTMock.CalledOnceWith(_docoptArgs, argumentName));
   ARE_EQUAL(argumentValueAsSizeT, argumentValue);
}

TEST(GetRequiredSizeT_ArgNotInMap_ThrowsInvalidArgumentException)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredSizeT(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundExceptionMessage);
}

TEST(GetRequiredSizeT_ArgInMapAsEmptyValue_ThrowsInvalidArgumentException)
{
   docopt::Value emptyValue;
   _docoptArgs[_argName] = emptyValue;
   //
   const string expectedExceptionMessage = String::Concat(
      "For argument [", _argName, "], a required size_t value was not specified");
   THROWS_EXCEPTION(_docoptParser.GetRequiredSizeT(_docoptArgs, _argName),
      invalid_argument, expectedExceptionMessage);
}

TEST(GetRequiredSizeT_ArgInMapAsANon0SizeT_ReturnsSizeTValueAsSizeTValue)
{
   const size_t sizeTValue = ZenUnit::RandomNon0<size_t>();
   _docoptArgs[_argName] = docopt::Value(sizeTValue);
   //
   const size_t returnedSizeTValue = _docoptParser.GetRequiredSizeT(_docoptArgs, _argName);
   //
   ARE_EQUAL(sizeTValue, returnedSizeTValue);
}

RUN_TESTS(DocoptParserTests)
