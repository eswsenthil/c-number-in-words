//
//  NumberAndThreeDigitsPosition.h
//  test-number-words
//
//  Created by Tester on 26.8.2023.
//

#ifndef NumberAndThreeDigitsPosition_h
#define NumberAndThreeDigitsPosition_h

struct NumberAndThreeDigitsPosition {
    
    // number less than 1000
    short number;
    
    // three digits position starting from right to left.
    short threeDigitsPosition;
};

void createNumberAndThreeDigitsPositionStack(void);
void destroyNumberAndThreeDigitsPositionStack(void);

void pushToNumberAndThreeDigitsPositionStack(struct NumberAndThreeDigitsPosition numberAndThreeDigitsPosition);

struct NumberAndThreeDigitsPosition frontOfNumberAndThreeDigitsPositionStack(void);

void popFromNumberAndThreeDigitsPositionStack(void);

// return 1 if empty, otherwise 0
int isNumberAndThreeDigitsPositionStackEmpty(void);

#endif /* NumberAndThreeDigitsPosition_h */
