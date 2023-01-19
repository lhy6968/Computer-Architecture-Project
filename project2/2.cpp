#include<stdio.h>  
#include <iostream>

#include<malloc.h>

using namespace std;

int new_address(int address,int init_address);

int main()  

{  
	void *va = malloc(6291456);
	cout<<va<<endl;
	int* a=(int*)va;
	*a = 1;
	cout<<a<<endl;
	*(a+1) = '2';
	cout<<a+1<<endl;
	
	uintptr_t number = (uintptr_t)a;
	cout<<number<<endl;
	int new_number = new_address(number,number);
	cout<<new_number<<endl;
	
	
    return 0;  

}  

int new_address(int address,int init_address){
	int newAddress = address - init_address + 4194304;
	return newAddress;
}







