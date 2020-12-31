#include "pch.h"
#include "libFileArb/Constants/ExceptionMessage.h"

TESTS(ExceptionMessageTests)
AFACT(ExceptionMessageConstants_AreExpectedStrings)
EVIDENCE

TEST(ExceptionMessageConstants_AreExpectedStrings)
{
   ARE_EQUAL("invalid concurrent_unordered_map<K, T> key: ", ExceptionMessage::InvalidConcurrentUnorderedMapKey);
   ARE_EQUAL("invalid unordered_map<K, T> key: ", ExceptionMessage::InvalidUnorderedMapKey);
   ARE_EQUAL("invalid map<K, T> key: ", ExceptionMessage::InvalidMapKey);
   ARE_EQUAL("key already present in map: ", ExceptionMessage::KeyAlreadyPresentInMap);
}

RUN_TESTS(ExceptionMessageTests)
