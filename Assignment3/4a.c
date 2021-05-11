#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LIMIT 500

void inputKey(char *key, int size)
{
    //printf("Enter the key\n");
    srand(time(0));
    for(int j = 0; j < size; j++)
    {
        key[j] = (rand() % 2) + 48;    
        //printf(" %c",key[j]);
    }          
}

void encrypt(char plaintext[MAX_LIMIT], char *key, char alphabets[26])
{
    char ciphertext[MAX_LIMIT];
    int size  = strlen(plaintext);
    for(int i = 0; i < size; i++)
    {
    
        //Encryption algorithm
        int num = ((plaintext[i] - 48) ^ (key[i] - 48));
        ciphertext[i] = num + 48; 
    
    }
    printf("The encrypted text is: %s\n", ciphertext);
    return;
}

void decrypt(char ciphertext[MAX_LIMIT], char *key, char alphabets[26])
{
    char plaintext[MAX_LIMIT];
    int size  = strlen(ciphertext);

    for(int i = 0; i < size; i++)
    {

        //Decryption algorithm
        int num = ((ciphertext[i] - 48) ^ (key[i] - 48));
        plaintext[i] = (num + 48); 
    }
    printf("\nThe decrypted text is: %s\n", plaintext);
    return;
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
    
    char ciphertext[MAX_LIMIT];
    char plaintext[MAX_LIMIT];
    
    int task;
    
    while(1)
    {
        printf("1. Enter 1 to Encrypt\n2. Enter 2 to Decrypt\n3. Enter 3 to Exit\n");
        scanf("%d", &task);
        
        if(task == 3){
            system("clear");
            printf("Exiting\n");
            return 0;
        }
        
        if(task == 1){
            //Encryption Part
            printf("\nEncrypting.\n");

            printf("Enter the plaintext.\n");
            scanf("%s", plaintext);
            printf("You entered: %s\n", plaintext);
            int size = strlen(plaintext);

            //Creating file for storing key
            FILE *fptr;
            fptr = fopen("otpKey.txt","w");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 

            char *key = (char*)malloc(size*sizeof(char));
            //Calling function to get key through user input
            inputKey(key, size);

            //Storing key in file
            for(int i = 0; i < size; i++)
            {    
                fprintf(fptr, "%c ", key[i]);
            }

            //close key.txt
            fclose(fptr);

            //Calling encryption function
            encrypt(plaintext, key, alphabets);
            return 0;
        }
        else if(task == 2){
            //Decryption Part
            printf("Decrypting.\n");

            printf("Enter the ciphertext.\n");
            scanf("%s", ciphertext);
            printf("You entered: %s\n", ciphertext);
            int size = strlen(ciphertext);

            //Opening file to read stored key 
            FILE *fptr = fopen("otpKey.txt", "r");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 
            char *key = (char*)malloc(size*sizeof(char));
            //Reading key from file
            for(int i = 0; i < size; i++)
            {
                fscanf(fptr, "%c ", &key[i]);
                //printf("%c",key[i]);
            }
            
            //close key.txt
            fclose(fptr);
            
            //Calling decryption function
            decrypt(ciphertext, key, alphabets);
            return 0;
        }
        
        else{
            printf("Invalid selection. Please re-enter your desired operation.\n");
        }

        //printf("\e[1;1H\e[2J");
    }
    
    return 0;
}

