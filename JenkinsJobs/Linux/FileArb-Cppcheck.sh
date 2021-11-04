#!/bin/bash
set -v

cores=$(grep -c ^processor /proc/cpuinfo)
cppcheck \
   --enable=all \
   --cppcheck-build-dir=Cppcheck \
   --suppressions-list=CppcheckSuppressions.txt \
   -D__linux__ \
   -DMETALMOCK_NONVOID1_FREE \
   -DMETALMOCK_NONVOID2_STATIC \
   -DMETALMOCK_NONVOID4_STATIC \
   -DMETALMOCK_NONVOID5_FREE \
   -DTEST \
   -DTESTS \
   -DTHEN_RUN_TEMPLATE_TESTS \
   -I /usr/include/c++/v1 \
   -I /usr/local/include/ZenUnitAndMetalMock \
   -I libFileArb \
   -I . \
   -j "$cores" \
   --output-file=cppcheck_results.txt \
   --error-exitcode=1 \
   .
if [ $? = 1 ]; then
   echo "Cppcheck failed with exit code 1"
   exit 1
fi
