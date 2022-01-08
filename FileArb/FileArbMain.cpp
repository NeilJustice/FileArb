#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"
#include "libFileArb/Components/FileArbProgram.h"

#if defined _WIN32
#if defined _DEBUG
#pragma comment(lib, "libboost_regex-vc142-mt-gd-x64-1_75.lib")
#else
#pragma comment(lib, "libboost_regex-vc142-mt-x64-1_75.lib")
#endif
#endif

// create-binary-file --target=D:\FileArbTesting --bytes=3K --random-bytes
// create-binary-files --target=D:\FileArbTesting --directories=1 --files=1 --bytes=3 --random-bytes
// create-binary-files --target=D:\FileArbTesting --directories=3 --files=1000 --bytes=3 --random-bytes --quiet
// create-binary-files --target=D:\FileArbTesting --directories=32 --files=10 --bytes=1M --parallel

// create-text-file --target=D:\FileArbTesting --lines=3 --characters=3 --random-letters
// create-text-files --target=D:\FileArbTesting --directories=3 --files=3 --lines=3 --characters=3 --random-letters --parallel --quiet
// create-text-files --target=D:\FileArbTesting --directories=32 --files=100 --lines=100 --characters=100 --random-letters --parallel --quiet

int main(int argc, char* argv[])
{
   FileArbProgram fileArbProgram;
   const int exitCode = fileArbProgram.Main(argc, argv);
   return exitCode;
}
