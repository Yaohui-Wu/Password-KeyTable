/* Description: 
 * This is a one-time encryption and decryption algorithm based on the random number of "JUNTAI distribution".
 * In fact, it is an implementation of Shannon encryption algorithm, but it only corrects the defect that the secret key should be the same length as the plaintext.
 * The key is to use cipher and secret key table to generate secret key of the same length as plaintext, that is to say,
 * using cipher and secret key table to shorten the length of secret key,
 * and then using "JUNTAI distribution" random number algorithm to restore the secret key of the same length as plaintext.
 * This is a demo version, as well as the official version, enhanced version and ultimate version. If you need source code, please contact me.
 * I hope who can crack it one day in my lifetime. WOW!
*/

// Usage (encryption): pkt plaintext.file cipher.file password
// Usage (decryption): pkt cipher.file plaintext.file password

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat statFileSize;

// get plaintext file size
    stat(argv[1], &statFileSize);

    unsigned long ulFileSize = statFileSize.st_size;

    unsigned char *pucPlaintextDataOrCipherData = malloc(ulFileSize);

// open plaintext file descriptor
    unsigned long ulPlaintextFD = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);

// read plaintext data from file
    read(ulPlaintextFD, pucPlaintextDataOrCipherData, ulFileSize);

    close(ulPlaintextFD);

    unsigned long i, j;

// the password at least 8 and at most 16, you can freely to change to infinity as you wish. WOW!
    unsigned char aucPassword[16];

/* key table of 256 values that you can set randomly,
 * yet you can freely to change to key table of 65536 values that you can set randomly,
 * you also can freely to change to key table of 4294967296 values that you can set randomly,
 * even if to change to key table of 18446744073709551616 values but limited to your machine memory. WOW!
*/
    unsigned char aucKeyTable[256] = {
          41, 31, 23, 11, 2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43, 44, 45, 46, 47, 48, 49,
          91, 83, 71, 61, 51, 50, 52, 53, 54, 55, 56, 57, 58, 59, 60, 62, 63, 64, 65, 66, 67, 68, 69, 70, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 89, 90, 92, 93, 94, 95, 96, 97, 98, 99,
          149, 131, 123, 113, 101, 100, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 114, 115, 116, 117, 118, 119, 120, 121, 122, 124, 125, 126, 127, 128, 129, 130, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148,
          191, 181, 173, 163, 151, 150, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 164, 165, 166, 167, 168, 169, 170, 171, 172, 174, 175, 176, 177, 178, 179, 180, 182, 183, 184, 185, 186, 187, 188, 189, 190, 192, 193, 194, 195, 196, 197, 198, 199,
          251, 241, 233, 221, 211, 209, 200, 201, 202, 203, 204, 205, 206, 207, 208, 210, 212, 213, 214, 215, 216, 217, 218, 219, 220, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 234, 235, 236, 237, 238, 239, 240, 242, 243, 244, 245, 246, 247, 248, 249, 250, 252, 253, 254, 255
    };

// get the password
    for(i = 0; argv[3][i]; ++i)
    {
        aucPassword[i] = argv[3][i];
    }

// initialize random seed
    srand(*((unsigned int*)aucPassword) % RAND_MAX);

// begin to deal with plaintext data
    for(j = 0; j < ulFileSize; j += 256)
    {
        unsigned long k, l, ulKeyTableIndex;

// change the password as key table index
        for(k = 0; k < i; ++k)
        {
            ulKeyTableIndex = aucPassword[k] % 256;

            aucPassword[k] = aucKeyTable[ulKeyTableIndex];
        }

// key table converts 8 * 32 = 256 bytes of data at once
        for(l = 0; l < 32; ++l)
        {
            unsigned long *pulKeySwap1 = (unsigned long*)aucKeyTable, *pulKeySwap2 = (unsigned long*)aucKeyTable, ulKeyTemp;

            if(!(j /256 % 2))
            {
                ulKeyTableIndex = aucPassword[l % i] % 32;
            }
            else
            {
                ulKeyTableIndex = rand() % 32;
            }

            ulKeyTemp = pulKeySwap1[l];

            pulKeySwap1[l] = pulKeySwap2[ulKeyTableIndex];

            pulKeySwap2[ulKeyTableIndex] = ulKeyTemp;
        }

// plaintext processes 256 bytes of data with XOR at once
        for(k = 0; k < 256 && j + k < ulFileSize; ++k)
        {
               pucPlaintextDataOrCipherData[j + k] ^= aucKeyTable[k];
        }
    }

// open ciphertext file descriptor
    unsigned long ulCiphertextFD = open(argv[2], O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);

// write ciphertext data to file
    write(ulCiphertextFD, pucPlaintextDataOrCipherData, ulFileSize);

    close(ulCiphertextFD);

    return 0;
}