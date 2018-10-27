//
// Created by Mr. Kobold on 10/27/2018.
//

#include <stdint.h>

#ifndef MINING_MD5_H
#define MINING_MD5_H

#endif //MINING_MD5_H

int PADDING_BYTES = 9;
uint32_t TWO_TO_31 = (uint32_t) 1 << 31;
uint32_t s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
uint32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void printBits(int num) {
    printf("\n\n\n");
    for (int bit = 0; bit < (sizeof(int) * 8); bit++) {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }
}

void show_memory_32(uint32_t n) {
    printf("\n");
    uint32_t mask = TWO_TO_31;
    for (int i = 0; i < 32; i++) {
        printf("%d", ((mask & n) != 0) ? 1 : 0);
        mask = mask >> 1;
        if ((i + 1) % 8 == 0) {
            printf(" ");
        }
    }
}

uint32_t rotate_right_32(uint32_t n, uint8_t steps) {
    return (n >> steps) | (n << (32 - steps));
}

uint32_t rotate_left_32(uint32_t n, uint32_t steps) {
    return (n << steps) | (n >> (32 - steps));
}

/// print hexadecimal of an uint32_t
void ph(char var, uint32_t n) {
    printf("%c:%u - %x\n", var, n, n);
}

/// print binary form of an array of uint8_t
/// length of array = 64 bytes!!!!!!!
void pab(uint8_t *a) {
    printf("\n\n");
    for (int i = 0; i < 64; i++) {
        uint8_t mask = (uint8_t) 1 << 7;
        uint8_t n = a[i];
        for (int j = 0; j < 8; j++) {
            printf("%d", ((mask & n) != 0) ? 1 : 0);
            mask = mask >> 1;
        }
        printf(" ");
    }
}

void print_reverse_endian(uint32_t number) {
    printf("%02x%02x%02x%02x ",
           number & 0xFF, (number >> 8) & 0xFF, (number >> 16) & 0xFF, (number >> 24) & 0xFF);
}