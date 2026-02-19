cmake_minimum_required(VERSION 3.10)
project(FileArb)
include(${CMAKE_SOURCE_DIR}/CMakeMacros.cmake)

if(UNIX)
   find_package(TBB REQUIRED)
endif()

source_group("" FILES FileArbMain.cpp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(FileArb FileArbMain.cpp)

target_link_libraries(FileArb libFileArb)
if(UNIX)
   set_property(TARGET FileArb PROPERTY LINKER_TYPE LLD)
   target_link_libraries(FileArb TBB::tbb)
   set_target_properties(FileArb PROPERTIES OUTPUT_NAME filearb)
   if(LCovCodeCoverageMode)
     target_link_libraries(FileArb CodeCovLibraryInterface)
   endif()
elseif(MSVC)
   replace(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ob1" "/Ob2")
   append(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oi /Ot /GS- /arch:AVX2 /fp:fast")
   replace(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug" "/DEBUG:FULL")
   replace(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/debug" "/DEBUG:FULL")
endif()

install(TARGETS FileArb DESTINATION "bin")
