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
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
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

int binStr_to_decInt(string str);

int new_address(int address,int init_address);

string long_dec_to_binary (long i,int x);

int binReg_to_decInt(string str);

void addi_func (int* rs, int imm,int* rt);

void add_func (int* rs, int* rt,int* rd);

int bne_func(int* rs,int *rt,int pc,int offset);

void sub_func(int* rs,int* rt,int* rd);

void lw_func(int* rs,int* rt,int offset);

void sw_func(int* rt,int* rs,int offset);

void lui_func(int* rt,int imm);

void ori_func(int* rs,int imm,int* rt);

int jal_func(int pc, int* ra,int target);

int beq_func(int* rs,int *rt,int pc,int offset);

int j_func(int pc,int target);

int jr_func(int* rs);

void addu_func (int* rs, int* rt,int* rd);

void addiu_func (int* rs, int imm,int* rt);

void and_func(int* rs,int* rt,int* rd);

void andi_func(int* rs,int imm,int* rt);

void div_func (int* rs,int* rt,int* lo,int* hi);

void divu_func (int* rs,int* rt,int* lo,int* hi);

void mult_func (int* rs,int* rt,int * lo,int* hi);

void multu_func (int* rs,int* rt,int * lo,int* hi);

void nor_func(int* rs,int* rt,int* rd);

void or_func(int* rs,int* rt,int* rd);

void sll_func (int shamt, int* rt,int* rd);

void sllv_func (int* rs, int* rt,int* rd);

void sra_func (int shamt, int* rt,int* rd);

void srav_func (int* rs, int* rt,int* rd);

void srl_func (int shamt, int* rt,int* rd);

void srlv_func (int* rs, int* rt,int* rd);

void subu_func(int* rs,int* rt,int* rd);

void xor_func(int* rs,int* rt,int* rd);

void xori_func(int* rs,int imm,int* rt);

void slt_func (int* rs, int* rt,int* rd);

void sltu_func (int* rs, int* rt,int* rd);

void slti_func(int* rs, int imm,int* rt);

void sltiu_func(int* rs, int imm,int* rt);

int bgez_func(int* rs,int pc,int offset);

int bgezal_func(int* rs,int pc,int offset);

int bgtz_func(int* rs,int pc,int offset);

int blez_func(int* rs,int pc,int offset);

int bltz_func(int* rs,int pc,int offset);

int bltzal_func(int* rs,int pc,int offset);

int jalr_func(int pc,int *rs,int* rd);

void teq_func(int* rs, int* rt,int pc);

void teqi_func(int* rs,int imm,int pc);

void tne_func(int* rs, int* rt,int pc);

void tnei_func(int* rs,int imm,int pc);

void tge_func(int* rs, int* rt,int pc);

void tgeu_func(int* rs, int* rt,int pc);

void tgei_func(int* rs,int imm,int pc);

void tgeiu_func(int* rs,int imm,int pc);

void tlt_func(int* rs, int* rt,int pc);

void tltu_func(int* rs, int* rt,int pc);

void tlti_func(int* rs,int imm,int pc);

void tltiu_func(int* rs,int imm,int pc);

void mfhi_func(int* rd,int* hi);

void mflo_func(int* rd,int* lo);

void mthi_func(int* rs,int* lo);

