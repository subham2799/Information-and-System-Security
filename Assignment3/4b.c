#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_LIMIT 500

int multiplicativeInv(int val){
        for(int i = 0; i < 26 ; i++){
        if((i*val) % 26 == 1){
            return i;
        }    
    }
}
int additiveInv(int val){
    for(int i = 0; i < 26 ; i++){
        if((val+i) % 26 == 0){
            return i;
        }    
    }
}
int main()
{
    printf("OTP Cipher\n");
    //creating English Alphabet list
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++){
        alphabets[i] = c++;
    }
    
    int plaintext[15];
    int ciphertext[15];
    
    printf("Enter the known plaintext.\n");
    for(int i = 0; i < 15; i++)
        scanf("%1d", &plaintext[i]);
    printf("Enter the ciphertext.\n");
    for(int i = 0; i < 15; i++)
        scanf("%1d",&ciphertext[i]);
    int key[15];
    printf("The key stream is: ");
    for(int i = 0; i < 15; i++){
        key[i] = plaintext[i] ^ ciphertext[i];
        printf("%d",key[i]);
    }
    printf("\n");
    int S0 = 0, S1 = 0, S2 = 0;
    for(int i = 4; i >= 0; i--)
    {
        S0 += ((1<<(4-i))*key[i]);
        //printf("\nS0 = %d\n", S0);
    }    
    for(int i = 4; i >= 0; i--)
    {
        S1 += ((1<<(4-i))*key[i+5]);
        //printf("\nS1 = %d\n", S1);
    }
    for(int i = 4; i >= 0; i--)
    {
        S2 += ((1<<(4-i))*key[i+10]);
        //printf("\nS2 = %d\n", S2);
    }
    int A = 0, B = 0;
    A = (multiplicativeInv((S0 + additiveInv(S1)) % 26) * ((S1 + additiveInv(S2)) %26)) % 26;
    B = (S1 + additiveInv(S0 * A)) % 26;
    printf("S0 = %d\n", S0);
    printf("A = %d\n", A);
    printf("B = %d\n", B);
    
    return 0;
}
/*
For plaintext =  001111000101001
ciphertext = 001001011101110
S0 = 3
A = 9
B = 5
*/