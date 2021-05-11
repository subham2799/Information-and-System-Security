#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LIMIT 500

//Taking Key Input
void inputKey(int *key, int b)
{
    printf("Enter the key\n");
    for(int j = 0; j < b; j++)
    {
        scanf("%1d", &key[j]);  
        key[j] -= 1;     
    }      
}

//Encryption Function
void encrypt(char plaintext[MAX_LIMIT], int *key, int b, char alphabets[26])
{
    
    int size = strlen(plaintext);
    char *ciphertext = (char *)malloc(size*sizeof(char));

    for(int i = 0; i < size-(b-1); i += b)
    {
        int temp1[b];

        //to convert lowercase to uppercase
        for(int l = 0; l < b; l++)
        {    
            if(plaintext[i+l] >= 97 && plaintext[i+l] <= 122){
                plaintext[i+l] = plaintext[i+l] - 32;
            }
            temp1[l] = plaintext[i+l] - 65;
        }
        
        for(int col = 0; col < b; col++)
        {   
            ciphertext[i+col] = plaintext[i+key[col]]; 
        }
    }
    printf("The encrypted text is: %s\n", ciphertext);
    
    return;
}



//Function to get inverse matrix of Key
void invertKey(int *key, int b)
{               
    int newKey[b];
    for(int i = 0; i < b; i++)
    {
        newKey[key[i]] = i;
    }

    for(int i = 0; i < b; i++)
    {
        key[i] = newKey[i];
    }
}

//Decryption Function
void decrypt(char ciphertext[MAX_LIMIT], int *key, int b, char alphabets[26])
{
    int size = strlen(ciphertext);
    char *plaintext = (char *)malloc(size*sizeof(char));

    for(int i = 0; i < size-(b-1); i += b)
    {
        int temp1[b];

        //to convert lowercase to uppercase
        for(int l = 0; l < b; l++)
        {    
            if(ciphertext[i+l] >= 97 && ciphertext[i+l] <= 122){
                ciphertext[i+l] = ciphertext[i+l] - 32;
            }
            temp1[l] = ciphertext[i+l] - 65;
        }
        
        for(int col = 0; col < b; col++)
        {   
            plaintext[i+col] = ciphertext[i+key[col]]; 
        }
    }
    printf("The decrypted text is: %s\n", plaintext);
    
    return;
}

void main()
{
    //Keyed Transposition Cipher
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++)
    {
        alphabets[i] = c++;
    }

    char task = 'a'; 

    int b = 0;             
    printf("\nEnter block size: \n");
    scanf("%d", &b); 
    
    fflush(stdin);
    fflush(stdin);

    while(1)
    {
        printf("1.To encrypt, enter E\n2.To decrypt, enter D\n3.Enter e to exit\n");
        scanf(" %c", &task);  
        
        if(task == 'E')
        {
                char plaintext[MAX_LIMIT];

                printf("Enter plain text to encrypt: \n");
                scanf("%s", plaintext);
                printf("You entered: %s\n", plaintext);

                int size = strlen(plaintext);
                

                if((size%b) != 0)
                {
                    int diff = b - (size%b);
                    for(int i = 1; i <= diff; i++){
                        plaintext[size-1+i] = 'X';
                    }
                    plaintext[size+diff] = '\0';
                }
                size = strlen(plaintext);

                //Creating file for storing key
                FILE *fptr;
                fptr = fopen("TransposeKey.txt","w");
                if(fptr == NULL){
                    printf("Error opening file");
                    return;
                } 

                int *key = (int*)malloc(size*sizeof(int));
                //Calling function to get key through user input
                inputKey(key, b);

                for(int i = 0; i < b; i++)
                {    
                    fprintf(fptr, "%d ", key[i]);
                }

                fclose(fptr);

                encrypt(plaintext, key, b, alphabets);
                return;       
        }
        else if(task == 'D'){
                char ciphertext[MAX_LIMIT];

                printf("Enter cipher text to decrypt: \n");
                scanf("%s", ciphertext);
                printf("You entered: %s\n", ciphertext);

                int size = strlen(ciphertext);
                
                //Opening file to read stored key 
                FILE *fptr = fopen("TransposeKey.txt", "r");
                if(fptr == NULL){
                    printf("Error opening file");
                    return;
                } 
                int *key = (int*)malloc(b*sizeof(int));
                //Reading key from file
                for(int i = 0; i < b; i++)
                {
                    fscanf(fptr, "%d ", &key[i]);
                }
                
                //close key.txt
                fclose(fptr);  

                //Function call to Inverse Key
                invertKey(key, b);

                decrypt(ciphertext, key, b, alphabets);
                return;

        }
        else if(task == 'e')
            return;
        else{
            printf("\nYou have selected an incorrect option. Please re-enter.\n");
        }
    
    }
    
    return;
}