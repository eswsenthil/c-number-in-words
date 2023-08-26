//
//  main.c
//  number-in-words
//
//  Created by Tester on 26.8.2023.
//

#include "Console.h"
#include "PrintNumberInWords.h"
#include "StringToNumber.h"
#include "VerifyNumberInWords.h"
#include "DictionaryFileParser.h"

#include <errno.h>

void printNumericStringInWords(const char *numericString)
{
    unsigned long long number;
    int retCode = numberForString(numericString, &number);
    if (retCode != 0) {
        writeToConsole("Error\n");
        return;
    }
    printNumberInWords(number);
}

int main(int argc, const char * argv[]) {
    
#ifdef VERIFY_NUMBER_IN_WORDS
    verifyNumberInWords();
    return 0;
#endif
    const char *path = "/Users/tester/Documents/GitHub/c-number-in-words/data/numbers.dict";
    
    buildDictionaryFromFile(path);

    return 0;
    if (argc == 2) {
        printNumericStringInWords(argv[1]);
    }
    else {
        writeToConsole("Error\n");
        return EINVAL;
    }
    return 0;
}
