#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LIMIT 500

//Taking Key Input
void inputKey(char **key, int b)
{
    char temp[MAX_LIMIT];
    printf("Enter the key: \n");
    scanf("%s", temp);
    int k = 0;
    for(int i = 0; i < b; i++)
    {
        for(int j = 0;j < b; j++)
        {
            if(temp[k] >= 97 && temp[k] <= 122){
                temp[k] = temp[k] - 32;
            }
            key[i][j] = temp[k];
            k++;
        }
    }      
}

//Function to Display Matrix
void display(int **A, int m) 
{ 
    for (int i=0; i<m; i++) 
    { 
        for (int j=0; j<m; j++) 
            printf("%d ", A[i][j]); 
        printf("\n"); 
    } 
}

//Encryption Function
void encrypt(char plaintext[MAX_LIMIT], char **key, int b, char alphabets[26])
{
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
        
        for(int row = 0; row < b; row++)
        {
            temp2[row] = 0;
            for(int col = 0; col < b; col++)
            {
                temp2[row] += temp1[col] * (key[row][col] - 65);
            }
            temp2[row] = temp2[row] % 26;
            ciphertext[i+row] = alphabets[temp2[row]]; 
        }
    }
    printf("The encrypted text is: %s\n", ciphertext);
    
    return;
}

void getCofactor(int** A, int** temp, int p, int q, int m) 
{ 
    
    int i = 0, j = 0; 
    

    for (int row = 0; row < m; row++) 
    { 
        for (int col = 0; col < m; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
                if (j == m - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int getDeterminant(int** A, int n) 
{ 
    
    int Det = 0; 
  
    
    if (n == 1) 
        return A[0][0]; 
  
    
    int **temp = (int **)malloc(n*sizeof(int *));
    for(int i=0; i<n; i++)
        temp[i] = (int*)malloc(n*sizeof(int));


    int sign = 1;
  
    for (int f = 0; f < n; f++) 
    { 
        getCofactor(A, temp, 0, f, n); 
        Det += sign * A[0][f] * getDeterminant(temp, n-1); 
        sign = -sign; 
    } 
  
    return Det; 
}

//Adjoint of the Matrix
void adjoint(int** A, int** adj, int n) 
{ 
    if (n == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 

    int sign = 1;
    int **temp = (int **)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++)
        temp[i] = (int*)malloc(n*sizeof(int));

    for (int i=0; i<n; i++) 
    { 
        for (int j=0; j<n; j++) 
        { 
            getCofactor(A, temp, i, j, n); 
  
            sign = ((i+j)%2==0)? 1: -1; 
  
            adj[j][i] = (sign)*(getDeterminant(temp, n-1)); 
        } 
    }
} 

//Multiplicative inverse using Extended Euclidean
int multiplicativeInv(int a, int b, int *gcd){
        int a0 = a;
        int b0 = b;
        int t0 = 0;
        int t = 1;
        int s0 = 1;
        int s = 0;
        int q = floor(a0/b0);
        int r = a0 - q * b0;
        while(r > 0){
            int temp = t0 - (q * t);
            t0 = t;
            t = temp;
            temp = s0 - (q * s);
            s0 = s;
            s = temp;
            a0 = b0;
            b0 = r;
            q = floor(a0/b0);
            r = a0 - q * b0;
        }
        r = b0;
        *gcd = r;
    return t;
}

//Function to get inverse matrix of Key
void invertKey(char **key, int m)
{
    int **A = (int **)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        A[i] = (int*)malloc(m*sizeof(int));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
            A[i][j] = key[i][j] - 65;
    }

    int **adj = (int **)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        adj[i] = (int*)malloc(m*sizeof(int));

    adjoint(A, adj, m);
    //printf("\n%d\n", m);
    //printf("\nThe adjoint matrix is : \n");
    //display(adj, m);
    //printf("\n");

    int mod = 26;

    int det = getDeterminant(A, m);
    //printf("The determinant of given matrix is: %d\n", det);

    int gcd = 0;
    int inv = multiplicativeInv(mod, det, &gcd);
    
    inv = (inv + mod) % mod;

    if(gcd != 1)
    {
        printf("Inverse does not exist.");
        return;
    }

    //printf("inv = %d\n",inv);

    //printf("\nThe Inverse Matrix is : \n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(adj[i][j]<=0)
                adj[i][j] = mod - abs(adj[i][j]) % mod;
            else
                adj[i][j] = adj[i][j] % mod;
            adj[i][j] = adj[i][j] * inv;
            adj[i][j] = adj[i][j] % mod;

            key[i][j] = adj[i][j] + 65;
            //printf("%d ", adj[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");
}

//Decryption Function
void decrypt(char ciphertext[MAX_LIMIT], char **key, int b, char alphabets[26])
{
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
        
        for(int row = 0; row < b; row++)
        {
            temp2[row] = 0;
            for(int col = 0; col < b; col++)
            {
                temp2[row] += temp1[col] * (key[row][col] - 65);
            }
            temp2[row] = temp2[row] % 26;
            plaintext[i+row] = alphabets[temp2[row]]; 
        }
    }
    printf("The decrypted text is: %s\n", plaintext);
    
    return;
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
    
    printf("1.To encrypt, enter E\n2.To decrypt, enter D\n3.Enter e to exit\n");
    while(1)
    {
        scanf("%c",&task);
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
                
                char **key = (char **)malloc(b*sizeof(char*));
                for(int i=0; i<b; i++){
                    key[i] = (char*)malloc(b*sizeof(char));
                }

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
                scanf("%s", ciphertext);
                printf("You entered: %s\n", ciphertext);

                int size = strlen(ciphertext);
                int b = 0; 
                printf("\nEnter block size: \n");
                scanf("%d",&b);

                
                char **key = (char **)malloc(b*sizeof(char*));
                for(int i=0; i < b; i++){
                    key[i] = (char*)malloc(b*sizeof(char));
                }

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