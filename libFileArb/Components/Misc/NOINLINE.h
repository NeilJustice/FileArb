#pragma once

#ifdef __linux__
   #define NOINLINE __attribute__((noinline))
#elif _WIN32
   #define NOINLINE __declspec(noinline)
#endif
