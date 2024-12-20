#ifndef MN_HEAP_H
#define MN_HEAP_H

#include <stdint.h>
#include <stddef.h>

void* MN_heap_malloc(size_t size);

void MN_heap_free(void * ptr);

#endif //MN_HEAP_H
