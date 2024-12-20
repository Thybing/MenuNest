#include "menu_nest/heap.h"
#include "menu_nest/common.h"

#define HEAP_SIZE 4096

#define ALIGNMENT 8
#define ALIGN_MASK (ALIGNMENT - 1)

// 静态内存池
static uint8_t heap[HEAP_SIZE];
stitic size_t heap_offset = 0;
static bool init_flag = false;

void* MN_heap_malloc(size_t size) {
    if(!init_flag){
        init_flag = true;
        while((size_t)(heap + heap_offset) % ALIGNMENT != 0){
            heap_offset++;
        }
    }
    //内存对齐
    size = (size + ALIGN_MASK) & ~ALIGN_MASK;

    // 检查请求的大小是否合理
    if (size > HEAP_SIZE - heap_offset) {
        return NULL;
    }

    void* ptr = &heap[heap_offset];

    // 增加偏移量
    heap_offset += size;

    return ptr;
}

void MN_heap_free(void * ptr) {
    ;
}
