$args = "create-text-files " +
"--target=X:\PerformanceTestingProgramResults\FileArb\VTuneHotspots " +
"--directories=10 " +
"--files=1000 " +
"--lines=1000 " +
"--characters=100 " +
"--quiet"

AcceliTune.exe build-then-collect-hotspots `
   --working-dir="." `
   --program="FileArb" `
   --configuration=RelWithDebInfo `
   --args="$args" `
   --results-folder="D:\PerformanceProfilingResults\VTune\FileArb_Hotspots" `
   --overwrite-results-folder
