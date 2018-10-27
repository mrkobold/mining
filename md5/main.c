#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mem.h>
#include "md5.h"

uint8_t *pad(uint8_t message);

void digest(const uint32_t *padded_message);

uint8_t initial_message = 'X'; // 65 - 01000001

int main() {
    uint8_t *padded_message = pad(initial_message);

    uint32_t *input_message = (uint32_t *) malloc(16 * sizeof(uint32_t));
    memcpy(input_message, padded_message, 64);

    digest(input_message);
}

void digest(const uint32_t *padded_message) {
    uint32_t A = a0;
    uint32_t B = b0;
    uint32_t C = c0;
    uint32_t D = d0;
    uint32_t F = 0, g = 0;

    for (uint32_t i = 0; i < 64; i++) {
        if (i <= 15) {
            F = (B & C) | ((~B) & D);
            g = i;
        }
        if (16 <= i && i <= 31) {
            F = (D & B) | ((~D) & C);
            g = (5 * i + 1) % 16;
        }
        if (32 <= i && i <= 47) {
            F = B ^ C ^ D;
            g = (3 * i + 5) % 16;
        }
        if (i >= 48) {
            F = C ^ (B | (~D));
            g = (7 * i) % 16;
        }

        F = (F + A + K[i] + padded_message[g]);
        A = D;
        D = C;
        C = B;
        B = (B + rotate_left_32(F, s[i]));
    }
    A = (A + a0);
    B = (B + b0);
    C = (C + c0);
    D = (D + d0);

    print_reverse_endian(A);
    print_reverse_endian(B);
    print_reverse_endian(C);
    print_reverse_endian(D);
}

uint8_t *pad(uint8_t message) {
    uint8_t *padded_message = (uint8_t *) malloc(64 * sizeof(uint8_t));
    padded_message[0] = message;
    padded_message[1] = 1 << 7;
    for (int i = 2; i <= 63; i++) {
        padded_message[i] = 0;
    }
    padded_message[56] = 8;
    return padded_message;
}