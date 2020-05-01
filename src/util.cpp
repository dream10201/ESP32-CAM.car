//
// Created by xl on 2020/4/25.
//
#include <Arduino.h>
#include "util.h"

bool ccieq(const char *str1, size_t size1, uint8_t *str2, size_t size2) {
    if (size1 != size2)return false;
    for (uint i = 0; i < size1; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}
