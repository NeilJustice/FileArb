#include "pch.h"
#include "libFileArb/Components/Exception/ExceptionWhat.h"

namespace Utils
{
	const string ExceptionWhat::InvalidConcurrentUnorderedMapKey = "invalid concurrent_unordered_map<K, T> key: ";
	const string ExceptionWhat::InvalidUnorderedMapKey = "invalid unordered_map<K, T> key: ";
	const string ExceptionWhat::InvalidMapKey = "invalid map<K, T> key: ";
	const string ExceptionWhat::KeyAlreadyPresentInMap = "key already present in map: ";
}
