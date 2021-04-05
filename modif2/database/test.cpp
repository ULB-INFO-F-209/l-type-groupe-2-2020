#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    fstream file;

    file.open("Gfg.txt",ios::out);

    if(!file){
       cout<<"Error in creating file!!!";
       return 0;
    }
  
    cout<<"File created successfully.";
  
    file.close();    
};


void test (){
  std::ifstream file("test2.txt");
  std::string str;
  
  while (std::getline(file, str)) {
    std::cout << str << "\n";
  }
}