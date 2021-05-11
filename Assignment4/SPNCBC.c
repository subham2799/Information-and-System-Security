//Key: 101100011010101000101101
//SBox: E4D12FB83A6C5907
//PBox: 14573628
//Plaintext: 10100100
//Ciphertext: Everytime we will run encryption, it will be different depending on randomly generated Initialization Vector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LIMIT 500

void inputKey(int *key, int size)
{
    printf("Enter the key\n");
    for(int j = 0; j < size; j++)
    {
        scanf("%1d", &key[j]) ;    
    }          
    fflush(stdin);
}

void roundKeyMix(int *text, int *key, int start)
{
    for(int i = 0; i < 8; i++)
    {
        text[i] = (text[i] ^ key[start + i]);
    }
}

void permute(int *text, int *PBox)
{
    
    int size = 8;
    int *newtext = (int *)malloc(size*sizeof(int));
    
    for(int i = 0; i < size; i++)
    {
        newtext[i] = text[PBox[i]];
    }
    for(int i = 0; i < size; i++)
    {
        text[i] = newtext[i]; 
    }

    return;
}

void substitute(int *text, int *SBox)
{
    for(int k = 0; k < 8; k += 4)
    {
        int size = 4;
        int val = 0;

        for(int i = 0; i < size; i++)
        {
            val += ((1<<(size - 1 - i)) * text[k + i]);
        }

        val = SBox[val];
        
        while (val > 0)
        {
            text[k + size-1] = val % 2;
            val /= 2;
            size--;
        }
        while(size > 0){
            text[k + size-1] = 0;
            size--;
        }
    }


    return;
}

void encryptionRound(int *text, int *key, int *SBox, int *PBox)
{
    substitute(text, SBox);
    permute(text, PBox);
}

void decryptionRound(int *text, int *key, int *SBox, int *PBox)
{
    permute(text, PBox);
    substitute(text, SBox);
}

void encrypt(int *text, int *key, int *SBox, int *PBox, int Nr)
{
    for(int i = 1; i <= Nr; i++)
    {
        int start = ((4 * i) - 3)  - 1;

        //round key mixing
        roundKeyMix(text, key, start);
        
        if(i != Nr)
            encryptionRound(text, key, SBox, PBox);
        else
        {
            //Permutation ommited from last round
            substitute(text, SBox);
        }
    }

    //Fifth Round key mixing
    int i = 5;
    int start = ((4 * i) - 3)  - 1;
    
    roundKeyMix(text, key, start);
    
    return;
}