void mtlo_func(int* rs,int* lo);

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
    registerList.push_back("k1");   
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
	int begin_num = 0;
	for (int i = 0;i<linesList.size();i=i+1){
		string beg_label = linesList[i].substr(0,5);
		if (beg_label==".text"){
			begin_num = i + 1;
			break;
		}
	}
	for (int i = begin_num;i<linesList.size();i=i+1){
		if (linesList[i] == ""){
			blank_num += 1;
			continue;
		};				
		string label;
		label = linesList[i].substr(0,linesList[i].find(':'));
		linesList[i] = linesList[i].substr(linesList[i].find(':')+1);
		label_dict[label] = i-blank_num-begin_num;
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
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
			string imm = dec_to_binary(number,16);
			machine_code = "001000" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
		else if(instruction_name == "addiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
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
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
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
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());	
			string imm = dec_to_binary(number,16);
			machine_code = "001101" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sll"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
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
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
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
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());	
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
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
			string imm = dec_to_binary(number,16);
			machine_code = "00111100000" + register_to_binary(registers[0],registerList)  + imm;
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "slti"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
			string imm = dec_to_binary(number,16);
			machine_code = "001010" + register_to_binary(registers[1],registerList) + register_to_binary(registers[0],registerList) + imm;			
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		}
	else if(instruction_name == "sltiu"){
			string machine_code;
			string newStr = linesList[i].substr(linesList[i].find(registers[0]));
			string newStr3 = newStr.substr(registers[0].length());
			string newStr1 = newStr3.substr(newStr3.find(registers[1]));
			string newStr2 = newStr1.substr(registers[1].length());			
			int i_beg;
			int i_end;
			for (int i = 0;i<newStr2.length();i=i+1){
				if (newStr2[i]==' '||newStr2[i]==','){
					continue;
				}
				else{
					i_beg = i; 
					while(isdigit(newStr2[i])||(newStr2[i]=='-')){
        				i += 1;
        				i_end = i;
        				if (i == newStr2.length()){
        				i += 1;
        				i_end = i;
        				break;	
					};		
					};
				break;
				}			
			};
			numberStr = newStr2.substr(i_beg,i_end-i_beg);
			number = atoi(numberStr.c_str());
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
	else if(instruction_name == "syscall"){
			string machine_code;
			machine_code = "00000000000000000000000000001100";
			line_number = line_number + 1;
			machineList.push_back(machine_code);
		
	}
};

	//创建所有的register模拟器 
	void *hi_void = malloc(4);
	void *lo_void = malloc(4);

	void *registers = malloc(128);
	
	//PC指针到底怎么创建
	int pc = 0;
	
	void *va = malloc(6291456);
	
	int *a = (int *)va;
	
	int order = 0;
	for (int i = 0;i<machineList.size();i=i+1){
		int n = binStr_to_decInt(machineList[i]);
		*(a+order) = n;
		order = order + 1;
		};
	
	char *b = (char *)(a+262144);
	int order2 = 0;
				
	for (int i = 0;i < linesList.size();i=i+1 ){
		if (linesList[i].find(".asciiz")!=-1){
			string newStr = linesList[i].substr(linesList[i].find("\"")+1);
			int location = newStr.find("\"");
			string asciizStr = linesList[i].substr(linesList[i].find("\"")+1,location);
			asciizStr = asciizStr + '\0';
			int remainder = asciizStr.length() % 4;
			int left;
			if (remainder == 0){
				left = 0;
			}
			else{
				left = 4 - remainder;
			}
			for (int j = 0;j< asciizStr.length();j = j+1){
				*(b+order2) = asciizStr[j];
				order2 = order2 + 1;
			}
			order2 = order2 + left;
		}
		else if (linesList[i].find(".word")!=-1){
			vector<int>wordList;
			string subWordStr = linesList[i].substr(linesList[i].find(".word")+5);
			while (subWordStr.find(",")!=-1){
				int word;
				string wordStr = subWordStr.substr(0,subWordStr.find(","));
				stringstream s1;  
    			s1 << wordStr;                  
    			s1 >> word;
    			wordList.push_back(word);
    			subWordStr = subWordStr.substr(subWordStr.find(",")+1);
			}
			int lastWord;
			stringstream s2;
			s2 << subWordStr;                  
    		s2 >> lastWord;
			wordList.push_back(lastWord);
			int *c = (int *)(b+order2);
			for (int i = 0;i<wordList.size();i=i+1){
				*(c+i) = wordList[i];
				order2 = order2 + 4;
			}
		}
		else if (linesList[i].find(".half")!=-1){
			vector<int>wordList;
			string subWordStr = linesList[i].substr(linesList[i].find(".half")+5);
			while (subWordStr.find(",")!=-1){
				int word;
				string wordStr = subWordStr.substr(0,subWordStr.find(","));
				stringstream s1;  
    			s1 << wordStr;                  
    			s1 >> word;
    			wordList.push_back(word);
    			subWordStr = subWordStr.substr(subWordStr.find(",")+1);
			}
			int lastWord;
			stringstream s2;
			s2 << subWordStr;                  
    		s2 >> lastWord;
			wordList.push_back(lastWord);
			short *c = (short *)(b+order2);
			for (int i = 0;i<wordList.size();i=i+1){
				*(c+i) = wordList[i];
				order2 = order2 + 2;
			}
		}
		else if (linesList[i].find(".ascii")!=-1){
			string newStr = linesList[i].substr(linesList[i].find("\"")+1);
			int location = newStr.find("\"");
			string asciizStr = linesList[i].substr(linesList[i].find("\"")+1,location);
			int remainder = asciizStr.length() % 4;
			int left;
			if (remainder == 0){
				left = 0;
			}
			else{
				left = 4 - remainder;
			}
			for (int j = 0;j< asciizStr.length();j = j+1){
				*(b+order2) = asciizStr[j];
				order2 = order2 + 1;
			}
			order2 = order2 + left;
		}
		else if (linesList[i].find(".byte")!=-1){
			vector<char>byteList;
			string subWordStr = linesList[i].substr(linesList[i].find(".byte")+5);
			char byteStr;
			while (subWordStr.find(",")!=-1){
				for (int i = 0;i<subWordStr.length();i=i+1){
				if (subWordStr[i]!=' '){
					byteStr = subWordStr[i];
					byteList.push_back(byteStr);
					break;
				}
			}
				subWordStr = subWordStr.substr(subWordStr.find(",")+1);
			}
			char lastByte;
			for (int i = 0;i<subWordStr.length();i=i+1){
				if (subWordStr[i]!=' '){
					lastByte = subWordStr[i];
					byteList.push_back(lastByte);
					break;
				}
			}
			char *c = (char *)(b+order2);
			for (int i = 0;i<byteList.size();i=i+1){
				*(c+i) = byteList[i];
				order2 = order2 + 1;					
			}
		}		
	};
