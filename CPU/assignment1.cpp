#include<stdio.h>

int main(){
    long long operations = 10000000000;
    long long count = 0;
    
    for (long long i = 0; i<operations; i++){
        count = count + 1;
    }

    printf("count of operations  %lld\n",count);
}