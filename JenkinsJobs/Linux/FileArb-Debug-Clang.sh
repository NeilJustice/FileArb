#!/bin/bash
set -ev

export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution=FileArb \
   --configuration=Debug \
   --cmake-definitions="-DFastLinuxDebugBuildMode=ON" \
   --install=false
