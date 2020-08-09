#include "libFileArb/Components/Misc/MSVCIgnoredWallWarnings.h"
#include "libFileArb/Components/FileArb/FileArbProgram.h"

// create-text-files --target=C:\FileRevisorTesting\Test --directories=3 --files=3 --lines=3 --characters=3 --verbose
// create-text-files --target=C:\FileRevisorTesting\Test --directories=32 --files=1000 --lines=100 --characters=100 --parallel --verbose

// create-binary-files --target=C:\FileRevisorTesting\Test --directories=3 --files=3 --bytes=3 --verbose
// create-binary-files --target=C:\FileRevisorTesting\Test --directories=32 --files=1000 --bytes=1000 --parallel --verbose

int main(int argc, char* argv[])
{
	FileArbProgram fileArbProgram;
	const int exitCode = fileArbProgram.Main(argc, argv);
	return exitCode;
}
