//Attack on Shift Cipher
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LIMIT 500

//Decryption Function
char* decrypt(char ciphertext[MAX_LIMIT], int key, char alphabets[26]){
    char plaintext[MAX_LIMIT];
    int size = strlen(ciphertext);
    int alphabetsize = strlen(alphabets);
    for(int i = 0; i < size; i++)
    {
        //to convert lowercase to uppercase
        if(ciphertext[i] >= 97 && ciphertext[i] <= 122){
            ciphertext[i] = ciphertext[i] - 32;
        }

        char *ptr;
        //search current ciphertext character in alphabet set
        ptr = strchr(alphabets, ciphertext[i]);
        
        if(ptr != NULL){
            //multiplicative cipher decryption algorithm

            //get index of current ciphertext character from alphabet set
            int num = (ptr - alphabets);
            num = num - key;
            if(num < 0)
                num = num + alphabetsize;
            plaintext[i] = alphabets[num];
        }
        else
            plaintext[i] = ciphertext[i]; //if plaintext character is not present in alphabet set, just append it to ciphertext
    }
    return strdup(plaintext);
}

int main(){
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++){
        alphabets[i] = c++;
    }

    char ciphertext[MAX_LIMIT];
    printf("Enter cipher text to decrypt: \n");
    scanf("%s", ciphertext);
    printf("You entered: %s\n", ciphertext);
                
    for(int key = 0; key < 26; key++){
        printf("\nkey = %d\n", key);
        printf("The decrypted text is: %s\n", decrypt(ciphertext, key, alphabets));
    }
    return 0;
}