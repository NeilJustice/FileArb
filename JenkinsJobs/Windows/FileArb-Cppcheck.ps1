$numberOfLogicalProcessors = (Get-CimInstance -ClassName Win32_ComputerSystem).NumberOfLogicalProcessors
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
   -DMETALMOCK_NONVOID0_STATIC_OR_FREE `
   -DMETALMOCK_NONVOID1_STATIC_OR_FREE `
   -DMETALMOCK_NONVOID2_STATIC_OR_FREE `
   -DMETALMOCK_NONVOID2_CONST `
   -DMETALMOCK_NONVOID2_STATIC_OR_FREE `
   -DMETALMOCK_NONVOID4_STATIC_OR_FREE `
   -DMETALMOCK_NONVOID5_STATIC_OR_FREE `
   -DMETALMOCK_VOID1_CONST `
   -DMETALMOCK_VOID1_STATIC_OR_FREE `
   -DMETALMOCK_VOID2_CONST `
   -DMETALMOCK_VOID4_CONST `
   -DMETALMOCK_VOID5_CONST `
   -DMETALMOCK_VOID4_CONST `
   -DRUN_TEMPLATE_TESTS `
   -I . `
   -I X:\include\ZenUnitAndMetalMock `
   -I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um" `
   -I libFileArb `
   -j $numberOfLogicalProcessors `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Get-Content cppcheck_results.txt
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
