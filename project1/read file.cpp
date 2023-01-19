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

        cout << "未成功打开文件" << endl; 

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
