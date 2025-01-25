#pragma once

#if defined __linux__
   #define NOINLINE __attribute__((noinline))
#elif _WIN32
   #define NOINLINE __declspec(noinline)
#endif

#if defined __linux__
   #define NORETURN __attribute__((noreturn))
#elif _WIN32
   #define NORETURN __declspec(noreturn)
#endif
