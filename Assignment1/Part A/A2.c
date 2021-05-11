#include<stdio.h>

int main(){ 
    int n = 0, val = 0;
    printf("Enter size of set\n");
    scanf("%d", &n);
    printf("Enter the number to get the Multiplicative inverse\n");
    scanf("%d", &val);
    
    for(int i = 0; i < n ; i++){
        if((i*val) % n == 1){
            printf("\nMultiplicative Inverse is %d\n", i);
            return 0;
        }    
    }
    printf("The Multiplicative inverse does not exist\n");
    
    return 0;
}

/*
test case

n = 26
val = 15

Multiplicative inverse is 7 as (7*15)%26 = 1
*/