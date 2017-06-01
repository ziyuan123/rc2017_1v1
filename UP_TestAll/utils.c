//
// Created by admin on 2017/6/1.
//

#include "utils.h"

int find_nearst_in_array(int value, const int *array, int start, int end) {
    int i;
    for (i = start; i < end; i++) {
        if (value < array[i])
            break;
    }
    if (i > start)
        return (value - array[i - 1]) < (array[i] - value) ? i - 1 : i;
    else
        return i;
}