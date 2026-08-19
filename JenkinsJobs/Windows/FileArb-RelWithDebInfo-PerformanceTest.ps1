$args = "create-text-files " +
"--target=X:\PerformanceTestingProgramResults\FileArb\PerformanceTest " +
"--directories=32 " +
"--files=100 " +
"--lines=1000 " +
"--characters=200 " +
"--random-letters " +
"--parallel"

AcceliTune.exe build-then-measure-program-run-time `
   --working-dir="." `
   --program="FileArb" `
   --configuration="RelWithDebInfo" `
   --args="$args" `
   --performance-test-results-file="C:\Code\WindowsPerformanceTestResults\Performance\FileArb-Performance.txt"
