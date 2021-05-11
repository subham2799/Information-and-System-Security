#include <stdio.h>
#include <math.h>

int gcd(int a, int b){
    int r[a*b];
    int q[a*b];
    q[0] = 0;
    r[0] = a;
    r[1] = b;
    int m = 1;
    while(r[m]!=0){
        q[m] = ceil(r[m-1]/r[m]);
        r[m+1] = r[m-1] - q[m]*r[m];
        m++; 
    }
    return r[m-1]; // as r[m] is 0
    /*
    Equivalent of the above
    while(b!=0){
        int t = b;
        b = a % b; // a % b = a - ceil(a/b) * b;
        a = t;
    }
    return a;
    */ 
}

int main(){
    int a,b;
    printf("Enter the 2 numbers to find GCD. \n");
    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    printf("\nThe gcd of %d and %d is %d", a, b, gcd(a, b));
}
