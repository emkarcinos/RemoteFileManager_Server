#include <sys/param.h>

uint64_t htonll(uint64_t n)
{
#if __BYTE_ORDER == __BIG_ENDIAN
    return n; 
#else
    return (((uint64_t)htonl(n)) << 32) + htonl(n >> 32);
#endif
}
