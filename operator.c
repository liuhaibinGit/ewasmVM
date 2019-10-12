#include <stdlib.h>
#include "util.h"


uint32_t i32_clz(uint32_t value){
    uint32_t num = 0;
    uint32_t tmp;
    tmp = value;
		
    // bit shift
    if(tmp == 0) {
        num = 32;
    } else {
        if ((tmp >> 16) == 0) {
            num += 16;
            tmp <<= 16;
        }
        if ((tmp >> 24) == 0) {
            num += 8;
            tmp <<= 8;
        }
        if ((tmp >> 28) == 0) {
            num += 4;
            tmp <<= 4;
        }
        if ((tmp >> 30) == 0) {
            num += 2;
            tmp <<= 2;
        }
        if ((tmp >> 31) == 0) {
            num += 1;
        }
    }

    return num;
}

uint32_t i32_ctz(uint32_t value){
    uint32_t num = 0;
    uint32_t tmp;
    tmp = value;
	
    // bit shift
    if (tmp == 0) {
        num = 32;
    } else {
        if ((tmp << 16) == 0) {
            num += 16;
            tmp >>= 16;
        }
        if ((tmp << 24) == 0) {
            num += 8;
            tmp >>= 8;
        }
        if ((tmp << 28) == 0) {
            num += 4;
            tmp >>= 4;
        }
        if ((tmp << 30) == 0) {
            num += 2;
            tmp >>= 2;
        }
        if ((tmp << 31) == 0) {
            num += 1;
        }
    }

    return num;
}

uint32_t i32_popcnt(uint32_t value){
    uint32_t n = value;

    // 11 (2) = 1 * 2 + 1 (10)
    // ab (2) = a * 2 + b (10)
    // ab >> 1 = a
    // ab - (ab >> 1) = a + b
    n -= (n >> 1)  & 0x55555555;
    n  = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n  = ((n >> 4) + n) & 0x0F0F0F0F;
    n += n >> 8;
    n += n >> 16;
    n &= 0x0000003F;
    return n;
}

uint32_t i64_clz(uint64_t value){

    uint32_t count = 0;
    uint64_t tmp;
    tmp = value;

    // bit shift
    if(!tmp) {
        count = 64;
    } else {
        if ((tmp >> 32) == 0) {
            count += 32;
            tmp <<= 32;
        }
        if ((tmp >> 48) == 0) {
            count += 16;
            tmp <<= 16;
        }
        if ((tmp >> 56) == 0) {
            count += 8;
            tmp <<= 8;
        }
        if ((tmp >> 60) == 0) {
            count += 4;
            tmp <<= 4;
        }
        if ((tmp >> 62) == 0) {
            count += 2;
            tmp <<= 2;
        }
        if ((tmp >> 63) == 0) {
            count += 1;
        }
    }

    return count;
}

uint32_t i64_ctz(uint64_t value){
    uint32_t count = 0;
    uint64_t tmp;
    tmp = value;

    // bit shift
    if (tmp == 0) {
        count = 64;
    } else {
        if ((tmp << 32) == 0) {
            count += 32;
            tmp >>= 32;
        }
        if ((tmp << 48) == 0) {
            count += 16;
            tmp >>= 16;
        }
        if ((tmp << 56) == 0) {
            count += 8;
            tmp >>= 8;
        }
        if ((tmp << 60) == 0) {
            count += 4;
            tmp >>= 4;
        }
        if ((tmp << 62) == 0) {
            count += 2;
            tmp >>= 2;
        }
        if (!tmp) {
            count += 1;
        }
    }
    return count;
}

uint32_t i64_popcnt(uint64_t value){
    uint32_t count;
    uint64_t tmp;
    tmp = value;
		
    while(tmp) {
        tmp &= tmp-1;
        count++;
    }
    return count;
}



