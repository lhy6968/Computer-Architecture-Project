#include <vector> 

#include <string> 

#include <fstream> 

#include <iostream> 
 

using namespace std; 

 

int main() 

{ 

    ifstream myfile("G:\\C++ project\\Read\\hello.txt"); 

    ofstream outfile("G:\\C++ project\\Read\\out.txt", ios::app); 

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
