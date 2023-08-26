//
//  PrintNumberInWords.c
//  test-number-words
//
//  Created by Tester on 26.8.2023.
//

#include "PrintNumberInWords.h"

#include "NumberAndThreeDigitsPosition.h"
#include "StringForNumbers.h"
#include "Console.h"


void printNumberLessThan20(short number)
{
    if (number < 0 || number > 19) {
        return;
    }
    const char *wordForNumber = stringForNumberLessThan20(number);
    writeToConsole(wordForNumber);
}

void printNumberFrom20To99(short number)
{
    if ((number < 20) || (number > 99)) {
        return;
    }
    
    short numberOfTens = number / 10;
    
    // starts from 20
    short index = numberOfTens - 2;
    
    const char *wordForTiesIndex = stringForTies(index);
    writeToConsole(wordForTiesIndex);
    
    short singles = number % 10;
    
    if (singles != 0) {
        writeToConsole(" ");
        printNumberLessThan20(singles);
    }
}

void printNumberFrom100To999(short number)
{
    if (number < 100 || number > 999) {
        return;
    }
    
    short numberOfHundreds = number / 100;
    printNumberLessThan20(numberOfHundreds);
    
    writeToConsole(" ");
    const char *wordForHundred = stringForHundred();
    writeToConsole(wordForHundred);
    
    short last2Digits = number % 100;
    if (last2Digits == 0) {
        return;
    }
    else if (last2Digits < 20) {
        writeToConsole(" ");
        printNumberLessThan20(last2Digits);
    }
    else {
        writeToConsole(" ");
        printNumberFrom20To99(last2Digits);
    }
}

void printUnit(short threeDigitsPosition)
{
    if (threeDigitsPosition != 0) {
        writeToConsole(" ");
        const char *wordForThreeDigitsPosition = stringForThreeDigitsPosition(threeDigitsPosition);
        writeToConsole(wordForThreeDigitsPosition);
    }
}


void printNumberAndThreeDigitsPosition(struct NumberAndThreeDigitsPosition x)
{
    if (x.number == 0) {
        return;
    }
    
    if (x.number < 20) {
        printNumberLessThan20(x.number);
    }
    else if (x.number < 100) {
        printNumberFrom20To99(x.number);
    }
    else {
        printNumberFrom100To999(x.number);
    }
    
    if (x.threeDigitsPosition != 0) {
        writeToConsole(" ");
        const char *wordForThreeDigitsPosition = stringForThreeDigitsPosition(x.threeDigitsPosition);
        writeToConsole(wordForThreeDigitsPosition);
    }
}

void printNumberInWordsFromStack(void)
{
    while (0 == isNumberAndThreeDigitsPositionStackEmpty()) {
        struct NumberAndThreeDigitsPosition x = frontOfNumberAndThreeDigitsPositionStack();
        printNumberAndThreeDigitsPosition(x);
        popFromNumberAndThreeDigitsPositionStack();
    }
    writeToConsole("\n");
}

void pushToStack(short number, short thousandsPositions)
{
    struct NumberAndThreeDigitsPosition numberAndThreeDigitsPosition = {
        number, thousandsPositions
    };
    pushToNumberAndThreeDigitsPositionStack(numberAndThreeDigitsPosition);
}

void printNumberInWords(unsigned long long number)
{
    if (number == 0) {
        const char *word = stringForNumberLessThan20(number);
        writeToConsole(word);
        writeToConsole("\n");
        return;
    }
    
    createNumberAndThreeDigitsPositionStack();
    
    short thousandsPosition = 0;
    
    unsigned long long remainingNumber = number;
    
    // Take every 3 digits from right to left and
    // push those 3 digits to stack.
    while (remainingNumber > 0) {
        short numberLessThanThousand = remainingNumber % 1000;
        remainingNumber = remainingNumber / 1000;
        pushToStack(numberLessThanThousand, thousandsPosition);
        ++thousandsPosition;
    }
    
    printNumberInWordsFromStack();
    
    destroyNumberAndThreeDigitsPositionStack();
}
