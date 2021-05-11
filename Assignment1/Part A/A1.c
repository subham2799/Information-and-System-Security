#include<stdio.h>

int main(){ 
    int n = 0, val = 0;
    printf("Enter size of set\n");
    scanf("%d", &n);
    printf("\nEnter the number to get the additive inverse\n");
    scanf("%d", &val);
    
    int inv = 0;
    for(int i = 0; i < n ; i++){
        if((val+i) % n == 0){
            printf("\nAdditive Inverse is %d\n", i);
            return 0;
        }    
    }
    printf("The additive inverse does not exist\n");
    
    return 0;
}

/*
test case

n = 26
val = 15

Additive inverse is 11 as (11+15)%26 = 0
*/