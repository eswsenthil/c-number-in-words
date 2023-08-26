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


int printNumberLessThan20(short number)
{
    if (number < 0 || number > 19) {
        return -1;
    }
    const char *wordForNumber = stringForNumberLessThan20(number);
    writeToConsole(wordForNumber);
    return 0;
}

int printNumberFrom20To99(short number)
{
    if ((number < 20) || (number > 99)) {
        return -1;
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
    return 0;
}

int printNumberFrom100To999(short number)
{
    if (number < 100 || number > 999) {
        return -1;
    }
    
    short numberOfHundreds = number / 100;
    printNumberLessThan20(numberOfHundreds);
    
    writeToConsole(" ");
    const char *wordForHundred = stringForHundred();
    writeToConsole(wordForHundred);
    
    short last2Digits = number % 100;
    if (last2Digits == 0) {
        return 0;
    }
    else if (last2Digits < 20) {
        writeToConsole(" ");
        printNumberLessThan20(last2Digits);
    }
    else {
        writeToConsole(" ");
        printNumberFrom20To99(last2Digits);
    }
    return 0;
}

int printWordForThreeDigitsPosition(short threeDigitsPosition)
{
    if (threeDigitsPosition == 0) {
        return -1;
    }
    writeToConsole(" ");
    const char *wordForThreeDigitsPosition = stringForThreeDigitsPosition(threeDigitsPosition);
    writeToConsole(wordForThreeDigitsPosition);
    return 0;
}


int printNumberAndThreeDigitsPosition(int prefixSpace, struct NumberAndThreeDigitsPosition x)
{
    if (x.number == 0) {
        return -1;
    }
    
    if (prefixSpace == 1) {
        writeToConsole(" ");
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
    
    printWordForThreeDigitsPosition(x.threeDigitsPosition);
    return 0;
}

void printNumberInWordsFromStack(void)
{
    int prefixSpace = 0;
    while (0 == isNumberAndThreeDigitsPositionStackEmpty()) {
        struct NumberAndThreeDigitsPosition x = frontOfNumberAndThreeDigitsPositionStack();
        printNumberAndThreeDigitsPosition(prefixSpace, x);
        prefixSpace = 1;
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
