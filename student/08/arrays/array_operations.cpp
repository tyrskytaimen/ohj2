#include "array_operations.hh"
#include <iostream>

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int* itemptr, int size)
{
    int greatest = *itemptr;
    for(int* position = itemptr; position < itemptr + size; ++position){
        if(*position > greatest)
        {
            greatest = *position;
        }
    }
    return greatest;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int* itemptr, int* endptr)
{
    int greatest = *itemptr;
    for(int* position = itemptr; position < endptr; ++position){
        if(*position > greatest)
        {
            greatest = *position;
        }
    }
    return greatest;
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int* itemptr, int* endptr, int* targetptr)
{
    int i = 0;
    for(int* position = itemptr; position < endptr; ++position){
        targetptr[i] = *position;
        ++i;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr)
{
    int original[rightptr - leftptr];
    copy(leftptr, rightptr, original);

    int i = rightptr - leftptr - 1;
    for(int* position = leftptr; position < rightptr; ++position){
        *position = original[i];
        --i;
    }
}
