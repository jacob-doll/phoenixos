#include <kernel/mem_utils.h>

void memcpy(void* dst, const void* src, size_t num) {
    unsigned char* _dst = (unsigned char*) dst;
    const unsigned char* _src = (const unsigned char*) src; 
    for(size_t i = 0; i < num; i++) {
        *(_dst + i) = *(_src + i);
    }
}
