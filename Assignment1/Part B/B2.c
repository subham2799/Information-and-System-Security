#include <stdio.h>
#include <math.h>
int extendedEuclidean(int a, int b, int *s, int *t){
        int a0 = a;
        int b0 = b;
        int t0 = 0;
        *t = 1;
        int s0 = 1;
        *s = 0;
        int q = floor(a0/b0);
        int r = a0 - q * b0;
        while(r > 0){
            int temp = t0 - q * (*t);
            t0 = *t;
            (*t) = temp;
            temp = s0 - q * (*s);
            s0 = (*s);
            (*s) = temp;
            a0 = b0;
            b0 = r;
            q = floor(a0/b0);
            r = a0 - q * b0;
        }
        r = b0;
    return r;
}
int main(){
    int a,b;
    
    printf("Enter the 2 numbers to find GCD.");
    printf("\na: ");
    scanf("%d", &a);
    printf("\nb: ");
    scanf("%d", &b);
    
    
    int s,t;
    int r = extendedEuclidean(a, b, &s, &t);
    
    printf("\nGCD(%d, %d) = %d\n", a, b, r);
    
    printf("\n(The inverse of %d) mod %d is %d", b, a, (t+a)%a);

}