//	cout<<b+92<<endl;
//	cout<<b+1<<endl;
//	cout<<b<<endl;
//	cout<<*(b+38)<<endl;
//	cout<<*(b+39)<<endl;
//	cout<<*(b+40)<<endl;
//	cout<<*(b+1)<<endl;
	//这个指针用于记录data部分到哪里结束了
	char *static_data_end =  (char *)(b+order2);
	uintptr_t mm = (uintptr_t)static_data_end;
	uintptr_t m = (uintptr_t)va;
	int *register1 = (int *)registers;
	*register1 = 0;
	*(register1+2) = 0;
	*(register1+3) = 0;
	*(register1+4) = 0;
	*(register1+5) = 0;
	*(register1+6) = 0;
	*(register1+7) = 0;
	*(register1+8) = 0;
	*(register1+9) = 0;
	*(register1+10) = 0;
	*(register1+11) = 0;
	*(register1+12) = 0;
	*(register1+13) = 0;
	*(register1+14) = 0;
	*(register1+15) = 0;
	*(register1+16) = 0;
	*(register1+17) = 0;
	*(register1+18) = 0;
	*(register1+19) = 0;
	*(register1+20) = 0;
	*(register1+21) = 0;
	*(register1+22) = 0;
	*(register1+23) = 0;
	
	
	
	//专门用来记录可以从哪个位置开始取 
	int sbrk_number = 0;
	
	int data_end = new_address(mm,m);

		
	int new_number = new_address(m,m);
	*(register1+29) = new_number + 6291456;	
	*(register1+30) = new_number + 6291456;
	*(register1+28) = new_number + 1048576; 
	pc = new_number;

	//offset = (pc - new_number)/4;
	
	int *zero1 = (int *)registers;
	*zero1 = 0; 

	while (abs((pc-new_number)/4)< machineList.size()){
		int offset = (pc - new_number)/4;
		string instruction = dec_to_binary(*(a+offset),32);
		string instruction1 = instruction.substr(0,6);
		string instruction2 = instruction.substr(21,5);
		string instruction3 = instruction.substr(26,6);
		string instruction4 = instruction.substr(11,5);

		if ((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="100000")){
	//		cout<<"this is add"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			add_func ((register1+rs), (register1+rt),(register1+rd));
			if ((*(register1+rd)>0)&&(*(register1+rs)<0)&&(*(register1+rt)<0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			else if((*(register1+rd)<0)&&(*(register1+rs)>0)&&(*(register1+rt)>0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="100001")){
	//		cout<<"this is addu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			addu_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if(instruction1=="001000"){
	//		cout<<"this is addi"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			cout<<*(register1+rs)<<endl;
			cout<<*(register1+rt)<<endl;
			addi_func ((register1+rs), imm,(register1+rt));
			cout<<*(register1+rs)<<endl;
			cout<<*(register1+rt)<<endl;
			if ((*(register1+rt)>0)&&(*(register1+rs)<0)&&(imm<0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			else if((*(register1+rt)<0)&&(*(register1+rs)>0)&&(imm>0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			pc = pc + 4;
		}
		else if(instruction1=="001001"){
	//		cout<<"this is addiu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			addiu_func ((register1+rs), imm,(register1+rt));
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="100100")){
	//		cout<<"this is and"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			and_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if(instruction1=="001100"){
	//		cout<<"this is andi"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			andi_func ((register1+rs), imm,(register1+rt));
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="011010")){
	//		cout<<"this is div"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			if (*(register1+rt)==0){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			div_func ((register1+rs),(register1+rt),lo,hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="011011")){
	//		cout<<"this is divu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			divu_func ((register1+rs),(register1+rt),lo,hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="011000")){
	//		cout<<"this is mult"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			mult_func ((register1+rs),(register1+rt),lo,hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="011001")){
	//		cout<<"this is multu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			multu_func ((register1+rs),(register1+rt),lo,hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="100111")){
	//		cout<<"this is nor"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			nor_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="100101")){
	//		cout<<"this is or"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			or_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if(instruction1=="001101"){
	//		cout<<"this is ori"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			ori_func((register1+rs),imm,(register1+rt));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000000")){
	//		cout<<"this is sll"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			string shamtStr = instruction.substr(21,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int shamt = binReg_to_decInt(shamtStr);
			int *register1 = (int *)registers;
			cout<<*(register1+rt)<<endl;
			cout<<*(register1+rd)<<endl;
			sll_func (shamt, (register1+rt),(register1+rd));
			cout<<*(register1+rt)<<endl;
			cout<<*(register1+rd)<<endl;
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000100")){
	//		cout<<"this is sllv"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			sllv_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000011")){
	//		cout<<"this is sra"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			string shamtStr = instruction.substr(21,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int shamt = binReg_to_decInt(shamtStr);
			int *register1 = (int *)registers;
			sra_func (shamt, (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000111")){
	//		cout<<"this is srav"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			srav_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000010")){
	//		cout<<"this is srl"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			string shamtStr = instruction.substr(21,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int shamt = binReg_to_decInt(shamtStr);
			int *register1 = (int *)registers;
			srl_func (shamt, (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="000110")){
	//		cout<<"this is srlv"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			srlv_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="100010")){
	//		cout<<"this is sub"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			sub_func((register1+rs), (register1+rt),(register1+rd));
			if ((*(register1+rs)<*(register1+rt))&&(*(register1+rd)>0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			else if ((*(register1+rs)>*(register1+rt))&&(*(register1+rd)<0)){
				printf("exception occurs at %d",pc);
				exit(1);
			}
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="100011")){
	//		cout<<"this is subu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			subu_func((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if ((instruction1=="000000")&&(instruction3=="100110")){
	//		cout<<"this is xor"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			xor_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if (instruction1=="001110"){
	//		cout<<"this is xori"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			xori_func((register1+rs),imm,(register1+rt));
			pc = pc + 4;
		}
		else if (instruction1=="001111"){
	//		cout<<"this is lui"<<endl;
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			lui_func((register1+rt),imm);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="101010")){
	//		cout<<"this is slt"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			slt_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="101011")){
	//		cout<<"this is sltu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5); 
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			sltu_func ((register1+rs), (register1+rt),(register1+rd));
			pc = pc + 4;
		}
		else if (instruction1=="001010"){
	//		cout<<"this is slti"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			slti_func((register1+rs),imm,(register1+rt));
			pc = pc + 4;
		}
		else if (instruction1=="001011"){
	//		cout<<"this is sltiu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			sltiu_func((register1+rs),imm,(register1+rt));
			pc = pc + 4;
		}
		else if (instruction1=="000100"){
	//		cout<<"this is beq"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = beq_func((register1+rs),(register1+rt),pc,offset);
		}
		else if ((instruction1=="000001")&&(instruction4=="00001")){
			cout<<"this is bgez"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = bgez_func((register1+rs),pc,offset);
		}
		else if ((instruction1=="000001")&&(instruction4=="10001")){
			cout<<"this is bgezal"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			*(register1+31) = pc;
			pc = bgezal_func((register1+rs),pc,offset);
		}
		else if ((instruction1=="000111")&&(instruction4=="00000")){
			cout<<"this is bgtz"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = bgtz_func((register1+rs),pc,offset);
		}
		else if ((instruction1=="000110")&&(instruction4=="00000")){
			cout<<"this is blez"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = blez_func((register1+rs),pc,offset);
		}
		else if ((instruction1=="000001")&&(instruction4=="10000")){
			cout<<"this is bltzal"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			*(register1+31) = pc;
			pc = bltzal_func((register1+rs),pc,offset);
		}
		else if ((instruction1=="000001")&&(instruction4=="00000")){
			cout<<"this is bltz"<<endl;
			string rsStr = instruction.substr(6,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = bltz_func((register1+rs),pc,offset);
		}
		else if (instruction1=="000101"){
			cout<<"this is bne"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			pc = bne_func((register1+rs),(register1+rt),pc,offset);

		}
		else if (instruction1=="000010"){
			cout<<"this is j"<<endl;
			string targetStr = instruction.substr(6,26);
			int target = binStr_to_decInt(targetStr);
			pc =  j_func(pc,target);
		}
		else if (instruction1=="000011"){
			cout<<"this is jal"<<endl;
			string targetStr = instruction.substr(6,26);
			int target = binStr_to_decInt(targetStr);
			int *register1 = (int *)registers;
			pc = jal_func(pc, (register1+31),target);
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="001001")){
			cout<<"this is jalr"<<endl;
			string rsStr = instruction.substr(6,5);
			string rdStr = instruction.substr(16,5);
			int rs = binReg_to_decInt(rsStr);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			pc = jalr_func(pc, (register1+rs),(register1+rd));
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="001000")){
			cout<<"this is jr"<<endl;
			string rsStr = instruction.substr(6,5);
			int rs = binReg_to_decInt(rsStr);
			int *register1 = (int *)registers;
			pc = jr_func((register1+rs));
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110100")){
			cout<<"this is teq"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			teq_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01100")){
			cout<<"this is teqi"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			teqi_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110110")){
			cout<<"this is tne"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			tne_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01110")){
			cout<<"this is tnei"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			tnei_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110000")){
			cout<<"this is tge"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			tge_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110001")){
			cout<<"this is tgeu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			tgeu_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01000")){
			cout<<"this is tgei"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			tgei_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01001")){
			cout<<"this is tgeiu"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			tgeiu_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110010")){
			cout<<"this is tlt"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			tlt_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="110011")){
			cout<<"this is tltu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int *register1 = (int *)registers;
			tltu_func((register1+rs),(register1+rt),pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01010")){
			cout<<"this is tlti"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			tlti_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if ((instruction1=="000001")&&(instruction4=="01011")){
			cout<<"this is tltiu"<<endl;
			string rsStr = instruction.substr(6,5);
			string immStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int imm = binStr_to_decInt(immStr);
			int *register1 = (int *)registers;
			tltiu_func((register1+rs),imm,pc);
			pc = pc + 4;
		}
		else if (instruction1=="100000"){
			cout<<"this is lb"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			char *lb = (char *)(a + (address-4194304)/4);
			int lb_int = *lb;
			*(register1+rt) = lb_int;
			pc = pc + 4;
		}
		else if (instruction1=="100100"){
			cout<<"this is lbu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			char *lb = (char *)(a + (address-4194304)/4);
			int lb_int = *lb;
			*(register1+rt) = lb_int;
			pc = pc + 4;
		}
		else if (instruction1=="100001"){
			cout<<"this is lh"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			short *lh = (short *)(a + (address-4194304)/4);
			int lh_int = *lh;
			*(register1+rt) = lh_int;
			pc = pc + 4;
		}
		else if (instruction1=="100101"){
			cout<<"this is lhu"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			short *lh = (short *)(a + (address-4194304)/4);
			int lh_int = *lh;
			*(register1+rt) = lh_int;
			pc = pc + 4;
		}
		else if (instruction1=="100011"){
			cout<<"this is lw"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			*(register1+rt) = *(a + (address-4194304)/4);
			lw_func((register1+rs),(register1+rt),offset);
			pc = pc + 4;
		}
		else if (instruction1=="100010"){
			cout<<"this is lwl"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int lwl = *(a + (address-4194304)/4);
			string lwlStr = dec_to_binary (lwl,32);
			string part1 = lwlStr.substr(0,16);
			int rt1 = *(register1+rt);
			string rt1Str = dec_to_binary (rt1,32);
			string part2 = rt1Str.substr(0,16);
			string all = part2 + part1;
			int result1 = binStr_to_decInt(all);
			*(register1+rt) = result1;
			pc = pc + 4;
		}
		else if (instruction1=="100110"){
			cout<<"this is lwr"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int lwr = *(a + (address-4194304)/4);
			string lwrStr = dec_to_binary (lwr,32);
			string part1 = lwrStr.substr(16,16);
			int rt1 = *(register1+rt);
			string rt1Str = dec_to_binary (rt1,32);
			string part2 = rt1Str.substr(0,16);
			string all = part2 + part1;
			int result1 = binStr_to_decInt(all);
			*(register1+rt) = result1;
			pc = pc + 4;
		}
		else if (instruction1=="110000"){
			cout<<"this is ll"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			*(register1+rt) = *(a + (address-4194304)/4);
			pc = pc + 4;
		}
		else if (instruction1=="101000"){
			cout<<"this is sb"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int sb_int = *(register1+rt);
			string sb3 = dec_to_binary (sb_int,32);
			string sb1 = sb3.substr(24,8);
			int sb1_int = binStr_to_decInt(sb1);
			char *sb2 = (char *)(a + (address-4194304)/4);
			*sb2 = sb1_int;
			pc = pc + 4;
		}
		else if (instruction1=="101001"){
			cout<<"this is sh"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int sh_int = *(register1+rt);
			string sh3 = dec_to_binary (sh_int,32);
			string sh1 = sh3.substr(24,16);
			int sh1_int = binStr_to_decInt(sh1);
			short *sh2 = (short *)(a + (address-4194304)/4);
			*sh2 = sh1_int;
			pc = pc + 4;
		}
		else if (instruction1=="101011"){
			cout<<"this is sw"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			*(a + (address-4194304)/4) = *(register1+rt);
			//sw_func((register1+rt),(register1+rs),offset);
			pc = pc + 4;
		}
		else if (instruction1=="101010"){
			cout<<"this is swl"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int swl = *(a + (address-4194304)/4);
			string swlStr = dec_to_binary (swl,32);
			string part1 = swlStr.substr(0,16);
			int rt1 = *(register1+rt);
			string rt1Str = dec_to_binary (rt1,32);
			string part2 = rt1Str.substr(0,16);
			string all = part1 + part2;
			int result1 = binStr_to_decInt(all);
			*(a + (address-4194304)/4) = result1;
			pc = pc + 4;
		}
		else if (instruction1=="101110"){
			cout<<"this is swr"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			int swl = *(a + (address-4194304)/4);
			string swlStr = dec_to_binary (swl,32);
			string part1 = swlStr.substr(0,16);
			int rt1 = *(register1+rt);
			string rt1Str = dec_to_binary (rt1,32);
			string part2 = rt1Str.substr(16,16);
			string all = part1 + part2;
			int result1 = binStr_to_decInt(all);
			*(a + (address-4194304)/4) = result1;
			pc = pc + 4;
		}
		else if (instruction1=="111000"){
			cout<<"this is sc"<<endl;
			string rsStr = instruction.substr(6,5);
			string rtStr = instruction.substr(11,5);
			string offsetStr = instruction.substr(16,16);
			int rs = binReg_to_decInt(rsStr);
			int rt = binReg_to_decInt(rtStr);
			int offset = binStr_to_decInt(offsetStr);
			int *register1 = (int *)registers;
			int address = *(register1+rs) + offset;
			*(a + (address-4194304)/4) = *(register1+rt);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="010000")){
			cout<<"this is mfhi"<<endl;
			string rdStr = instruction.substr(16,5);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
//			int *lo = (int *)lo_void;
			mfhi_func((register1+rd),hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="010010")){
			cout<<"this is mflo"<<endl;
			string rdStr = instruction.substr(16,5);
			int rd = binReg_to_decInt(rdStr);
			int *register1 = (int *)registers;
//			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			mflo_func((register1+rd),lo);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="010001")){
			cout<<"this is mthi"<<endl;
			string rsStr = instruction.substr(6,5);
			int rs = binReg_to_decInt(rsStr);
			int *register1 = (int *)registers;
			int *hi = (int *)hi_void;
//			int *lo = (int *)lo_void;
			mthi_func((register1+rs),hi);
			pc = pc + 4;
		}
		else if((instruction1=="000000")&&(instruction2=="00000")&&(instruction3=="010011")){
			cout<<"this is mtlo"<<endl;
			string rsStr = instruction.substr(6,5);
			int rs = binReg_to_decInt(rsStr);
			int *register1 = (int *)registers;
//			int *hi = (int *)hi_void;
			int *lo = (int *)lo_void;
			mtlo_func((register1+rs),lo);
			pc = pc + 4;
		}
		else if(instruction=="00000000000000000000000000001100"){
			cout<<"this is syscall"<<endl;
			FILE *fp = NULL; 
			int *v0 = (int *)(zero1 + 2);

			if (*v0 == 5){
				int number1; 
			//	cout<<"please enter an integer: ";
				cin >> number1;
				*v0 = number1;
			}
			else if (*v0 == 1){
			//	cout<<"the integer is:";
				cout<< *(zero1 + 4)<<endl;
			}
			else if (*v0 == 10){
				exit(0);
			}
			else if (*v0 == 12){
				char chara;
			//	cout<<"please enter a char: ";
				cin >> chara;
				int chara_num = chara;
				*v0 = chara_num;
			}
			else if (*v0 == 11){
			//	cout<<"the char is:";
				
				int *a0 = (int *)(v0+2);
				char as = *a0;
				cout<<as<<endl;
			}
			else if (*v0 == 9){				 
				*v0 = data_end + sbrk_number;
				sbrk_number = sbrk_number + *(v0+2);				
			}
			else if (*v0 == 8){
				int a0 = *(v0+2);
				char *read = (char *)(a+(a0-4194304)/4);
			//	printf("please enter a string of length %d: ",*(v0+3));
				string str;
				cin >> str;
				for(int i = 0;i<str.length();i=i+1){
					*read = str[i];
					read = read + 1;
				}
			}
			else if (*v0 == 4){
				char *print_string = (char *)(a+(*(v0+2)-4194304)/4);
				string str;
				while (*print_string != '\0'){
					str = str + *print_string;
					print_string = print_string + 1;
				}
				cout<<str<<endl;
			}
			else if (*v0 == 13){
				char *print_string = (char *)(a+(*(v0+2)-4194304)/4);
				string str;
				while (*print_string != '\0'){
					str = str + *print_string;
					print_string = print_string + 1;
				}
				char *p = (char*)str.c_str();
				//r
				if (*(v0+3)==0){
					fp = fopen(p,"r");
				}
				//w
				else if(*(v0+3)==1){
					fp = fopen(p,"w");
				}
				//rw
				else if(*(v0+3)==2){
					fp = fopen(p,"r+");
				}
				int fd;
				fd = fileno(fp);
				*(v0+2) = fd;		
			}
			else if (*v0 == 14){
				int fd = *(v0+2);
				fp = fdopen(fd,"r");
				*(v0+2) = *(v0+4);
				char buff[255];
				fgets(buff,*(v0+4),(FILE*)fp);
				int a1 = *(v0+3);
				char *read = (char *)(a+(a1-4194304)/4);
				string str;
				str = buff;
				for(int i = 0;i<str.length();i=i+1){
					*read = str[i];
					read = read + 1;
				}	
			}
			else if(*v0 == 15){
				int fd = *(v0+2);
				fp = fdopen(fd,"w");
				*(v0+2) = *(v0+4);
				char *print_string = (char *)(a+(*(v0+3)-4194304)/4);
				string str;
				for (int i = 0;i<*(v0+4);i=i+1){
					str = str + *print_string;
					print_string = print_string + 1;
				}
				char *p = (char*)str.c_str();
				fputs(p,fp);	
				}
			else if(*v0 == 16){
				int fd = *(v0+2);
				fp = fdopen(fd,"r");
				fclose(fp);
			}
			else if (*v0 == 17){
				cout<<*(v0+2)<<endl;
				exit(0);
			}	
			pc = pc + 4;
		}
			
	}


};

void mtlo_func(int* rs,int* lo){
	*lo = *rs;
}

void mthi_func(int* rs,int* hi){
	*hi = *rs;
}

void mflo_func(int* rd,int* lo){
	*rd = *lo;
}

void mfhi_func(int* rd,int* hi){
	*rd = *hi;
}

void tne_func(int* rs, int* rt,int pc){
	if (*rs != *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}


void teq_func(int* rs, int* rt,int pc){
	if (*rs == *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tlt_func(int* rs, int* rt,int pc){
	if (*rs < *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tltu_func(int* rs, int* rt,int pc){
	if (*rs < *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tge_func(int* rs, int* rt,int pc){
	if (*rs >= *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tgeu_func(int* rs, int* rt,int pc){
	if (*rs >= *rt){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void teqi_func(int* rs,int imm,int pc){
	if (*rs == imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tnei_func(int* rs,int imm,int pc){
	if (*rs != imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tgei_func(int* rs,int imm,int pc){
	if (*rs >= imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tlti_func(int* rs,int imm,int pc){
	if (*rs < imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tltiu_func(int* rs,int imm,int pc){
	if (*rs < imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void tgeiu_func(int* rs,int imm,int pc){
	if (*rs >= imm){
		printf("exception occurs at %d",pc);
		exit(1);
	}
}

void slt_func (int* rs, int* rt,int* rd){
	if (*rs < *rt){
		*rd = 1;
	}
	else{
		*rd = 0;
	}
}

void sltu_func (int* rs, int* rt,int* rd){
	if (*rs < *rt){
		*rd = 1;
	}
	else{
		*rd = 0;
	}
}

void slti_func(int* rs, int imm,int* rt){
	if (*rs < imm){
		*rt = 1;
	}
	else{
		*rt = 0;
	}
}

void sltiu_func(int* rs, int imm,int* rt){
	if (*rs < imm){
		*rt = 1;
	}
	else{
		*rt = 0;
	}
}


void sll_func (int shamt, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string sub_rtStr = rtStr.substr(shamt);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + "0";
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void sllv_func (int* rs, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string sub_rtStr = rtStr.substr(*rs);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + "0";
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void sra_func (int shamt, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string place;
	if (rtStr[0] == '1'){
		place = "1";
	}
	else{
		place = "0";
	}
	string sub_rtStr = rtStr.substr(0,rtStr.length()-shamt);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + place;
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void srav_func (int* rs, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string place;
	if (rtStr[0] == '1'){
		place = "1";
	}
	else{
		place = "0";
	}
	string sub_rtStr = rtStr.substr(0,rtStr.length()-*rs);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + place;
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void srl_func (int shamt, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string sub_rtStr = rtStr.substr(0,rtStr.length()-shamt);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + "0";
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void srlv_func (int* rs, int* rt,int* rd){
	string rtStr = dec_to_binary(*rt,32);
	string sub_rtStr = rtStr.substr(0,rtStr.length()-*rs);
	while (sub_rtStr.length()!=32){
		sub_rtStr = sub_rtStr + "0";
	}
	*rd = binStr_to_decInt(sub_rtStr);
}

void addi_func (int* rs, int imm,int* rt){
	*rt = *rs + imm;
}

void addiu_func (int* rs, int imm,int* rt){
	*rt = *rs + imm;
}

void add_func (int* rs, int* rt,int* rd){
	*rd = *rs + *rt;
}

void addu_func (int* rs, int* rt,int* rd){
	*rd = *rs + *rt;
}

int bne_func(int* rs,int *rt,int pc,int offset){
	if (*rs != *rt){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int beq_func(int* rs,int *rt,int pc,int offset){
	if (*rs == *rt){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int bgez_func(int* rs,int pc,int offset){
	if (*rs >= 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int bgtz_func(int* rs,int pc,int offset){
	if (*rs > 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int bgezal_func(int* rs,int pc,int offset){
	if (*rs >= 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int bltzal_func(int* rs,int pc,int offset){
	if (*rs < 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}

int bltz_func(int* rs,int pc,int offset){
	if (*rs < 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}


int blez_func(int* rs,int pc,int offset){
	if (*rs <= 0){		
		pc = pc + (offset+1)*4;
	}
	else{
		pc = pc + 4;
	}
	return pc;
}


void sub_func(int* rs,int* rt,int* rd){
	*rd = *rs-*rt;
}

void subu_func(int* rs,int* rt,int* rd){
	*rd = *rs-*rt;
}


void lw_func(int* rs,int* rt,int offset){
	*rt = *rs+offset;
}

//void sw_func(int* rt,int* rs,int offset){
//	*rs = *rt + offset;
//} 

void lui_func(int* rt,int imm){
	int lowWord = imm % 65535;
	int new_word = lowWord * 65536;
	*rt = new_word;
//	*rt = new_word - 4194304;
}

void ori_func(int* rs,int imm,int* rt){
	string rsStr = dec_to_binary(*rs,32);
	string immStr = dec_to_binary(imm,32);
	string rtStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='0')&&(immStr[i]=='0')){
			rtStr = rtStr + "0";
		}
		else{
			rtStr = rtStr + "1";
		}
	}
	*rt = binStr_to_decInt(rtStr);
}

void xori_func(int* rs,int imm,int* rt){
	string rsStr = dec_to_binary(*rs,32);
	string immStr = dec_to_binary(imm,32);
	string rtStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='0')&&(immStr[i]=='0')){
			rtStr = rtStr + "0";
		}
		else if ((rsStr[i]=='1')&&(immStr[i]=='1')){
			rtStr = rtStr + "0";
		}
		else{
			rtStr = rtStr + "1";
		}
	}
	*rt = binStr_to_decInt(rtStr);
}

void andi_func(int* rs,int imm,int* rt){
	string rsStr = dec_to_binary(*rs,32);
	string immStr = dec_to_binary(imm,32);
	string rtStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='1')&&(immStr[i]=='1')){
			rtStr = rtStr + "1";
		}
		else{
			rtStr = rtStr + "0";
		}
	}
	*rt = binStr_to_decInt(rtStr);
}


void and_func(int* rs,int* rt,int* rd){
	string rsStr = dec_to_binary(*rs,32);
	string rtStr = dec_to_binary(*rt,32);
	string rdStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='1')&&(rtStr[i]=='1')){
			rdStr = rdStr + "1";
		}
		else{
			rdStr = rdStr + "0";
		}
	}
	*rd = binStr_to_decInt(rdStr);
}

void or_func(int* rs,int* rt,int* rd){
	string rsStr = dec_to_binary(*rs,32);
	string rtStr = dec_to_binary(*rt,32);
	string rdStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='0')&&(rtStr[i]=='0')){
			rdStr = rdStr + "0";
		}
		else{
			rdStr = rdStr + "1";
		}
	}
	*rd = binStr_to_decInt(rdStr);
}

void xor_func(int* rs,int* rt,int* rd){
	string rsStr = dec_to_binary(*rs,32);
	string rtStr = dec_to_binary(*rt,32);
	string rdStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='0')&&(rtStr[i]=='0')){
			rdStr = rdStr + "0";
		}
		else if ((rsStr[i]=='1')&&(rtStr[i]=='1')) {
			rdStr = rdStr + "0";
		}
		else{
			rdStr = rdStr + "1";
		}
	}
	*rd = binStr_to_decInt(rdStr);
}

void nor_func(int* rs,int* rt,int* rd){
	string rsStr = dec_to_binary(*rs,32);
	string rtStr = dec_to_binary(*rt,32);
	string rdStr;
	for (int i = 0;i<32;i=i+1){
		if ((rsStr[i]=='0')&&(rtStr[i]=='0')){
			rdStr = rdStr + "1";
		}
		else{
			rdStr = rdStr + "0";
		}
	}
	*rd = binStr_to_decInt(rdStr);
}


int jal_func(int pc, int* ra,int target){
	*ra = pc + 4;
	pc = 4194304 + (target * 4);
	return pc;
}

int j_func(int pc,int target){
	pc = 4194304 + (target * 4);
	return pc;
}

int jalr_func(int pc,int *rs,int* rd){
	*rd = pc + 4; 
	int address = *rs;
	return address;
}

int jr_func(int* rs){
	int pc = *rs;
	return pc;
}

void div_func (int* rs,int* rt,int* lo,int* hi){
	*lo = *rs / *rt;
	*hi = *rs % *rt;
}

void divu_func (int* rs,int* rt,int* lo,int* hi){
	*lo = *rs / *rt;
	*hi = *rs % *rt;
}

void mult_func (int* rs,int* rt,int * lo,int* hi){
	long result = (*rs) * (*rt);
	string result_string = long_dec_to_binary(result,64);
	string string_hi = result_string.substr(0,32);
	string string_lo = result_string.substr(32,32);	
	*hi = binStr_to_decInt(string_hi);
	*lo = binStr_to_decInt(string_lo);
}

void multu_func (int* rs,int* rt,int * lo,int* hi){
	long result = (*rs) * (*rt);
	string result_string = long_dec_to_binary(result,64);
	string string_hi = result_string.substr(0,32);
	string string_lo = result_string.substr(32,32);	
	*hi = binStr_to_decInt(string_hi);
	*lo = binStr_to_decInt(string_lo);
}


int binReg_to_decInt(string str){
	int number = 0;
	int bit = 0;
	for (int i = str.length()-1;i>=0;i=i-1){
		if (str[i]=='1'){
			number = number + pow(2,bit);
			bit = bit + 1;
		}
		else{
			bit = bit + 1;
		}
	}
	return number;
}




//将一个二进制字符串转换成一个十进制整数
int binStr_to_decInt(string str){
	int number = 0;
	int bit = 0;
	if (str[0]=='1'){
		for (int i = str.length()-1;i>=1;i=i-1){
		if (str[i]=='0'){
			str[i] = '1';
		}
		else{
			str[i] = '0';
			break;
		}
		}
		for (int i = 1;i<str.length();i=i+1){
			if (str[i]=='0'){
				str[i] ='1';
			}
			else{
				str[i] = '0';
			}
		}
		for (int i = str.length()-1;i>0;i=i-1){
		if (str[i]=='1'){
			number = number + pow(2,bit);
			bit = bit + 1;
		}
		else{
			bit = bit + 1;
		}
	}
	number = -number;
	}
	
	else if (str[0]=='0'){
		for (int i = str.length()-1;i>=0;i=i-1){
		if (str[i]=='1'){
			number = number + pow(2,bit);
			bit = bit + 1;
		}
		else{
			bit = bit + 1;
		}
	}
	}
	return number;
} 

//将63位真地址变成32位假地址 
int new_address(int address,int init_address){
	int newAddress = address - init_address + 4194304;
	return newAddress;
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

string long_dec_to_binary (long i,int x)
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
		binary_number = "0000000000000000000000000000000000000000000000000000000000000000" + newStr;
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


