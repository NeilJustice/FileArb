Set-PSDebug -Trace 1

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
   -j 64 `
   --output-file=cppcheck_results.txt `
   --error-exitcode=1 `
   .

Set-PSDebug -Trace 0
