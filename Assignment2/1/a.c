//Shift Cipher
#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 500

//Encryption Function
char* encrypt(char plaintext[MAX_LIMIT], int key, char alphabets[26]){
    char ciphertext[MAX_LIMIT];
    int size = strlen(plaintext);
    int alphabetsize = strlen(alphabets);
    for(int i = 0; i < size; i++)
    {
        //to convert lowercase to uppercase
        if(plaintext[i] >= 97 && plaintext[i] <= 122){
            plaintext[i] = plaintext[i] - 32;
        }

        char *ptr;
        //searching for current plaintext character in alphabet set
        ptr = strchr(alphabets, plaintext[i]);
        if(ptr != NULL){
            //shift cipher encryption algorithm

            //get index of current ciphertext character from alphabet set
            int num = (ptr - alphabets);
            num = (num + key) % alphabetsize;
            ciphertext[i] = alphabets[num];
        }
        else
            ciphertext[i] = plaintext[i]; //if plaintext character is not present in alphabet set, just append it to ciphertext
    }
    return strdup(ciphertext);
}

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
        //search current ciphertext character in alphabet set
        char *ptr;
        ptr = strchr(alphabets, ciphertext[i]);
        
        if(ptr != NULL){
            //shift cipher decryption algorithm

            //get index of current ciphertext character from alphabet set
            int num = (ptr - alphabets);
            num = num - key;
            if(num < 0)
                num = num + alphabetsize;
            plaintext[i] = alphabets[num];
        }
        else
            plaintext[i] = ciphertext[i]; //if plaintext character not present in alphabet set, just append it to ciphertext
    }
    return strdup(plaintext);
}

int main(){
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++){
        alphabets[i] = c++;
    }

    char task; 
    char plaintext[MAX_LIMIT];
    char ciphertext[MAX_LIMIT];
    int key;
    printf("1.To encrypt, enter E\n2.To decrypt, enter D\n3.Enter e to exit\n");
    while(1){
        scanf("%c",&task);
        if(task == 'E'){
                printf("Enter plain text to encrypt: \n");
                scanf("%s", plaintext);
                printf("You entered: %s\n", plaintext);
                printf("Enter the key: ");
                scanf("%d", &key);
                printf("The encrypted text is: %s\n", encrypt(plaintext, key, alphabets));
                break;
        }
        else if(task == 'D'){
                printf("Enter cipher text to decrypt: \n");
                scanf("%s", ciphertext);
                printf("You entered: %s\n", ciphertext);
                printf("Enter the key: ");
                scanf("%d", &key);
                printf("The decrypted text is: %s\n", decrypt(ciphertext, key, alphabets));
                break;
        }
        else if(task == 'e')
            break;
        else
            printf("\nYou have selected an incorrect option. Please re-enter.\n");
    }
    return 0;
}