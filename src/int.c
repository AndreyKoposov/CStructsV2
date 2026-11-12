#include <stdlib.h>

#include "objects/int.h"


void* Int(long long value) {
    Integer* i = malloc(sizeof(Integer));
    if (!i) return NULL;

    i->value = value;

    return i;
}

void* UInt(unsigned long long value) {
    UInteger* i = malloc(sizeof(Integer));
    if (!i) return NULL;

    i->value = value;

    return i;
}