//
//  StringToNumber.c
//  number-in-words
//
//  Created by Tester on 26.8.2023.
//

#include "StringToNumber.h"

#include <errno.h>

int numberForString(const char *numericStr, unsigned long long *numberPtr)
{
    unsigned long long result = 0;
    const char *p = numericStr;
    while (*p != '\0') {
        if ( (*p < '0') || (*p > '9') ) {
            return EINVAL;
        }
        // TODO: check for overflow
        result = (result * 10) + (*p - '0');
        ++p;
    }
    *numberPtr = result;
    
    return 0;
}

