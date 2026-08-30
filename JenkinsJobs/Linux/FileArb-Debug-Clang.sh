#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=FileArb \
   --configuration=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --install=false
