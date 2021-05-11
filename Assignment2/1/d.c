//Playfair Cipher
#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 500

void inputKey(char key[5][5])
{
    char temp[MAX_LIMIT];
    printf("Enter the key: \n");
    scanf("%s", temp);
    int k = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0;j < 5; j++)
        {
            if(temp[k] >= 97 && temp[k] <= 122){
                temp[k] = temp[k] - 32;
            }
            key[i][j] = temp[k];
            k++;
        }
    }      
}

void find(char key[5][5], char ch, int *row, int *col)
{
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5;j++)
        {
            if(key[i][j] == ch){
                *row = i;
                *col = j;
                return;
            }
        }
    }
    *row = -1;
    *col = -1;
}

//Encryption Function
char* encrypt(char plaintext[MAX_LIMIT], char key[5][5], char alphabets[26])
{
    char ciphertext[MAX_LIMIT];
    int size = strlen(plaintext);

    for(int i = 0; i < size-1; i += 2)
    {
        //to convert lowercase to uppercase
        if(plaintext[i] >= 97 && plaintext[i] <= 122){
            plaintext[i] = plaintext[i] - 32;
        }
        if(plaintext[i+1] >= 97 && plaintext[i+1] <= 122){
            plaintext[i+1] = plaintext[i+1] - 32;
        }
        if(plaintext[i] == 'J'){
            plaintext[i] = 'I';
        }
        if(plaintext[i+1] == 'J'){
            plaintext[i+1] = 'I';
        }
        int row1 = 0, col1 = 0, row2 = 0, col2 = 0;
        //PLAYFAIR cipher encryption algorithm            
        find(key, plaintext[i], &row1, &col1);
        find(key, plaintext[i+1], &row2, &col2);
        printf("plaintext[%d] = %c,row1 = %d, col1 = %d\nplaintext[%d] = %c,row2 = %d, col2 = %d\n",i,plaintext[i],row1,col1,i+1,plaintext[i+1],row2,col2);
        if(row1 == row2)
        {
            ciphertext[i] = key[row1][(col1+1)%5];
            ciphertext[i+1] = key[row2][(col2+1)%5];
        }
        else if(col1 == col2)
        {
            ciphertext[i] = key[(row1 + 1) % 5][col1];
            ciphertext[i+1] = key[(row2 + 1) % 5][col2];
        }
        else{
            ciphertext[i] = key[row1][col2];
            ciphertext[i+1] = key[row2][col1];
        }
       
    }
    //printf("%s", ciphertext); 
    return strdup(ciphertext);
}

//Decryption Function
char* decrypt(char ciphertext[MAX_LIMIT], char key[5][5], char alphabets[26])
{
    char plaintext[MAX_LIMIT];
    int size = strlen(ciphertext);
    int alphabetsize = strlen(alphabets);
    printf("%s\n", ciphertext);
    for(int i = 0; i < size-1; i += 2)
    {
        //to convert lowercase to uppercase
        if(ciphertext[i] >= 97 && ciphertext[i] <= 122)
        {
            ciphertext[i] = ciphertext[i] - 32;
        }
        if(ciphertext[i+1] >= 97 && ciphertext[i+1] <= 122)
        {
            ciphertext[i+1] = ciphertext[i+1] - 32;
        }
        int row1 = 0, col1 = 0, row2 = 0, col2 = 0;
        //shift cipher Decryption algorithm            
        find(key, ciphertext[i], &row1, &col1);
        find(key, ciphertext[i+1], &row2, &col2);
        printf("ciphertext[%d] = %c,row1 = %d, col1 = %d\nciphertext[%d] = %c,row2 = %d, col2 = %d\n",i,ciphertext[i],row1,col1,i+1,ciphertext[i+1],row2,col2);
        if(row1 == row2)
        {
            col1 = col1-1;
            col2 = col2-1;
            if(col1 < 0)
                col1 += 5;
            if(col2 < 0)
                col2 += 5;
            plaintext[i] = key[row1][col1];
            plaintext[i+1] = key[row2][col2];
        }
        else if(col1 == col2)
        {
            row1 = row1-1;
            row2 = row2-1;
            if(row1 < 0)
                row1 += 5;
            if(row2 < 0)
                row2 += 5;
            plaintext[i] = key[row1][col1];
            plaintext[i+1] = key[row2][col2];
        }
        else
        {
            plaintext[i] = key[row1][col2];
            plaintext[i+1] = key[row2][col1];
        }
    }    
    return strdup(plaintext);
}

void main()
{
    char c = 'A';
    char alphabets[26];
    for(int i = 0; i < 26; i++)
    {
        alphabets[i] = c++;
    }

    char task; 
    char plaintext[MAX_LIMIT];
    char ciphertext[MAX_LIMIT];
    char key[5][5];
    printf("1.To encrypt, enter E\n2.To decrypt, enter D\n3.Enter e to exit\n");
    while(1)
    {
        scanf("%c",&task);
        if(task == 'E')
        {
                printf("Enter plain text to encrypt: \n");
                scanf("%s", plaintext);
                printf("You entered: %s\n", plaintext);
                int size = strlen(plaintext);
                if((size % 2) != 0)
                {
                    plaintext[size] = 'X';
                    plaintext[size+1] = '\0';
                }
                //printf("%s\n", plaintext);
                //Take key input
                inputKey(key);
                // printf("\nThe key is:\n");
                // for(int i = 0;i < 5; i++)
                // {
                //     for(int j = 0;j < 5;j++)
                //     {
                //         printf("%c ",key[i][j]);
                //     }
                //     printf("\n");
                // }  
                printf("The encrypted text is: %s\n", encrypt(plaintext, key, alphabets));
                return;
        }
        else if(task == 'D'){
                printf("Enter cipher text to decrypt: \n");
                scanf("%s", ciphertext);
                printf("You entered: %s\n", ciphertext);
                int size = strlen(ciphertext);
                if((size % 2) != 0)
                {
                    ciphertext[size] = 'z';
                }
                //Take key input
                inputKey(key);
                // printf("\nThe key is:\n");
                // for(int i = 0;i < 5; i++)
                // {
                //     for(int j = 0;j < 5;j++)
                //     {
                //         printf("%c ",key[i][j]);
                //     }
                //     printf("\n");
                // }  
                printf("The decrypted text is: %s\n", decrypt(ciphertext, key, alphabets));
                return;
        }
        else if(task == 'e')
            return;
        else
            printf("\nYou have selected an incorrect option. Please re-enter.\n");
    }
    return;
}