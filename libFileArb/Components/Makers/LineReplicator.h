#pragma once

class LineReplicator
{
public:
   virtual ~LineReplicator() = default;

   virtual string ReplicateLineNTimes(const string& line, size_t n) const;
};
