#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LIMIT 500

void inputKey(int *input, int b)
{
    printf("Enter the key\n");
    char keyStream[b];
    //take key stream user input
    scanf("%s", keyStream);
    
    for(int j = 0; j < b; j++)
    {
        //check if small letter, convert into capital letter
        if(keyStream[j] >= 97 && keyStream[j] <= 122){
            keyStream[j] = keyStream[j] - 32;
        }
        //converting key to range 0-25
        input[j] = keyStream[j] - 65;    
    }          
}

void encrypt(char plaintext[MAX_LIMIT], int *key, char alphabets[26])
{
    char ciphertext[MAX_LIMIT];
    int size  = strlen(plaintext);
    for(int i = 0; i < size; i++)
    {
    
       //to convert lowercase to uppercase
        if(plaintext[i] >= 97 && plaintext[i] <= 122){
            plaintext[i] = plaintext[i] - 32;
        }
        
        //Encryption algorithm
        int num = ((plaintext[i]-65) + key[i]) % 26;
        ciphertext[i] = alphabets[num]; 
    }
    printf("The encrypted text is: %s\n", ciphertext);
    return;
}

void decrypt(char ciphertext[MAX_LIMIT], int *key, char alphabets[26])
{
    char plaintext[MAX_LIMIT];
    int size  = strlen(ciphertext);

    for(int i = 0; i < size; i++)
    {
    
       //to convert lowercase to uppercase
        if(ciphertext[i] >= 97 && ciphertext[i] <= 122){
            ciphertext[i] = ciphertext[i] - 32;
        }

        //Decryption algorithm
        int num = ((ciphertext[i]-65) - key[i]);
        if(num < 0)
            num = num + 26;
        plaintext[i] = alphabets[num]; 
    }
    printf("The decrypted text is: %s\n", plaintext);
    return;
}


int main()
{
    printf("Vigenere Cipher\n");
    //creating English Alphabet list
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++){
        alphabets[i] = c++;
    }
    
    char ciphertext[MAX_LIMIT];
    char plaintext[MAX_LIMIT];
    
    int task;
    
    //Getting Block Size
    int b;
    printf("Enter block size: ");
    scanf("%d", &b);
    printf("\n");
    
    fflush(stdin);
    fflush(stdin);
    
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
            fptr = fopen("key.txt","w");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 

            int *key = (int*)malloc(size*sizeof(int));
            //Calling function to get key through user input
            inputKey(key, b);

            //Storing key in file
            for(int i = 0; i < b; i++)
            {    
                fprintf(fptr, "%d ", key[i]);
            }

            //close key.txt
            fclose(fptr);

            for(int i = b; i < size; i++)
            {
                key[i] = key[i%b];
            }

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
            FILE *fptr = fopen("key.txt", "r");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 
            int *key = (int*)malloc(b*sizeof(int));
            //Reading key from file
            for(int i = 0; i < b; i++)
            {
                fscanf(fptr, "%d", &key[i]);
            }
            
            //close key.txt
            fclose(fptr);
            
            for(int i = b; i < size; i++)
            {
                key[i] = key[i%b];
            }

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

