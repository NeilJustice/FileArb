#pragma once

class LineReplicator
{
public:
   LineReplicator();
   virtual ~LineReplicator();
   virtual string ReplicateLineNTimes(const string& line, size_t n) const;
};
