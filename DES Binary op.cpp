#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <WinDef.h>
typedef unsigned char byte;
typedef unsigned long u32;
using namespace std;
#ifdef __GNUC__
# define __rdtsc __builtin_ia32_rdtsc
#else
# include<intrin.h>
#endif
/* The S-Box tables */
static char Sbox[8][64] = { {
        /* S1 */
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
         0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    },{
        /* S2 */
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
         3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
         0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    },{
        /* S3 */
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
         1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    },{
        /* S4 */
         7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
         3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
    },{
        /* S5 */
         2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
         4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    },{
        /* S6 */
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
         9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
         4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    },{
        /* S7 */
         4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
         1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
         6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    },{
        /* S8 */
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
         1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
         7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
         2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    } };

/* Permuted Choice 1 Table */
static char PC_1[] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

/* Permuted Choice 2 Table */
static char PC_2[] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
/* Initial Permutation Table */
static char Initial_P[] = {
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};

/*Expansion table */
static char Expansion_P[] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};
/*  permutation */
static char Permutation[] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};


// Inverse Initial Permutation Table 
static char PI[] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};
// Iteration Shift Array 
static char leftshift[] = {
       1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1
};
//Function To Read input
uint64_t  read_u64_hex(const char *data)
{
    uint64_t ret = 0;
    for (;;++data) {
    byte dec = *data- '0';
    if (dec < 10)
    ret = ret << 4 | dec;
    else {
        byte upper = (*data & 0xDF) - 'A';
        if (upper > 5) {
                break;
            }
    ret = ret << 4 | upper + 10;
    }
    }
    return ret;
}
uint64_t DES(uint64_t data, uint64_t key, string operation) {
   
    //declarations
    int i, j;
    char rw, cn;
    uint32_t C = 0 , D=0, L=0, R=0;
    uint64_t ip_result = 0, inv_result = 0, output_1 = 0;
    uint32_t sb_out = 0, func_result = 0, temp = 0;
    uint64_t s_key[16] = { 0 };
    uint64_t sb_in = 0, perm_1 = 0, perm_2 = 0;
    uint64_t R_64 = 0xffffffff00000000;
    uint64_t  L_64 = 0x00000000ffffffff;
    uint64_t LB_64 =  0x0000000000000001;
    uint32_t LB_32 = 0x00000001;

   
    // Performing initial permutation 
    for (i = 0; i < 64; i++) {

        ip_result <<= 1;
        ip_result |= (data >> (64 - Initial_P[i])) & LB_64;

    }
    L = (uint32_t)(ip_result >> 32) & L_64;
    R = (uint32_t)ip_result & L_64;

    // initial key schedule calculation 
    for (i = 0; i < 56; i++) {

        perm_1 <<= 1;
        perm_1 |= (key >> (64 - PC_1[i])) & LB_64;

    }

    C = (uint32_t)((perm_1 >> 28) & 0x000000000fffffff);
    D = (uint32_t)(perm_1 & 0x000000000fffffff);

   

    /* Calculation of the 16 keys */
    for (i = 0; i < 16; i++) {

        // Left shift
        for (j = 0; j < leftshift[i]; j++) {

            C = 0x0fffffff & (C << 1) | 0x00000001 & (C >> 27);
            D = 0x0fffffff & (D << 1) | 0x00000001 & (D >> 27);

        }

        perm_2 = 0;
        perm_2 = (((uint64_t)C) << 28) | (uint64_t)D;

        s_key[i] = 0;

        for (j = 0; j < 48; j++) {

            s_key[i] <<= 1;
            s_key[i] |= (perm_2 >> (56 - PC_2[j])) & LB_64;

        }

    }
    // Measuring cycles after Key generation
    // start
    long long t1 = __rdtsc();
    for (i = 0; i < 16; i++) {

        // F- Function
        sb_in = 0;

        for (j = 0; j < 48; j++) {

            sb_in <<= 1;
            sb_in |= (uint64_t)((R >> (32 - Expansion_P[j])) & LB_32);

        }

        //Xoring the expanded result and key
        // In Case of Decryption the keys are inversed
        if (operation == "decrypt") {
           
            sb_in = sb_in ^ s_key[15 - i];

        }
        //In Case of Encryption
        else if (operation == "encrypt") {
            
            sb_in = sb_in ^ s_key[i];

        }

        // Performing S-Box Permutation 
        for (j = 0; j < 8; j++) {

            rw = (char)((sb_in & (0x0000840000000000 >> 6 * j)) >> 42 - 6 * j);
            rw = (rw >> 4) | rw & 0x01;

            cn = (char)((sb_in & (0x0000780000000000 >> 6 * j)) >> 43 - 6 * j);

            sb_out <<= 4;
            sb_out |= (u32)(Sbox[j][16 * rw + cn] & 0x0f);

        }

        func_result = 0;

        for (j = 0; j < 32; j++) {

            func_result <<= 1;
            func_result |= (sb_out >> (32 - Permutation[j])) & LB_32;

        }
        //Swapping in the end
        temp = R;
        R = L ^ func_result;
        L = temp;

    }

    output_1 = (((uint64_t)R) << 32) | (uint64_t)L;
    //end of measuring cycles
    long long t2 = __rdtsc();
    //Printing number of cycles
    printf("cycles: %lld\n", t2 - t1);
   
    // Applying inverse initial permutation 
    for (i = 0; i < 64; i++) {

        inv_result <<= 1;
        inv_result |= (output_1 >> (64 - PI[i])) & LB_64;

    }

    return inv_result;

}

int main(int argc,  const char** argv) {

    //User Input From Command Line
    string operation= argv[1];
    string data = argv[2];
    string  key = argv[3];
    uint64_t final_output,d,k;
    //generating inputs
    d = read_u64_hex(argv[2]);
    k = read_u64_hex(argv[3]);
    //Performing DES function
    final_output = DES(d, k, operation);
    //Displaying output in hexadecimal
    if (operation == "encrypt")
    {
        printf("cipher text: %016llX\n", final_output);
       
    }
    else if (operation == "decrypt")
    {
        printf("plain text: %016llX\n", final_output);
    }
    
    return 0;
    
}