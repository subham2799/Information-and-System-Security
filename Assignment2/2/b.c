//Multiplicative Cipher
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LIMIT 500

//Function to find multiplicative inverse of the key for equation plaintext = (ciphertext*(inverse of key))%26
int multiplicativeInverse(int key){
    for(int i = 0; i < 26 ; i++){
        if((i*key) % 26 == 1){
            return i;
        }    
    }
    printf("\nMultiplicative inverse does not exist\n");
    return 0;
}

//Decryption Function
char* decrypt(char ciphertext[MAX_LIMIT], int key, char alphabets[26]){
    char plaintext[MAX_LIMIT];
    int size = strlen(ciphertext);
    int alphabetsize = strlen(alphabets);
    key = multiplicativeInverse(key);
    if(!key)
        return "";
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
            num = (num * key) % alphabetsize;
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
    printf("%c",alphabets[26]);

    char ciphertext[MAX_LIMIT];
    printf("Enter cipher text to decrypt: \n");
    scanf("%s", ciphertext);
    printf("You entered: %s\n", ciphertext);
                
    for(int key = 0; key < 26; key++){
        printf("\n%d", key);
        if(decrypt(ciphertext, key, alphabets) == "")
            printf("Cannot decrypt\n");
        else
            printf("\nThe decrypted text is: %s\n", decrypt(ciphertext, key, alphabets));
    }
    return 0;
}