void decrypt(int *text, int *key, int *SBox, int *PBox, int Nr)
{

    
    //First Round key(5th key of Encryption) mixing
    int i = 5;
    int start = ((4 * i) - 3)  - 1;    
    roundKeyMix(text, key, start);
    

    for(int i = 4; i >= 1; i--)
    {
        int start = ((4 * i) - 3)  - 1;

        if(i != 4)
        {
            decryptionRound(text, key, SBox, PBox);
            
        }    
        else
        {
            //Permutation ommited from first round
            substitute(text, SBox);
            
        }

        //round key mixing
        roundKeyMix(text, key, start);
        
    }

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

int main()
{
    printf("SPN Cipher\n");
    //creating English Alphabet list
    char c = 'A'; 
    char alphabets[26];
    for(int i = 0; i < 26; i++){
        alphabets[i] = c++;
    }
    
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

            int Nr = 0;

            printf("Enter the number of rounds: ");
            scanf("%d", &Nr);

            int keySize = 8 + Nr * 4;

            //Creating file for storing key
            FILE *fptr;
            fptr = fopen("SPNKey.txt","w");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 

            int *key = (int*)malloc(keySize*sizeof(int));
            //Calling function to get key through user input
            inputKey(key, keySize);

            //Storing key in file
            for(int i = 0; i < keySize; i++)
            {    
                fprintf(fptr, "%d ", key[i]);
            }

            //close key.txt
            fclose(fptr);

            char temp[16];
            int SBox[16];
            printf("\nEnter the S-box: \n");
            scanf("%s",temp);
            
            for(int i = 0; i < 16; i++)
            {
                if(temp[i] >= 65 && temp[i] <= 70){
                    SBox[i] = temp[i] - 65 + 10; 
                }
                else{
                    SBox[i] = temp[i] - 48;
                }
            }
            
            printf("The S-box is: \n");
            for(int i = 0; i < 16; i++)
            {
                printf("%3d", i);
            }
            printf("\n");
            for(int i = 0; i < 16; i++)
            {
                printf("%3c", temp[i]);
            }
            printf("\n");
            
            
            int PBox[8];
            printf("\nEnter the P-box: \n");
            for(int i = 0; i < 8; i++){
                scanf("%1d", &PBox[i]);
            }
            
            printf("The P-box is: \n");
            for(int i = 0; i < 8; i++)
            {
                printf("%2d ", i+1);
            }
            printf("\n");
            for(int i = 0; i < 8; i++)
            {
                printf("%2d ", PBox[i]);
                PBox[i]--;
            }
            printf("\n");
            
            char str[MAX_LIMIT];
            printf("\nEnter the plaintext.\n");
            scanf("%s",str);
            fflush(stdin);

            printf("\nYou entered: ");
            printf("%s", str);

            printf("\n");
            
            int size = strlen(str);
            int *plaintext = (int*)malloc(size*sizeof(int));
            int pos = 0;
            if((size%8) != 0)
            {
                int diff = 8 - (size%8);
                for(int i = 0; i < diff; i++){
                    plaintext[i] = 0;
                }
                pos = diff;
            }
            for(int i = 0; i < size; i++)
            {    
                plaintext[pos + i] = str[i] - 48;
            }
            int t = 0;
            printf("\nFinal plaintext: ");
            for(t = 0; t < size + pos; t++)
            {    
                printf("%d",plaintext[t]);
            }
            printf("\n");
            
            int *IV = (int*)malloc(8*sizeof(int));
            srand(time(0));
            for(int j = 0; j < 8; j++)
            {
                IV[j] = (rand() % 2);    
            }  
            //Creating file for storing initialization vector
            FILE *fptr1;
            fptr1 = fopen("IV.txt","w");
            if(fptr1 == NULL){
                printf("Error opening file");
                return 0;
            } 

            //Storing IV in file
            for(int i = 0; i < 8; i++)
            {    
                fprintf(fptr1, "%d ", IV[i]);
            }

            //close IV.txt
            fclose(fptr1);
 
            int b = 8;
            for(int l = 0; l < size; l+=b)
            {
                roundKeyMix(IV, plaintext, l);
                encrypt(IV, key, SBox, PBox, Nr);
                for(int j = 0; j < 8; j++)
                {
                        plaintext[l+j] = IV[j]; 
                }
            }
            printf("\nThe encrypted text is: ");
            for (int k = 0; k < size + pos; k++)
            {
                printf("%d", plaintext[k]);
            }
            printf("\n");
            return 0;
        }
        else if(task == 2){
            //Decryption Part
            printf("\nDecrypting.\n");

            int Nr = 0;

            printf("Enter the number of rounds: ");
            scanf("%d", &Nr);

            int keySize = 8 + Nr * 4;

            //Opening file to read stored key 
            FILE *fptr = fopen("SPNKey.txt", "r");
            if(fptr == NULL){
                printf("Error opening file");
                return 0;
            } 
            int *key = (int*)malloc(keySize*sizeof(int));
            //Reading key from file
            for(int i = 0; i < keySize; i++)
            {
                fscanf(fptr, "%d ", &key[i]);
            }
            //close key.txt
            fclose(fptr);

            char temp[16];
            int *SBox = (int*)malloc(16*sizeof(int));
            printf("\nEnter the S-box: \n");
            scanf("%s",temp);
            
            for(int i = 0; i < 16; i++)
            {
                if(temp[i] >= 65 && temp[i] <= 70){
                    SBox[i] = temp[i] - 65 + 10; 
                }
                else{
                    SBox[i] = temp[i] - 48;
                }
            }

            invertKey(SBox, 16);
            
            printf("The S-box is: \n");
            for(int i = 0; i < 16; i++)
            {
                printf("%3d", i);
            }
            printf("\n");
            for(int i = 0; i < 16; i++)
            {
                printf("%3c", temp[i]);
            }
            printf("\n");
            
            
            int *PBox = (int*)malloc(8*sizeof(int));
            printf("\nEnter the P-box: \n");
            for(int i = 0; i < 8; i++){
                scanf("%1d", &PBox[i]);
                PBox[i]--;
            }

            invertKey(PBox, 8);
            
            printf("The P-box is: \n");
            for(int i = 0; i < 8; i++)
            {
                printf("%2d ", i+1);
            }
            printf("\n");
            for(int i = 0; i < 8; i++)
            {
                printf("%2d ", PBox[i] + 1);
            }
            printf("\n");
            
            char str[MAX_LIMIT];
            printf("\nEnter the ciphertext.\n");
            scanf("%s",str);
            fflush(stdin);

            printf("\nYou entered: ");
            printf("%s", str);

            printf("\n");
            
            int size = strlen(str);
            int *ciphertext = (int*)malloc(size*sizeof(int));
            for(int i = 0; i < size; i++)
            {    
                ciphertext[i] = str[i] - 48;
            }
            int t = 0;
            
            int *IV = (int*)malloc(8*sizeof(int));
            //Opening file to read stored initialization vector 
            FILE *fptr1 = fopen("IV.txt", "r");
            if(fptr1 == NULL){
                printf("Error opening file");
                return 0;
            } 
            //Reading IV from file
            for(int i = 0; i < 8; i++)
            {
                fscanf(fptr1, "%d ", &IV[i]);
            }
            
            //close IV.txt
            fclose(fptr1);
            
            
            int b = 8;
            
            int *plaintext = (int*)malloc(size*sizeof(int));
            for(int i = 0; i < size; i++)
            {
                plaintext[i] = ciphertext[i];
            }
            for(int l = 0; l < size; l+=b)
            {
                //Decrypt function call
                decrypt(&plaintext[l], key, SBox, PBox, Nr);
                
                if(l == 0){
                    //Round Key Mixing of 1st block
                    roundKeyMix(&plaintext[l], IV, 0);
                    
                }
                    
                else{
                    //Round key mixing of rest of the blocks
                    roundKeyMix(&plaintext[l], ciphertext, l-b);

                }
            }
            printf("\nThe decrypted text is: ");
            for (int k = 0; k < size; k++)
            {
                printf("%d", plaintext[k]);
            }
            printf("\n");
            return 0;
        }
        
        else{
            printf("Invalid selection. Please re-enter your desired operation.\n");
        }
        
    }
    
    return 0;
}

