//
//  main.c
//  test-rush-02
//
//  Created by Tester on 21.8.2023.
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h> // malloc

char hundred[] = "hundred";

char ons[][10] = {
    "thousand",
    "million",
    "billion",
    "trillion"
};

char ties[][10] = {
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety"
};

char beginners[][10] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"
};

int gCountOfThousandDivisions = 0;

void writeToConsole(const char* message)
{
    while (*message != '\0') {
        write(1, message, 1);
        ++message;
    }
}

int ft_atoi(const char *numericStr, unsigned long long *numberPtr)
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

void printNumberLessThan1000(unsigned long long number)
{
    if (number < 20) {
        writeToConsole(beginners[number]);
    }
    else if (number < 100) {
        unsigned long long tens = number / 10;
        
        // twenty starts at index 0.
        writeToConsole(ties[tens - 2]);
        int ones = number % 10;
        if (ones != 0) {
            writeToConsole(" ");
            printNumberLessThan1000(ones);
        }
    }
    else if (number < 1000) {
        unsigned long long hundreds = number / 100;
        unsigned long long tensAndOnes = number % 100;
        
        printNumberLessThan1000(hundreds);
        writeToConsole(" hundred");
        if (tensAndOnes != 0) {
            writeToConsole(" ");
            printNumberLessThan1000(tensAndOnes);
        }
    }
}

unsigned long long getTopThreeDigits(unsigned long long givenNumber, unsigned long long *threeDigitsPosition, unsigned long long *remainingDigits)
{
    unsigned long long number = givenNumber;
    
    if (number < 1000) {
        *threeDigitsPosition = 0;
        *remainingDigits = 0;
        return number;
    }
    
    unsigned long long topThreeDigits = 0;
    unsigned long long position = 0;
    unsigned long divisor = 1;
    while (number > 999) {
        ++position;
        number /= 1000;
        divisor *= 1000;
    }
    
    topThreeDigits = number;
    *threeDigitsPosition = position;
    *remainingDigits = givenNumber % divisor;
    
    return topThreeDigits;
}



void printNumberInWords(unsigned long long number)
{
    if (number < 1000) {
        printNumberLessThan1000(number);
    }
    else {
        int prefixSpace = 0;
        unsigned long long remainingDigits = number;
        unsigned long long threeDigitsPosition = 0;
        
        while (remainingDigits != 0) {
            unsigned long long topThreeDigits = getTopThreeDigits(remainingDigits, &threeDigitsPosition, &remainingDigits);
            if (topThreeDigits != 0) {
                if (prefixSpace == 1) {
                    writeToConsole(" ");
                }
                printNumberLessThan1000(topThreeDigits);
                if (threeDigitsPosition != 0) {
                    writeToConsole(" ");
                    writeToConsole(ons[threeDigitsPosition-1]);
                    prefixSpace = 1;
                }
            }
        }
    }
}

void printNumericStringInWords(const char *numericStr)
{
    unsigned long long number;
    int errCode = ft_atoi(numericStr, &number);
    if (errCode != 0) {
        writeToConsole("Error\n");
        return;
    }    
    printNumberInWords(number);
    write(1, "\n", 1);
}


int main(int argc, const char * argv[]) {
//    if (argc < 2 || argc > 3) {
//        writeToConsole("Error\n");
//        return EINVAL;
//    }

    printNumericStringInWords("1");
    printNumericStringInWords("101");
    printNumericStringInWords("1001");
    printNumericStringInWords("10001");
    printNumericStringInWords("10101");
    printNumericStringInWords("1000001");
    printNumericStringInWords("1001001");
    printNumericStringInWords("10000001");
    printNumericStringInWords("100100001");
    printNumericStringInWords("100101001");
    printNumericStringInWords("1000512345");

    
//    printNumericStringInWords("1000512345");
//    writeToConsole("\n");
//    
//    printNumericStringInWords("1000012345");
//    writeToConsole("\n");
//    
//    printNumericStringInWords("1000002345");
//    writeToConsole("\n");
    
   // printNumericStringInWords("1000000345");
    //writeToConsole("\n");
   // printNumericStringInWords("20");
    //writeToConsole("\n");
    
    //return 0;
    
    if (argc == 2) {
        printNumericStringInWords(argv[1]);
    }
    return 0;
}
