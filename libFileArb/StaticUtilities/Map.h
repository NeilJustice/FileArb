#pragma once

class Map
{
public:
   template<
      template<typename...>
      typename MapType,
      typename KeyType, typename ValueType, typename... Types>
   static const ValueType& At(const MapType<KeyType, ValueType, Types...>& m, const KeyType& key)
   {
      try
      {
         const ValueType& value = m.at(key);
         return value;
      }
      catch (const std::out_of_range&)
      {
         ThrowOutOfRangeExceptionWithMessageIncludingTheKeyNotFound(key);
      }
   }

   template<
      template<typename...>
      typename MapType,
      typename KeyType, typename ValueType>
   static pair<bool, ValueType> TryGetValue(const MapType<KeyType, ValueType>& m, const KeyType& key)
   {
      const typename MapType<KeyType, ValueType>::const_iterator findIter = m.find(key);
      if (findIter != m.end())
      {
         pair<bool, ValueType> trueAndValueInMap = {true, findIter->second};
         return trueAndValueInMap;
      }
      pair<bool, ValueType> falseAndDefaultValue = {false, ValueType{}};
      return falseAndDefaultValue;
   }

private:
   template<typename KeyType>
   static NORETURN NOINLINE void ThrowOutOfRangeExceptionWithMessageIncludingTheKeyNotFound(const KeyType& key)
   {
      std::ostringstream oss;
      oss << "Key not found in map: [" << key << "]";
      const std::string what(oss.str());
      throw std::out_of_range(what);
   }
};
