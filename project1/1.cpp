#include <vector> 

#include <string> 

#include <fstream> 

#include <iostream> 

 

using namespace std; 
void assember();
 

int main() 
{ 

    void assember();

}
//���ļ���д�ļ�
void assembler(){
	string input_file,output_file;
	std::cin>>input_file;
	std::cin>>output_file;
	
	ifstream myfile(input_file); 

    ofstream outfile(output_file, ios::app); 

    string temp; 

    if (!myfile.is_open()) 

    { 

        cout << "δ�ɹ����ļ�" << endl; 

    } 

    while(getline(myfile,temp)) 

    { 

        outfile << temp; 

        outfile << endl;

    } 

    myfile.close(); 

    outfile.close();

    return 0;  
} 

 
