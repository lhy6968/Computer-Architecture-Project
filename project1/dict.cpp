#include <map>

#include<vector>

#include <string>  
  
#include <iostream>  

#include <sstream>
#include<string.h>

using namespace std;  

//函数声明
string dec_to_binary(int i, int x); 



string register_to_binary(string registers,vector<string> registerList); 



int findElement(vector<string> v, string key);

int main()
{
//创建含instructions具体信息的字典 
    map<string, vector<string> > all_instructions;

    vector<string> add;
  	add.push_back("R");
  	add.push_back("000000");
  	add.push_back("4");
  	add.push_back("2");
  	add.push_back("3");
  	add.push_back("00000");
  	add.push_back("100000");
  	
  	vector<string> addu;
  	addu.push_back("R");
  	addu.push_back("000000");
  	addu.push_back("4");
  	addu.push_back("2");
  	addu.push_back("3");
  	addu.push_back("00000");
  	addu.push_back("100001");
  	
	vector<string> addi;
  	addi.push_back("I");
  	addi.push_back("001000");
  	addi.push_back("3");
  	addi.push_back("2");
  	addi.push_back("4");

	vector<string> addiu;
  	addiu.push_back("I");
  	addiu.push_back("001001");
  	addiu.push_back("3");
  	addiu.push_back("2");
  	addiu.push_back("4");
  	
  	vector<string>AND;
  	AND.push_back("R");
  	AND.push_back("000000");
  	AND.push_back("4");
  	AND.push_back("2");
  	AND.push_back("3");
  	AND.push_back("00000");
  	AND.push_back("100100");
  	
  	vector<string>andi;
  	andi.push_back("I");
  	andi.push_back("001100");
  	andi.push_back("3");
  	andi.push_back("2");
  	andi.push_back("4");
  	
  	vector<string>div;
  	div.push_back("R");
  	div.push_back("000000");
  	div.push_back("2");
  	div.push_back("3");
  	div.push_back("0000000000");
  	div.push_back("011010");
  	
  	vector<string>divu;
  	divu.push_back("R");
  	divu.push_back("000000");
  	divu.push_back("2");
  	divu.push_back("3");
  	divu.push_back("0000000000");
  	divu.push_back("011011");
  	
  	
  	vector<string>mult;
  	mult.push_back("R");
  	mult.push_back("000000");
  	mult.push_back("2");
  	mult.push_back("3");
  	mult.push_back("0000000000");
  	mult.push_back("011000");
  	
  	
  	vector<string>multu;
  	multu.push_back("R");
  	multu.push_back("000000");
  	multu.push_back("2");
  	multu.push_back("3");
  	multu.push_back("0000000000");
  	multu.push_back("011001");
  	
  	
  	
	vector<string>mul;
	mul.push_back("R");
	mul.push_back("011100");
	mul.push_back("4");
	mul.push_back("2");
	mul.push_back("3");
	mul.push_back("00000");
	mul.push_back("000010");
	
	vector<string>nor;
	nor.push_back("R");
	nor.push_back("000000");
	nor.push_back("4");
	nor.push_back("2");
	nor.push_back("3");
	nor.push_back("00000");
	nor.push_back("100111");
	
	vector<string>OR;
	OR.push_back("R");
	OR.push_back("000000");
	OR.push_back("4");
	OR.push_back("2");
	OR.push_back("3");
	OR.push_back("00000");
	OR.push_back("100101");
	
	vector<string>ori;
	ori.push_back("I");
	ori.push_back("001101");
	ori.push_back("3");
	ori.push_back("2");
	ori.push_back("4");
	
	vector<string>sll;
	sll.push_back("R");
	sll.push_back("000000");
	sll.push_back("00000");
	sll.push_back("4");
	sll.push_back("3");
	sll.push_back("5");
	sll.push_back("000000");
	
	vector<string>sllv;
	sllv.push_back("R");
	sllv.push_back("000000");
	sllv.push_back("4");
	sllv.push_back("3");
	sllv.push_back("2");
	sllv.push_back("00000");
	sllv.push_back("000100");
	
	vector<string>sra;
	sra.push_back("R");
	sra.push_back("000000");
	sra.push_back("00000");
	sra.push_back("4");
	sra.push_back("3");
	sra.push_back("5");
	sra.push_back("000011");
	
	vector<string>srav;
	srav.push_back("R");
	srav.push_back("000000");
	srav.push_back("4");
	srav.push_back("3");
	srav.push_back("2");
	srav.push_back("00000");
	srav.push_back("000111");
	
	vector<string>srl;
	srl.push_back("R");
	srl.push_back("000000");
	srl.push_back("00000");
	srl.push_back("4");
	srl.push_back("3");
	srl.push_back("5");
	srl.push_back("000010");
	
	vector<string>srlv;
	srlv.push_back("R");
	srlv.push_back("000000");
	srlv.push_back("4");
	srlv.push_back("3");
	srlv.push_back("2");
	srlv.push_back("00000");
	srlv.push_back("000110");
	
	
	vector<string>sub;
	sub.push_back("R");
	sub.push_back("000000");
	sub.push_back("4");
	sub.push_back("2");
	sub.push_back("3");
	sub.push_back("00000");
	sub.push_back("100010");
	
	
	vector<string>subu;
	subu.push_back("R");
	subu.push_back("000000");
	subu.push_back("4");
	subu.push_back("2");
	subu.push_back("3");
	subu.push_back("00000");
	subu.push_back("100011");
	
	vector<string>XOR;
	XOR.push_back("R");
	XOR.push_back("000000");
	XOR.push_back("4");
	XOR.push_back("2");
	XOR.push_back("3");
	XOR.push_back("00000");
	XOR.push_back("100110");
	
	
	
	
    all_instructions["add"] = add;
    all_instructions["addu"] = addu;
    all_instructions["addi"] = addi;
    all_instructions["addiu"] = addiu;
    all_instructions["and"] = AND;
    all_instructions["andi"] = andi;
    all_instructions["div"] = div;
    all_instructions["divu"] = divu;
    all_instructions["mult"] = mult;
    all_instructions["multu"] = multu;
    all_instructions["mul"] = mul;
    all_instructions["nor"] = nor;
    all_instructions["or"] = OR;
    all_instructions["ori"] = ori;
    all_instructions["sll"] = sll;
    all_instructions["sllv"] = sllv;
    all_instructions["sra"] = sra;
    all_instructions["srav"] = srav;
    all_instructions["srl"] = srl;
    all_instructions["srlv"] = srlv;
    all_instructions["sub"] = sub;
    all_instructions["subu"] = subu;
    all_instructions["xor"] = XOR;
    
    
//创建register的列表    
    vector<string> registerList;
    registerList.push_back("zero");
    registerList.push_back("at");
    registerList.push_back("v0");
    registerList.push_back("v1");
    registerList.push_back("a0");
    registerList.push_back("a1");
    registerList.push_back("a2");
    registerList.push_back("a3");
    registerList.push_back("t0");
    registerList.push_back("t1");
    registerList.push_back("t2");
    registerList.push_back("t3");
    registerList.push_back("t4");
    registerList.push_back("t5");
    registerList.push_back("t6");
    registerList.push_back("t7");
    registerList.push_back("s0");
    registerList.push_back("s1");
    registerList.push_back("s2");
    registerList.push_back("s3");
    registerList.push_back("s4");
    registerList.push_back("s5");
    registerList.push_back("s6");
    registerList.push_back("s7");
    registerList.push_back("t8");
    registerList.push_back("t9");
    registerList.push_back("k0");
    registerList.push_back("k1") ;   
    registerList.push_back("gp");
    registerList.push_back("sp");
    registerList.push_back("fp");
    registerList.push_back("ra");
    

	
} 




//十进制转换为二进制的函数 
string dec_to_binary (int i,int x)
{
	//局部变量声明
	string binary_number = "";
	int result = 0, temp = i, j = 1;
	while(temp){
		result = result + j*(temp%2);
		temp = temp/2;
		j = j*10;
	}

	stringstream sstr;
	sstr << result;
	string str = sstr.str();
	binary_number = "00000000000000000000000000000000" + str;
	binary_number = binary_number.substr(binary_number.length()-x,binary_number.length()-1);
	return binary_number;	
}


//找到vector中元素对应的下标 
int findElement(vector<string> v, string key){
	int len = v.size();
	for(int i=0; i<len; i++){
		if(v.at(i) == key){
			return i;
		}
	}
	return -1;
}



//将对应的register转换为对应的二进制数字 
string register_to_binary (string registers,vector<string> registerList)
{
	int index = findElement(registerList, registers);
	return dec_to_binary(index,5);
}

//负数转换为二补码
string negative_to_complement(int negative_number){
	
}













