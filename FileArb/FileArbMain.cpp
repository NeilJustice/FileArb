#include "libFileArb/Compiler/IfMSVCIgnoreTheseWarningsGlobally.h"
#include "libFileArb/Components/FileArbProgram.h"

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
