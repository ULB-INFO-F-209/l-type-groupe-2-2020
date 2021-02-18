#include "parsing.hpp"

void parsing(char str[100], char token1[20], char token2[20]) {
	//str has the correct structure i.e "Mb_MYPSEUDO_MYPASSWORD"
	int i = 0;
    char *token = strtok(str, "&");
    while (token != NULL) {
        //std::cout << i << " >> " << token << std::endl;
        token = strtok(NULL, "&");
        if(i==0) {strcpy(token1, token);}
        else if(i==1) {strcpy(token2, token);}
        i++;
    }
}

void parsing_pseudo(char str[100], char pseudo[20]) {
	char *token = strtok(str, "&");
	token = strtok(NULL, "&");
	strcpy(pseudo, token);
}

int main() {
	//convert char* val >> char val[100]
	char pseudo[20], pswd[20] = {'\0'};
	
	char str[100] = "Ma&NAME&12pass34&pid";
	char str1[100] = "Mf&VINOVE&pid";
	
	parsing(str, pseudo, pswd);
	std::cout << pseudo << " : " << pswd << std::endl;
	
	parsing_pseudo(str1, pseudo);
	std::cout << pseudo << std::endl;
	
	return 0;	
}
