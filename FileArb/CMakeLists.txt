cmake_minimum_required(VERSION 3.5)
project(FileArb)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

source_group("" FILES FileArbMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(FileArb FileArbMain.cpp)

if(UNIX)
   set_target_properties(FileArb PROPERTIES OUTPUT_NAME filearb)
elseif(MSVC)
   target_link_libraries(FileArb libFileArb)
endif()

install(TARGETS FileArb DESTINATION "bin")

if(UNIX AND NOT APPLE)
   target_link_libraries(FileArb stdc++fs)
   if(LCovCodeCoverageMode)
     target_link_libraries(FileArb CodeCovLibraryInterface)
   endif()
endif()
