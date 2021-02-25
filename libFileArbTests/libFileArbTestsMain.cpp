#include "pch.h"

#if defined _WIN32
#if defined _DEBUG
#pragma comment(lib, "libboost_regex-vc142-mt-gd-x64-1_75.lib")
#else
#pragma comment(lib, "libboost_regex-vc142-mt-x64-1_75.lib")
#endif
#endif

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
