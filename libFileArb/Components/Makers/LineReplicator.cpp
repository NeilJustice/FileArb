#include "pch.h"
#include "libFileArb/Components/Makers/LineReplicator.h"
#if defined __linux__
#include <cstring> // memcpy
#endif

LineReplicator::LineReplicator()
{
}

LineReplicator::~LineReplicator()
{
}

string LineReplicator::ReplicateLineNTimes(const string& line, size_t n) const
{
   const size_t replicatedStringLength = line.size() * n;
   const size_t lineSize = line.size();
   string lineReplicatedNTimes(replicatedStringLength, 0);
   for (size_t i = 0; i < n; ++i)
   {
      const size_t stringOffset = i * lineSize;
      memcpy(const_cast<char*>(lineReplicatedNTimes.c_str()) + stringOffset, line.c_str(), lineSize);
   }
   return lineReplicatedNTimes;
}
