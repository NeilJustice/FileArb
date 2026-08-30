#!/bin/bash
set -ev

export UBSAN_OPTIONS="silence_unsigned_overflow=1"
export CXX=clang++
LinuxCPlusPlusBuilder build-cpp-solution \
   --solution-name=FileArb \
   --configuration=Debug \
   --cmake-definitions="-DClangUndefinedBehaviorSanitizerMode=ON" \
   --install=false
