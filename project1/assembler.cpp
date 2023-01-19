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

using namespace std;

//function declaration

//delete comments in asm files that are not related to translation
string clean_instruction(string str);

//gets the instruction name for each line of instruction
string get_instruction_name(string str);

//get the registers for each instruction
vector<string> get_register(string line);

//convert decimal digits to binary
string dec_to_binary(int i, int x); 

//convert register to the corresponding binary digit
string register_to_binary(string registers,vector<string> registerList); 

//find the subscripts of the elements in the vector
int findElement(vector<string> v, string key);

int main() 

{
	//all the global variables
	//create a vector with all registers    
    vector<string> registerList;
    //create a vector to store all the lines read from the asm file 
	vector<string> linesList;	
	//create a vector to store all the machine code translated from each instruction
	vector<string>machineList;
	//find the labels and store them in a map
	//the key of the map is label
	//the value of the map is the location of label
	map<string, int > label_dict;
	//create to store the number translated from instruction as string 
	string numberStr;
	//translate numberStr to int
	int number;
	//store the line number of instruction
	int line_number = 0;
       
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
	
	//open the asm input file 
	ifstream infile;
    string input_file;
    string line; 
    cout<<"please enter the input file name:";    
    cin >> input_file;
    infile.open(input_file.c_str(), ios::in);
    if (!infile)
    {
        cerr << "open " << input_file << "fail" << endl;
        return -1;
    }
    while(!infile.eof())
    {
        if (infile.peek() == EOF)
            break;
        getline(infile, line);     
        linesList.push_back(line);
    }
 
 	//close the asm input file
    infile.close();
    
    //simplify the content in each line	
	for (int i = 0;i < linesList.size();i=i+1 ){
		linesList[i] = clean_instruction(linesList[i]);
	};
		
	
	
	//find the labels and store them in a map
	//the key of the map is label
	//the value of the map is the location of label
	int blank_num = 0;
	for (int i = 0;i<linesList.size();i=i+1){
		if (linesList[i] == ""){
			blank_num += 1;
			continue;
		};				
		string label;
		label = linesList[i].substr(0,linesList[i].find(':'));
		linesList[i] = linesList[i].substr(linesList[i].find(':')+1);
		label_dict[label] = i-blank_num;
		}

	//use for loop to process each line of instruction
	for (int i = 0;i<linesList.size();i=i+1){
		//null line will be passed
		if (linesList[i]==""){
			continue;
		};
		
		//get the instruction name of each line
		string instruction_name = get_instruction_name(linesList[i]);
		vector<string>registers;
		//store all the registers of each line
		registers = get_register(linesList[i]);
		
		//translate each line to machine code according to the instruction name
		if (instruction_name == "add"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100000";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		} 
		else if(instruction_name == "addu"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100001";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
		else if(instruction_name == "addi"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
						};
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}
			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "001000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
		else if(instruction_name == "addiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}	
			};	
			string imm = dec_to_binary(number,16);
			machine_code = "001001" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
		else if(instruction_name == "and"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100100";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
		else if(instruction_name == "andi"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};
			
			string imm = dec_to_binary(number,16);

			machine_code = "001100" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;

			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "div"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + "0000000000011010";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "divu"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + "0000000000011011";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "mult"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + "0000000000011000";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "multu"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + "0000000000011001";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "nor"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100111";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "or"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100101";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "ori"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "001101" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sll"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string shamt = dec_to_binary(number,5);
			machine_code = "00000000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + shamt + "000000";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sllv"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[2],registerList) + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + "00000000100";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sra"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string shamt = dec_to_binary(number,5);
			machine_code = "00000000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + shamt + "000011";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "srav"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[2],registerList) + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + "00000000111";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "srl"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string shamt = dec_to_binary(number,5);
			machine_code = "00000000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + shamt + "000010";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "srlv"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[2],registerList) + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + "00000000110";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sub"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100010";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "subu"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100011";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "xor"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000100110";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "xori"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "001110" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "slt"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000101010";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sltu"){
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[2],registerList) + register_to_binary(registers[0],registerList) + "00000101011";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "lui"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "00111100000" + register_to_binary(registers[0],registerList)  + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "slti"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "001010" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;			
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sltiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "001011" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;			
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "beq"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000100"+ register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "bgez"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000001"+ register_to_binary(registers[0],registerList) + "00001" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "bgezal"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};

				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000001"+ register_to_binary(registers[0],registerList) + "10001" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "bgtz"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000111"+ register_to_binary(registers[0],registerList) + "00000" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}

	else if(instruction_name == "blez"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000110"+ register_to_binary(registers[0],registerList) + "00000" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "bltzal"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000001"+ register_to_binary(registers[0],registerList) + "10000" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "bltz"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr2[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000001"+ register_to_binary(registers[0],registerList) + "00000" + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}	
	else if(instruction_name == "bne"){
		string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[1]));
			string newStr2 = newStr.substr(registers[1].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(isalpha(newStr2[i]))||newStr[i]=='_'||(ispunct(newStr2[i]))){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);				
				}			
			};
		int offsetNum = label_dict[numberStr] - line_number - 1;
		string offset = dec_to_binary(offsetNum,16);
		machine_code = "000101"+ register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}	
	else if (instruction_name == "jalr"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + "00000" + register_to_binary(registers[1],registerList) + "00000001001";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "jr"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + "000000000000000001000";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "teq"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110100";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}	
	else if(instruction_name == "teqi"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01100" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}		
	else if (instruction_name == "tne"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110110";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "tnei"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01110" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "tge"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110000";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "tgeu"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110001";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "tgei"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01000" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "tgeiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01001" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "tlt"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110010";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if (instruction_name == "tltu"){			
			string machine_code;
			machine_code = "000000" + register_to_binary(registers[0],registerList) + register_to_binary(registers[1],registerList)+ "0000000000110011";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "tlti"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};
			
			string imm = dec_to_binary(number,16);

			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01010" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "tltiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr2 = newStr.substr(registers[0].length());
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '){
					continue;
				}
				else{
					int i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				if (i == newStr2.length()){
        				i += 1;
        				break;
					};		
					};
				numberStr = newStr2.substr(i_beg,i-i_beg);
				number = atoi(numberStr.c_str());
				}			
			};			
			string imm = dec_to_binary(number,16);
			machine_code = "000001" + register_to_binary(registers[0],registerList)  + "01011" + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}	
	else if(instruction_name == "lb"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "100000"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "lbu"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);
		
		machine_code = "100100"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "lh"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "100001"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "lhu"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);
		
		machine_code = "100101"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name == "lw"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "100011"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "lwl"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);
		
		machine_code = "100010"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "lwr"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);
		
		machine_code = "100110"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "ll"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "110000"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "sb"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "101000"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "sh"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "101001"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "sw"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "101011"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "swl"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "101010"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "swr"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "101110"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name == "sc"){ 
		string machine_code;
		string newStr = linesList[i].substr(linesList[i].find(registers[0]));
		string newStr2 = newStr.substr(registers[0].length());
		int number_beg = 0;
		int number_end = 0;
		for (int i = 0;i<newStr2.length();i=i+1){
			if (newStr2[i]==','||newStr2[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr2[i])||(newStr2[i]=='-')){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr2.substr(number_beg,number_end-number_beg);
		number = atoi(numberStr.c_str());
		string offset = dec_to_binary(number,16);		
		machine_code = "111000"+ register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + offset;
		line_number = line_number + 1;
		machineList.push_back(machine_code);	
	}
	else if(instruction_name=="mfhi"){
		string machine_code;
		machine_code = "0000000000000000"+ register_to_binary(registers[0],registerList) + "00000010000";
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name=="mflo"){
		string machine_code;
		machine_code = "0000000000000000"+ register_to_binary(registers[0],registerList) + "00000010010";
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name=="mthi"){
		string machine_code;
		machine_code = "000000"+ register_to_binary(registers[0],registerList) + "000000000000000010001";
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if(instruction_name=="mtlo"){
		string machine_code;
		machine_code = "000000"+ register_to_binary(registers[0],registerList) + "000000000000000010011";
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if (instruction_name=="j"){
		string machine_code;
		int number_beg = 0;
		int number_end = 0;
		string newStr = linesList[i].substr(linesList[i].find(instruction_name)+1);
		for (int i = 0;i<newStr.length();i=i+1){
			if (newStr[i]==','||newStr[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr[i]) || (isalpha(newStr[i])) || newStr[i]=='_'||(ispunct(newStr[i]))){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr.substr(number_beg,number_end-number_beg);
		int targetNum;
		for (int i = 0;i<numberStr.length();i=i+1){
			if (isalpha(numberStr[i])){
				targetNum = label_dict[numberStr];
				break;
			} 
			else{
				if (i>=numberStr.length()){
					targetNum = atoi(numberStr.c_str());
					break;
				}
				continue;
			}
		}
		string target = dec_to_binary(targetNum,26);
		machine_code = "000010"+ target;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
	else if (instruction_name=="jal"){
		string machine_code;
		int number_beg = 0;
		int number_end = 0;
		string newStr = linesList[i].substr(linesList[i].find(instruction_name)+3);
		for (int i = 0;i<newStr.length();i=i+1){
			if (newStr[i]==','||newStr[i]==' '){
				continue;
			}
			else{
					number_beg = i;
					break;	
					};
			};
		for (int i = number_beg;i>=0;i=i+1){
			if (isdigit(newStr[i]) || (isalpha(newStr[i]) )||newStr[i]=='_'||(ispunct(newStr[i]))){
				continue;
			}
			else{
				number_end = i;
				break;
			}
		}
		string numberStr = newStr.substr(number_beg,number_end-number_beg);
		int targetNum;
		for (int i = 0;i<numberStr.length();i=i+1){
			if (isalpha(numberStr[i])){
				targetNum = label_dict[numberStr];
				break;
			} 
			else{
				if (i>=numberStr.length()){
					targetNum = atoi(numberStr.c_str());
					break;
				}
				continue;
			}
		}
		string target = dec_to_binary(targetNum,26);
		machine_code = "000011"+ target;
		line_number = line_number + 1;
		machineList.push_back(machine_code);
	}
};
	
	//create the output_file name 
	string out_file;
	cout<<"please enter the output file:"; 
	cin >> out_file;
	ofstream out;
    out.open(out_file.c_str());
    if (out.is_open())
    {
    for (int i = 0;i < machineList.size();i=i+1 ){
    	//write the machine code to the output txt file
		out<<machineList[i];
		out<<"\n";
	};
        out.close();
    }
}

//clean comments and others which do not related to the translation
string clean_instruction(string str){
	string::size_type idx;
	string comment = "#";
	idx=str.find(comment);
	string newStr;
	//exist comment 
	if(idx != string::npos ){
        str = str.substr(0,str.find(comment)-1);
    };
    //delete the space and \t at the beginning of each line 
    while((str[0] == '\t') or (str[0] == ' ')){
    	str = str.substr(1);
	}	
	//delete the \n at the end of each line
	string::size_type idx2;
	string comment2 = "\n";
	idx2=str.find(comment2);
	string newStr2;
	//exist comment
	if(idx2 != string::npos ){
        str = str.substr(0,str.find(comment)-1);
    };
    return str;
} 

//get the instruction name of each instruction
string get_instruction_name(string str){
	while((str[0] == '\t') or (str[0] == ' ')){
    	str = str.substr(1);
	};
	int po = min(str.find(" "),str.find("\t"));
	if (po==-1){
		po = max(str.find(" "),str.find("\t"));
	}
	string name = str.substr(0,po);
	return name;	
}

//get the register for each row and store them in order
vector<string> get_register(string line){	
	vector <string> registers;	
	while(line.find("$")<=line.length()){
		int reg_beg,reg_end;
        reg_beg = line.find("$") + 1;
        reg_end = reg_beg + 1;
        while(isdigit(line[reg_end])||islower(line[reg_end])){
        	reg_end += 1;
        	if (reg_end == line.length()){
        		reg_end += 1;
        		break;
			};		
			};
		string registerOne = line.substr(reg_beg,reg_end-reg_beg);
        line = 	line.replace(line.find("$"),1," ");
		registers.push_back(registerOne);
			}
	return registers;
		};

//convert register to the corresponding binary digit
string register_to_binary (string registers,vector<string> registerList)
{
	int index = findElement(registerList, registers);
	return dec_to_binary(index,5);
}

//base to binary
string dec_to_binary (int i,int x)
{
	if (i>=0){
		string binary_number;
		string newStr = "";
		while (i!=0){
		int subNum = i%2;
		i = i/2;
		stringstream ss;
		ss << subNum;
		string subStr;
		ss >> subStr;
		newStr = subStr + newStr;
	}
		binary_number = "00000000000000000000000000000000" + newStr;
		binary_number = binary_number.substr(binary_number.length()-x,binary_number.length()-1);
		return binary_number;	
		}
	else{
		i = -i;
		string binary_number;
		string newStr = "";
		while (i!=0){
		int subNum = i%2;
		i = i/2;
		stringstream ss;
		ss << subNum;
		string subStr;
		ss >> subStr;
		newStr = subStr + newStr;
	};

		binary_number = "00000000000000000000000000000000" + newStr;
		binary_number = binary_number.substr(binary_number.length()-x,binary_number.length()-1);
		binary_number = "1" + binary_number.substr(1);
		for (int i = 1;i < binary_number.length();i=i+1){

			if (binary_number[i]=='0'){
				binary_number = binary_number.substr(0,i) + "1" +binary_number.substr(i+1);
			}
			else{
				binary_number = binary_number.substr(0,i) + "0" +binary_number.substr(i+1);
			}
		}
		for (int i = binary_number.length() - 1;i>=0;i = i - 1){
			if (binary_number[i]=='0'){
				binary_number = binary_number.substr(0,i) + "1" +binary_number.substr(i+1);
				break;
			}
			else{
				binary_number = binary_number.substr(0,i) + "0" +binary_number.substr(i+1);
			}
		}
		return binary_number;
	}
}

//find the subscripts of the elements in the vector 
int findElement(vector<string> v, string key){
	int len = v.size();
	for(int i=0; i<len; i++){
		if(v.at(i) == key){
			return i;
		}
	}
	return -1;
}









