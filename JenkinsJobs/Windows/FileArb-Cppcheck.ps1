Set-PSDebug -Trace 1

cppcheck.exe `
   --enable=all `
   -DTEST `
   -DTESTS `
   -DMETALMOCK_NONVOID1_FREE `
   -DMETALMOCK_NONVOID2_STATIC `
   -DMETALMOCK_NONVOID4_STATIC `
   -DMETALMOCK_NONVOID5_FREE `
   -I C:\include\ZenUnitAndMetalMock `
   -I libFileArb `
   -I . `
   -j 64 `
   .

Set-PSDebug -Trace 0
