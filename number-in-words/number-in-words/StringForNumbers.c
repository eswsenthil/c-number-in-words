//
//  StringForNumbers.c
//  test-number-words
//
//  Created by Tester on 26.8.2023.
//

#include "StringForNumbers.h"

char hundred[] = "hundred";

char thousands[][10] = {
    "",
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


const char *stringForNumberLessThan20(short number)
{
    if (number < 20) {
        return beginners[number];
    }
    return "";
}

const char *stringForTies(short index)
{
    return ties[index];
    
}

const char *stringForHundred(void)
{
    return "hundred";
}

const char *stringForThreeDigitsPosition(short position)
{
    if (position > 4) {
        return "Undefined";
    }
    
    return thousands[position];
}
