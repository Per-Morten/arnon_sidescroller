/// ArnonSidescroller

/* 
 * Contains various asserts
 */

#ifndef ASSERTS_H
#define ASSERTS_H

#include "arnlog.h"

 // Arn Assert can either be errors and terminate the program or treat as warnings
#if defined(ARN_ASSERT_TERMINATE)
#define ARN_ASSERT(expr) if(!(expr)) logErr("Assertion Failed: ({}) is {}! At Line {} in {}", (#expr), (expr), __LINE__, __FILE__); std::terminate();
#elif defined(ARN_ASSERT_REPORT)
#define ARN_ASSERT(expr) if(!(expr)) logWarn("Assertion Failed: ({}) is {}! At Line {} in {}", (#expr), (expr), __LINE__, __FILE__);
#else
#define ARN_ASSERT(expr)
#endif

#ifndef NDEBUG
// Weak Assert is always just a warning, and merely a suggestion that something might be wrong
#define ARN_WEAK_ASSERT(expr) if (!(expr)) logWarn("Weak Assertion Failed: ({}) is! At Line {} in {}", (#expr), (expr), __LINE__, __FILE__);
#else
#define ARN_WEAK_ASSERT(expr)
#endif

#endif // ASSERTS_H
