// Usage (encryption): PasswordKeyTable plaintext.file ciphertext.file password
// Usage (decryption): PasswordKeyTable ciphertext.file plaintext.file password
// Compiled on MacOS, Linux and *BSD in X86_64 platform.
// Talk is so easy, show you my GOD.
// Simple is beautiful.

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned long ulPasswordLength;

// You can set a password at least 8 or at most 16 characters.
// You can freely to change to infinity as you wish. 
// For example, 256 characters, 512 characters, 1024 characters, and so on until infinity.
    unsigned char aucPassword[16];

// To get the password, no more than 16 characters.
// Of course, more than 16 characters is no problem.
    for(ulPasswordLength = 0; argv[3][ulPasswordLength]; ++ulPasswordLength)
    {
        aucPassword[ulPasswordLength] = argv[3][ulPasswordLength];
    }

/*
 * Key table of 256 values that you can set randomly,
 * yet you can freely to change to key table of 65536 values that you can set randomly,
 * you can also freely to change to key table of 4294967296 values that you can set randomly,
 * even if to change to key table of 18446744073709551616 values but limited to your machine memory.
*/
    unsigned char aucKeyTable[256] = {
          42, 32, 22, 12, 2, 19, 7, 47, 17, 5, 43, 37, 29, 13, 3, 41, 31, 23, 11, 0, 1, 4, 6, 8, 9, 10, 14, 15, 16, 18, 20, 21, 24, 25, 26, 27, 28, 30, 33, 34, 35, 36, 38, 39, 40, 44, 45, 46, 48, 49,
          92, 82, 72, 62, 52, 79, 59, 97, 89, 73, 67, 53, 91, 83, 71, 61, 51, 50, 54, 55, 56, 57, 58, 60, 63, 64, 65, 66, 68, 69, 70, 74, 75, 76, 77, 78, 80, 81, 84, 85, 86, 87, 88, 90, 93, 94, 95, 96, 98, 99,
          142, 132, 122, 112, 102, 139, 107, 137, 127, 103, 149, 131, 123, 113, 101, 100, 104, 105, 106, 108, 109, 110, 111, 114, 115, 116, 117, 118, 119, 120, 121, 124, 125, 126, 128, 129, 130, 133, 134, 135, 136, 138, 140, 141, 143, 144, 145, 146, 147, 148,
          192, 182, 172, 162, 152, 199, 197, 193, 179, 167, 157, 191, 181, 173, 163, 151, 150, 153, 154, 155, 156, 158, 159, 160, 161, 164, 165, 166, 168, 169, 170, 171, 174, 175, 176, 177, 178, 180, 183, 184, 185, 186, 187, 188, 189, 190, 194, 195, 196, 198,
          252, 242, 232, 222, 212, 202, 239, 227, 251, 241, 233, 223, 211, 209, 200, 201, 203, 204, 205, 206, 207, 208, 210, 213, 214, 215, 216, 217, 218, 219, 220, 221, 224, 225, 226, 228, 229, 230, 231, 234, 235, 236, 237, 238, 240, 243, 244, 245, 246, 247, 248, 249, 250, 253, 254, 255
    };

// initialize random number seed
    srand(*((unsigned int*)aucPassword) % RAND_MAX);

    struct stat statFileSize;

    stat(argv[1], &statFileSize);

// get plaintext or ciphertext file size
    unsigned long ulFileSize = statFileSize.st_size;

// allocate storage space
    unsigned char *pucPlaintextOrCiphertext = (unsigned char*)malloc(ulFileSize);

// open plaintext or ciphertext file
    int iPlaintextOrCiphertext = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);

// read data from plaintext or ciphertext file
    read(iPlaintextOrCiphertext, pucPlaintextOrCiphertext, ulFileSize);

    close(iPlaintextOrCiphertext);

// begin to deal with plaintext or ciphertext data
    for(unsigned long i = 0; i < ulFileSize; i += 256)
    {
        unsigned long j, k;

// use key table index to change the password 
        for(j = 0; j < ulPasswordLength; ++j) aucPassword[j] = aucKeyTable[aucPassword[j]];

// key table converts 8 * 32 = 256 bytes of data at a time
        for(k = 0; k < 32; ++k)
        {
            unsigned long ulKeyIndex, ulKeyTemp, *pulKeySwap1 = (unsigned long*)aucKeyTable, *pulKeySwap2 = (unsigned long*)aucKeyTable;

            if(!(i / 256 % 2))
            {
                ulKeyIndex = aucPassword[k % ulPasswordLength] % 32;
            }
            else
            {
                ulKeyIndex = rand() % 32;
            }

            ulKeyTemp = pulKeySwap1[k];

            pulKeySwap1[k] = pulKeySwap2[ulKeyIndex];

            pulKeySwap2[ulKeyIndex] = ulKeyTemp;
        }

// plaintext or ciphertext data processes 256 bytes with XOR at a time
        for(j = 0; j < 256 && i + j < ulFileSize; ++j)
        {
               pucPlaintextOrCiphertext[i + j] ^= aucKeyTable[j];
        }
    }

// open ciphertext or plaintext file
    iPlaintextOrCiphertext = open(argv[2], O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);

// write data to ciphertext or plaintext file
    write(iPlaintextOrCiphertext, pucPlaintextOrCiphertext, ulFileSize);

    close(iPlaintextOrCiphertext);

    free(pucPlaintextOrCiphertext);

    return 0;
}
