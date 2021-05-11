#include <stdio.h>
#include <math.h>

int power(int a, int b, int P)
{
    if (b == 1)
        return a;

    else
        return ((int)pow(a, b)) % P;
}
int main(){
    
    int g,p; //public keys
    int private;
    printf("Enter the public keys : \n");
    printf("Enter g : ");
    scanf("%d",&g);
    printf("Enter p : ");
    scanf("%d",&p);

    printf("Enter your private key : ");
    scanf("%d",&private);

    printf("Generated Public Parameter to send to other party : %d\n",power(g,private,p));

    int shared;
    printf("Enter Public parameter received from the other party : ");
    scanf("%d",&shared);

    printf("Generated Secret Key : %d\n",power(shared,private,p));

}

/*test case
g = 5
p = 17
a = 4
b = 6
Public key of Alice = 5^4 mod 17 = 13
Public key of Bob = 5^6 mod 17 = 2
Secret key obtained by Alice = 2^private key of Alice mod 17 = 2^4 mod 17 = 16
Secret key obtained by Bob = 13^private key of Bob mod 17 = 13^6 mod 17 = 16
*/