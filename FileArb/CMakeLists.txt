cmake_minimum_required(VERSION 3.5)
project(FileArb)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

source_group("" FILES FileArbMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(FileArb FileArbMain.cpp)

if(UNIX)
   set_target_properties(FileArb PROPERTIES OUTPUT_NAME filearb)
endif()
target_link_libraries(FileArb libFileArb)
if(MSVC)
   replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ob1" "/Ob2")
   append(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oi /Ot /GS- /arch:AVX2 /fp:fast")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/DEBUG:FASTLINK")
   replace(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/debug" "/DEBUG:FASTLINK")
endif()

install(TARGETS FileArb DESTINATION "bin")

if(UNIX AND NOT APPLE)
   target_link_libraries(FileArb stdc++fs)
   if(LCovCodeCoverageMode)
     target_link_libraries(FileArb CodeCovLibraryInterface)
   endif()
endif()
