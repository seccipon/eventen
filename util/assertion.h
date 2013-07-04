#ifndef ASSERTION_H
#define ASSERTION_H
#include "log/log.h"
#include "exceptions/exceptions.h"


#define ASSERT(x) { if (!(x)) {  throw EXCEPTION_ASSERT_FAILED(#x); } }

#endif // ASSERTION_H
