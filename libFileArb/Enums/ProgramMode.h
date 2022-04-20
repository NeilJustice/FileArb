#pragma once

enum class ProgramMode : unsigned char
{
   Unset,
   CreateBinaryFile,
   CreateTextFile,
   CreateBinaryFiles,
   CreateTextFiles,
   Invalid,
   MaxValue
};
