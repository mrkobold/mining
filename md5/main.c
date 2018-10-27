#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mem.h>
#include "md5.h"

uint8_t *pad(const uint8_t *message, uint64_t *padded_len);

void digest(const uint32_t *padded_message, const uint64_t padded_msg_len);

uint64_t get_length(const uint8_t *char_array);

uint8_t initial_message = 'X'; // 65 - 01000001

int main() {
    printf("Mr.Kobold - md5 checksum generator\n");
    printf("message:");

    uint8_t message[1000];
    scanf("%s", message);

    uint64_t padded_len;
    uint8_t *padded_message = pad(message, &padded_len);

    uint32_t *input = (uint32_t *) malloc(padded_len * 16 * sizeof(uint32_t));
    memcpy(input, padded_message, padded_len * 64);

    digest(input, padded_len);
}

void digest(const uint32_t *padded_message, const uint64_t padded_msg_len) {
    uint32_t A, B, C, D;
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;
    uint32_t F = 0, g = 0;
    for (int chunk = 0; chunk < padded_msg_len; chunk++) {
        A = a0;
        B = b0;
        C = c0;
        D = d0;
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
            F = (F + A + K[i] + padded_message[chunk * 16 + g]);
            A = D;
            D = C;
            C = B;
            B = (B + rotate_left_32(F, s[i]));
        }
        a0 = A + a0;
        b0 = B + b0;
        c0 = C + c0;
        d0 = D + d0;
    }

    print_reverse_endian(a0);
    print_reverse_endian(b0);
    print_reverse_endian(c0);
    print_reverse_endian(d0);
}

uint8_t *pad(const uint8_t message[], uint64_t *padded_len) {
    const uint64_t message_len = get_length(message);
    const uint64_t remainder = message_len % 64;
    uint64_t result_len;
    if (remainder > 55) {
        result_len = message_len / 64 + 2;
    } else {
        result_len = message_len / 64 + 1;
    }
    uint8_t *result = (uint8_t *) malloc(result_len * 64 * sizeof(uint8_t));
    for (int i = 0; i < message_len; i++) {
        result[i] = message[i];
    }
    result[message_len] = 1 << 7;
    for (uint64_t i = message_len + 1; i < result_len * 64; i++) {
        result[i] = 0;
    }
    uint64_t orig_len_bits = 8 * message_len;
    memcpy(result + result_len * 64 - 8, &orig_len_bits, 8);
    *padded_len = result_len;
    return result;
}

uint64_t get_length(const uint8_t *char_array) {
    uint64_t i;
    for (i = 0; char_array[i] != '\0'; i++);
    return i;
}