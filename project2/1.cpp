#include<stdio.h>  
#include <iostream>

#include<malloc.h>

using namespace std;



int main()  

{  
    int *p;  

    p=(int *)malloc(6291456);
    *p = 1;
    printf("p = %p\n", p);
    printf("p+1 = %p\n", p+1);
    *(p+4) = '3';
    printf("p+3 = %p\n", p+3);
    
    
    
    
    
    if(p)  

        printf("Memory Allocated at: %x/n",p);  

    else  

        printf("Not Enough Memory!/n");  

    free(p);  

    return 0;  

}















 
