
#pragma once
#include "libFileArb/ValueTypes/FileArbArgs.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<FileArbArgs>
   {
      static void AssertEqual(const FileArbArgs& expectedFileArbArgs, const FileArbArgs& actualFileArbArgs);
   };

   FileArbArgs TestableFileArbArgs(const RandomGenerator* randomGenerator);
   template<>
   FileArbArgs Random();
};
