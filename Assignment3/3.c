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
    int **newKey = (int **)malloc(b*sizeof(int *));
    for(int i=0; i < b; i++){
        newKey[i] = (int*)malloc(b*sizeof(int));
    }
    
    for(int i = 0; i < b; i++){
        for(int j = 0; j < b; j++){
            newKey[i][j] = 0;
        }
    }
    
    for(int col = 0; col < b; col++)
    {
        newKey[key[col]][col] = 1;        
    }
    // for(int i = 0; i < b; i++){
    //     for(int j = 0; j < b; j++){
    //         printf("%d ",newKey[i][j]);
    //     }
    //     printf("\n");
    // }

    int size = strlen(plaintext);
    char *ciphertext = (char *)malloc(size*sizeof(char));

    for(int i = 0; i < size-(b-1); i += b)
    {
        int temp1[b];
        int temp2[b];

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
            temp2[col] = 0;
            for(int row = 0; row < b; row++)
            {
                temp2[col] += (temp1[row] * newKey[row][col]);
                //printf("%d,%d,%d\n", temp1[row], newKey[row][col], temp2[col]);
            }
            
            //printf("%d,%d\n",temp1[col],temp2[col]);
            ciphertext[i+col] = alphabets[temp2[col]]; 
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

    for(int i = 0; i < b; i++){
        key[i] = newKey[i];
    }
}

//Decryption Function
void decrypt(char ciphertext[MAX_LIMIT], int *key, int b, char alphabets[26])
{
    int **newKey = (int **)malloc(b*sizeof(int *));
    for(int i=0; i < b; i++){
        newKey[i] = (int*)malloc(b*sizeof(int));
    }
    
    for(int i = 0; i < b; i++){
        for(int j = 0; j < b; j++){
            newKey[i][j] = 0;
        }
    }

    for(int col = 0; col < b; col++)
    {
        newKey[key[col]][col] = 1;        
    }

    int size = strlen(ciphertext);
    char *plaintext = (char *)malloc(size*sizeof(char));

    for(int i = 0; i < size-(b-1); i += b)
    {
        int temp1[b];
        int temp2[b];

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
            temp2[col] = 0;
            for(int row = 0; row < b; row++)
            {
                temp2[col] += (temp1[row] * newKey[row][col]);
                //printf("%d,%d,%d\n", temp1[row], newKey[row][col], temp2[col]);
            }
            
            //printf("%d,%d\n",temp1[col],temp2[col]);
            plaintext[i+col] = alphabets[temp2[col]]; 
        }
    }
    printf("The decrypted text is: %s\n", plaintext);
    
    return;
}

void main()
{
    printf("Transposition Cipher(using Hill Cipher)\n");
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++)
    {
        alphabets[i] = c++;
    }

    char task; 
    
    printf("1.To encrypt, enter E\n2.To decrypt, enter D\n3.Enter e to exit\n");
    while(1)
    {
        scanf(" %c",&task);
        if(task == 'E')
        {
                char plaintext[MAX_LIMIT];

                printf("Enter plain text to encrypt: \n");
                scanf("%s", plaintext);
                printf("You entered: %s\n", plaintext);

                int size = strlen(plaintext);
                int b = 0; 
                
                printf("\nEnter block size: \n");
                scanf("%d",&b);
                
                int *key = (int*)malloc(b*sizeof(int));
                

                if((size%b) != 0)
                {
                    int diff = b - (size%b);
                    for(int i = 1; i <= diff; i++){
                        plaintext[size-1+i] = 'X';
                    }
                    plaintext[size+diff] = '\0';
                }
                size = strlen(plaintext);

                //Take key input
                inputKey(key, b);
                // printf("\nThe key is:\n");
                // for(int i = 0;i < b; i++)
                // {
                //     for(int j = 0;j < b;j++)
                //     {
                //         printf("%c ",key[i][j]);
                //     }
                //     printf("\n");
                // }  

                encrypt(plaintext, key, b, alphabets);
                
                return;
        }
        else if(task == 'D'){
                char ciphertext[MAX_LIMIT];

                printf("Enter cipher text to decrypt: \n");
                scanf(" %s", ciphertext);
                printf("You entered: %s\n", ciphertext);

                int size = strlen(ciphertext);
                
                int b = 0; 
                printf("\nEnter block size: \n");
                scanf("%d",&b);

                
                int *key = (int*)malloc(b*sizeof(int));

                //Take key input
                inputKey(key, b);

                // printf("\nThe key is:\n");
                // for(int i = 0; i < b; i++)
                // {
                //     for(int j = 0; j < b; j++)
                //     {
                //         printf("%c ",key[i][j]);
                //     }
                //     printf("\n");
                // }  
                if((size%b) != 0)
                {
                    int diff = b - (size%b);
                    for(int i = 1; i <= diff; i++){
                        ciphertext[size-1+i] = 'X';
                    }
                    ciphertext[size+diff] = '\0';
                }
                size = strlen(ciphertext);
                //printf("\n%d\n",size);
                //Function call to Inverse Key
                invertKey(key, b);
                decrypt(ciphertext, key, b, alphabets);

                return;
        }
        else if(task == 'e')
            return;
        else
            printf("\nYou have selected an incorrect option. Please re-enter.\n");
    }
    return;
}