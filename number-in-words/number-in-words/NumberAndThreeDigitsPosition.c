//
//  NumberAndThreeDigitsPosition.c
//  test-number-words
//
//  Created by Tester on 26.8.2023.
//

#include "NumberAndThreeDigitsPosition.h"

#include <stdlib.h> // malloc

struct NumberAndThreeDigitsPositionNode {
    struct NumberAndThreeDigitsPosition numberAndThreeDigitsPosition;
    struct NumberAndThreeDigitsPositionNode *next;
};


static struct NumberAndThreeDigitsPositionNode *gStackHead = NULL;

void createNumberAndThreeDigitsPositionStack(void)
{
    gStackHead = malloc(sizeof(struct NumberAndThreeDigitsPositionNode));
    gStackHead->numberAndThreeDigitsPosition.number = -1;
    gStackHead->numberAndThreeDigitsPosition.threeDigitsPosition = -1;
    gStackHead->next = NULL;
}

void destroyNumberAndThreeDigitsPositionStack(void)
{
    while (!isNumberAndThreeDigitsPositionStackEmpty()) {
        popFromNumberAndThreeDigitsPositionStack();
    }
    free(gStackHead);
    gStackHead = NULL;
}

void pushToNumberAndThreeDigitsPositionStack(struct NumberAndThreeDigitsPosition numberAndThreeDigitsPosition)
{
    struct NumberAndThreeDigitsPositionNode *node = malloc(sizeof(struct NumberAndThreeDigitsPositionNode));
    node->numberAndThreeDigitsPosition = numberAndThreeDigitsPosition;
    node->next = gStackHead->next;
    gStackHead->next = node;
}

struct NumberAndThreeDigitsPosition frontOfNumberAndThreeDigitsPositionStack(void)
{
    return gStackHead->next->numberAndThreeDigitsPosition;
}

void popFromNumberAndThreeDigitsPositionStack(void)
{
    if (gStackHead->next)
    {
        struct NumberAndThreeDigitsPositionNode *nodeToBeFreed = gStackHead->next;
        gStackHead->next = nodeToBeFreed->next;
        free(nodeToBeFreed);
    }
}

int isNumberAndThreeDigitsPositionStackEmpty(void)
{
    if (gStackHead == NULL) {
        return 1;
    }
    if (gStackHead->next == NULL) {
        return 1;
    }
    return 0;
}
