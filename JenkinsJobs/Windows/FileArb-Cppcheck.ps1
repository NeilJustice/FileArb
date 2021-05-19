cppcheck.exe `
   --enable=all `
   --cppcheck-build-dir=Cppcheck `
   --suppressions-list=CppcheckSuppressions.txt `
   -D_WIN32 `
   -DTEST `
   -DTESTS `
   -DMETALMOCK_NONVOID0_FREE `
   -DMETALMOCK_NONVOID1_FREE `
   -DMETALMOCK_NONVOID2_STATIC `
   -DMETALMOCK_NONVOID4_STATIC `
   -DMETALMOCK_NONVOID5_FREE `
   -I C:\include\ZenUnitAndMetalMock `
   -I libFileArb `
   -I . `
   -j 48 `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .
if ($LastExitCode -eq 1)
{
   Write-Host "Cppcheck failed with exit code 1"
   exit 1
}
