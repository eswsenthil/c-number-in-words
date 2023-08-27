//
//  NewFile.c
//  test-senthil
//
//  Created by Tester on 27.8.2023.
//

#include "NewFile.h"

#include "ft.h"

#include <unistd.h>

static t_list *gTab;

void writeToConsole(const char* message)
{
    while (*message != '\0') {
        write(1, message, 1);
        ++message;
    }
}

const char *wordForThreeDigitsPosition(unsigned long long position)
{
    int i;
    unsigned long long number;
    
    i = 0;
    number = 1;
    while (i < position) {
        number *= 1000;
        ++i;
    }
    
    i = 0;
    while (i <= 31) {
        if (gTab[i].nb == number)
            return gTab[i].val;
        ++i;
    }
    return NULL;
}

int printWordForThreeDigitsPosition(unsigned long long position)
{
    const char *word;
    word = wordForThreeDigitsPosition(position);
    if (word == NULL)
        return -1;
    writeToConsole(word);
    return 0;
}

const char *wordForNumber(unsigned long long number)
{
    int i;
    
    i = 0;
    while (i <= 31) {
        if (gTab[i].nb == number)
            return gTab[i].val;
        ++i;
    }
    return NULL;
}

int printNumber(unsigned long long number)
{
    const char *word;
    word = wordForNumber(number);
    if (word == NULL)
        return -1;
    writeToConsole(word);
    return 0;
}

void printNumberLessThan1000(unsigned long long number)
{
    if (number < 21) {
        printNumber(number);
    }
    else if (number < 100) {
        
        unsigned long long ones = number % 10;
        unsigned long long tyes = number - ones;
        printNumber(tyes);
        if (ones != 0) {
            writeToConsole(" ");
            printNumber(ones);
        }
    }
    else if (number < 1000) {
        unsigned long long hundreds = number / 100;
        unsigned long long tensAndOnes = number % 100;
        
        printNumberLessThan1000(hundreds);
        writeToConsole(" ");
        printNumber(100);
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
                    printWordForThreeDigitsPosition(threeDigitsPosition);
                    prefixSpace = 1;
                }
            }
        }
    }
}


void    ft_new_print(unsigned long long n, t_list *tab)
{
    gTab = tab;
    printNumberInWords(n);
    writeToConsole("\n");
}
