$numberOfLogicalProcessorsDividedBy2 = (Get-CimInstance -ClassName Win32_ComputerSystem).NumberOfLogicalProcessors / 2
cppcheck.exe `
   --enable=all `
   --cppcheck-build-dir=Cppcheck `
   --suppressions-list=CppcheckSuppressions.txt `
   -D_WIN32 `
   -DAFACT `
   -DFACTS `
   -DTEST `
   -DTESTS `
   -DMETALMOCK_NONVOID0 `
   -DMETALMOCK_NONVOID0_CONST `
   -DMETALMOCK_NONVOID0_FREE `
   -DMETALMOCK_NONVOID1_FREE `
   -DMETALMOCK_NONVOID2_STATIC `
   -DMETALMOCK_NONVOID2_CONST `
   -DMETALMOCK_NONVOID2_FREE `
   -DMETALMOCK_NONVOID4_STATIC `
   -DMETALMOCK_NONVOID5_FREE `
   -DMETALMOCK_VOID1_CONST `
   -DMETALMOCK_VOID1_FREE `
   -DMETALMOCK_VOID2_CONST `
   -DMETALMOCK_VOID4_CONST `
   -DMETALMOCK_VOID5_CONST `
   -DMETALMOCK_VOID4_CONST `
   -DRUN_TEMPLATE_TESTS `
   -I C:\include\ZenUnitAndMetalMock `
   -I libFileArb `
   -I . `
   -j $numberOfLogicalProcessorsDividedBy2 `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Get-Content cppcheck_results.txt
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
