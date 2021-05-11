#include <stdio.h>
#include <stdlib.h>

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

int multiplicativeInv(int val, int n)
{
    for(int i=0; i<n; i++)
    {
        if((val * i) % n == 1)
        {
            return i;
        }
    }
    return -1;
}
void display(int **A, int m) 
{ 
    for (int i=0; i<m; i++) 
    { 
        for (int j=0; j<m; j++) 
            printf("%d ", A[i][j]); 
        printf("\n"); 
    } 
} 
int main()
{
    int m;
    printf("Enter the dimension of the matrix.\n");
    scanf("%d", &m);

    int **A = (int **)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        A[i] = (int*)malloc(m*sizeof(int));

    printf("Enter the array elements. \n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
            scanf("%d", &A[i][j]);
    }

    printf("\nThe input matrix is : \n");
    display(A, m);
    printf("\n");

    int mod;
    printf("Enter the mod value.\n");
    scanf("%d", &mod);

    int **adj = (int **)malloc(m*sizeof(int*));
    for(int i=0; i<m; i++)
        adj[i] = (int*)malloc(m*sizeof(int));
    adjoint(A, adj, m);
    printf("\n%d\n", m);
    printf("\nThe adjoint matrix is : \n");
    display(adj, m);
    printf("\n");

    int det = getDeterminant(A, m);
    printf("The determinant of given matrix is: %d\n", det);
    
    int inv = multiplicativeInv(det, mod);

    if(inv == -1)
    {
        printf("Inverse does not exist.");
        return 0;
    }
    printf("inv = %d\n",inv);
    printf("\nThe Inverse Matrix is : \n");
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
            
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

/*
test case

m = 3

A is
6 24 1
13 16 10
20 17 15

mod = 26

Output:

The adjoint matrix is :
70 -343 224
5 70 -47
-99 378 -216

The determinant of given matrix is: 441

The Inverse Matrix is :
8 5 10
21 8 21
21 12 8
*/