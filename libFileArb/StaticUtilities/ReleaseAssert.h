#pragma once

void ReleaseAssert(bool predicateResult, const char* predicateText, const char* filePath, long lineNumber, const char* functionName);

#ifndef release_assert
#define release_assert(predicate) ReleaseAssert(predicate, #predicate, __FILE__, __LINE__, __func__)
#endif
