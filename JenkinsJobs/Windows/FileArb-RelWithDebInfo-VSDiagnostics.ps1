AcceliTune.exe build-then-collect-vsdiagnostics `
   --working-dir="."  `
   --solution=FileArb `
   --program=FileArb `
   --configuration=RelWithDebInfo `
   --args-file="JenkinsJobs\Windows\VSDiagnosticsArgs.txt" `
   --session-id=61 `
   --diagsession-output-file="D:\PerformanceProfilingResults\VSDiagnostics\FileArb-RelWithDebInfo-VSDiagnostics.diagsession"
