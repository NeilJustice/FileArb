#!/usr/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=FileArb \
   --configuration=Debug \
   --cmake-definitions="-DIncludeWhatYouUseMode=ON" \
   --install=false \
   --standard-output-file="/code/IncludeWhatYouUseReports/FileArb_iwyu_report.txt"
