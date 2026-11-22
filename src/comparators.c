int comparator_int(void* d1, void* d2, void* ctx) {
    (void)ctx;

    int* i1 = d1;
    int* i2 = d2;

    if (*i1 == *i2) return 0;
    else return *i1 < *i2 ? -1 : 1;
}

int comparator_double(void* d1, void* d2, void* ctx) {
    (void)ctx;

    double* i1 = d1;
    double* i2 = d2;

    if (*i1 < *i2) return -1;
    else if (*i1 > *i2) return 1;
    else return 0;
}

int comparator_char(void* d1, void* d2, void* ctx) {
    (void)ctx;

    char* i1 = d1;
    char* i2 = d2;

    if (*i1 == *i2) return 0;
    else return *i1 < *i2 ? -1 : 1;
}
