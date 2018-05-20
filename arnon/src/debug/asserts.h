/// ArnonSidescroller

/* 
 * Contains various asserts
 */

#ifndef ASSERTS_H
#define ASSERTS_H

#include "arnlog.h"

#if defined(ARN_ASSERT_TERMINATE)
#define ARN_ASSERT(expr) if(!(expr)) logErr("Assertion Failed: ({}) is {}! At Line {} in {}", (#expr), (expr), __LINE__, __FILE__); std::terminate();
#elif defined(ARN_ASSERT_REPORT)
#define ARN_ASSERT(expr) if(!(expr)) logWarn("Assertion Failed: ({}) is {}! At Line {} in {}", (#expr), (expr), __LINE__, __FILE__);
#else
#define ARN_ASSERT(expr)
#endif

#endif // ASSERTS_H
