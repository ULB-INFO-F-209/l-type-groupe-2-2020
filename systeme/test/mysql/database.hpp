#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mysql/mysql.h> 

class Database final
{
	constexpr static char SERVER[10] = "localhost";
	constexpr static char USER[5] = "pixi";
	constexpr static char PSWD[10] = "";
	constexpr static char NOM_DB[12] = "Application";
	MYSQL *_connect;
	MYSQL_RES *_res;
	MYSQL_ROW _row;
	void _dsp (std::ostream& out) const;  
public:
	//constructors
	Database(){
		_connect=mysql_init(NULL); //initialisation
		if (not _connect){std::cout<<"MySQL Initialization failed"; exit(1);}
		_connect=mysql_real_connect(_connect, SERVER, USER, PSWD , 
		NOM_DB,0,NULL,0);
		if (_connect){
			std::cout<<"connection Succeeded\n";
		}
		else{
			std::cout<<"connection failed\n";
			exit(EXIT_FAILURE);
		}
	}

	//getters
	void user_info(char *res, char *pseudo){

		char query[150]; 
		sprintf(query, "SELECT pseudo, score from User WHERE pseudo=%s ", pseudo);
		mysql_query (_connect,query);
		_res = mysql_store_result(_connect);
		_row = mysql_fetch_row(_res);
		sprintf(res, "%s_%s", _row[0], _row[1]);
	}

	bool find_pseudo(char*pseudo){
		bool res = false;
		char query[150]; 
		sprintf(query, "SELECT pseudo from User WHERE pseudo=%s ", pseudo);
		mysql_query (_connect,query);
		_res = mysql_store_result(_connect);
		if((_row = mysql_fetch_row(_res) ) != NULL){ res = 1;}
		return res;
	}
	//setters
	void create_account(char *pseudo , char*pswd){
		char query[150]; 
		sprintf(query, "INSERT INTO User (pseudo, password) VALUES ('%s', '%s'", pseudo, pswd);
		mysql_query (_connect,query);
	}




	//Destructors
	~Database(){
		mysql_close (_connect);
	}

	//extern
	friend inline std::ostream& operator<< (std::ostream& out, const Database& db){
		db._dsp(out);
		return out;
	}
	
};

#endif //DATABASE_HPP