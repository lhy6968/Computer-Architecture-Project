#include<stdio.h>  
#include <iostream>
#include<string>
#include<malloc.h>
#include <vector> 
#include <string> 
#include <fstream> 
#include <iostream> 
#include <map>
#include<stdlib.h>
#include <stdio.h> 
#include <map>
#include <sstream>
#include <iostream>   
#include <string.h>
#include<malloc.h>
#include<bitset>
#include<math.h>
using namespace std;
int binStr_to_decInt(string str);


int main()  

{  
	string ax = "111000";
	if (ax=="111000"){
		cout<<"this is ax"<<endl;
	}



	string a1 = "123";
	a1 = a1 + '\0';
	cout<<a1.length()<<endl;
	void *va = malloc(6291456);
	char *p = (char *)(va);
	*p = 'w';
	*(p+1) = 'r';
	int *a = (int *)(p+2);
	*a = 1;
	*(a+1)= 2;
	uintptr_t m1 = (uintptr_t)a;
	uintptr_t m2 = (uintptr_t)(a+1);
	uintptr_t m3 = (uintptr_t)(p+2);
	uintptr_t m4 = (uintptr_t)(p+3);
	uintptr_t m5 = (uintptr_t)(p+10);
	uintptr_t m6 = (uintptr_t)(p+11);
	cout<<m1<<endl;
	cout<<m2<<endl;
	cout<<m3<<endl;
	cout<<m4<<endl;
	cout<<m5<<endl;
	cout<<m6<<endl;
//	char * p_data = £¨char *£©£¨p_start + 1mb£©
	*a = 12;
	*(a+1) = 13;
	
	


	

}




int binStr_to_decInt(string str){
	int number = 0;
	int bit = 0;
	for (int i = str.length()-1;i>=0;i=i-1){
		if (str[i]=='1'){
			cout<<bit<<endl;
			cout<<number<<endl;
			number = number + pow(2,bit);
			cout<<number<<endl;
			bit = bit + 1;
		}
		else{
			bit = bit + 1;
		}
	}
	return number;
} 

