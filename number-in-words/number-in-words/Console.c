//
//  Console.c
//  test-number-words
//
//  Created by Tester on 26.8.2023.
//

#include "Console.h"

#include <unistd.h>

void writeToConsole(const char* message)
{
    while (*message != '\0') {
        write(1, message, 1);
        ++message;
    }
}
