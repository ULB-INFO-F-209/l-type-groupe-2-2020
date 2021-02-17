#include "parsing.hpp"

void parsing(char str[100], char token1[20], char token2[20]){
	//str has the correct structure i.e "Mb_MYPSEUDO_MYPASSWORD"
	int i = 0;
    char *token = strtok(str, "_");
    while (token != NULL) {
        //std::cout << i << " >> " << token << std::endl;
        token = strtok(NULL, "_");
        if(i==0) { strcpy(token1, token); }
        else if(i==1) { strcpy(token2, token); }
        i++;
    }
}

int main() {
	//convert char* val >> char val[100]
	char str1[100] = "Mb_Chantelle_12pass34";
	char str[100] = "Mc_PseudoMe_PseudoF";
	//char* str = "Mc_PseudoMe_PseudoF";
	char pseudo[20], pswd[20] = {'\0'};
	parsing(str1, pseudo, pswd);
	std::cout << pseudo << " : " << pswd << std::endl;
	return 0;	
}
