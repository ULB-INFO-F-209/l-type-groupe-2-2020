#include<iostream>
#include<fstream>

struct Student {
   std::string name;
   int vote;
};

struct DatabaseLevel{
   std::string level;
   std::string name;
   int vote;
};
int main() {

	//Student helin{};
	/*
	std::ofstream outfile;
	outfile.open("caca.bin", std::ios::out | std::ios::binary);

	std::string str = helin.name;
	size_t size=str.size();
	char char_size = char(size);
	outfile.write(&char_size,sizeof(size));
	outfile.write(&str[0],size);

	int vote = helin.vote;
	outfile.write(reinterpret_cast<const char *>(&vote), sizeof(vote));
	outfile.close();

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
	
	int vote;
	infile.read(reinterpret_cast<char *>(&vote), sizeof(vote));
	std::cout << vote << std::endl;
	infile.close();
	*/
	/*
	std::fstream levels;
	levels.open("caca.bin", std::ios::out | std::ios::binary);

	std::string pseudo = "helin";
	DatabaseLevel lev{"LS_aaaaaaaaa_0_2_70_30_4|0_450_0_70_30_0_2&|", "aaaaaaaaa", 0};

	std::string str(pseudo);
	size_t size = str.size();
	char char_size = char(size);
	levels.write(&char_size,sizeof(size));
	levels.write(&str[0],size);

	size_t size2 = lev.level.size();
	char char_size2 = char(size2);
	levels.write(&char_size2,sizeof(size2));
	levels.write(&lev.level[0],size2);

	size_t size3=lev.name.size();
	char char_size3 = char(size3);
	levels.write(&char_size3,sizeof(size3));
	levels.write(&lev.name[0],size3);

	int vote = lev.vote;
	levels.write(reinterpret_cast<const char *>(&vote), sizeof(vote));
	*/
    std::ifstream levels;
    levels.open("caca.bin", std::ios::in | std::ios::binary);
	size_t size1, size2, size3;
    char read_size1, read_size2, read_size3;

	levels.read(&read_size1, sizeof(size1));        
	std::string read_pseudo, read_level, read_name;

	size1 = read_size1;
	read_pseudo.resize(size1);
	levels.read(&read_pseudo[0], size1);

	levels.read(&read_size2, sizeof(size2));
	size2 = read_size2;
	read_level.resize(size2);
	levels.read(&read_level[0], size2);

	levels.read(&read_size3, sizeof(size3));
	size3 = read_size3;
	read_name.resize(size3);
	levels.read(&read_name[0], size3);

	int vote;
	levels.read(reinterpret_cast<char *>(&vote), sizeof(vote));

	std::cout << read_pseudo << read_level << read_name << vote << std::endl;
}