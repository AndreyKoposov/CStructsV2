#ifndef COMP_H
#define COMP_H


typedef int (*comparator)(void* d1, void* d2, void* ctx);

int comparator_int(void* d1, void* d2, void* ctx);
int comparator_double(void* d1, void* d2, void* ctx);
int comparator_char(void* d1, void* d2, void* ctx);


#endif