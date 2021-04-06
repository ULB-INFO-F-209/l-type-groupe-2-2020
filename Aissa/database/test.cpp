#include<iostream>
#include<fstream>

struct Student {
   int roll_no;
   std::string name;
};
int main() {
	
	std::ofstream outfile;
	outfile.open("caca.bin", std::ios::out | std::ios::binary);
	std::string str("whatever");
	size_t size=str.size();
	char char_size = char(size);
	outfile.write(&char_size,sizeof(size));
	outfile.write(&str[0],size);
	outfile.close();
	
	/*
	std::ifstream infile;
	infile.open("caca.bin", std::ios::in | std::ios::binary);
	if(!infile){
    std::cout << "salut bg"<<std::endl;
       std::cout<<"Error in creating file!!!"<<std::endl;
       throw ;
    }
	size_t size;
	std::string read_string;
	char read_char_size;
	infile.read(&read_char_size, sizeof(size));
	size = read_char_size;
	read_string.resize(size);
	infile.read(&read_string[0], size);
	std::cout << read_string << std::endl;
	infile.close();
	*/
}