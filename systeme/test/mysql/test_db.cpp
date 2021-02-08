#include <iostream>
#include "database.hpp"
#include <mysql/mysql.h> 

int main()
{
	MYSQL *connect;
	connect=mysql_init(NULL);
	if (not connect){std::cout<<"MySQL Initialization failed"; exit(1);}

	connect=mysql_real_connect(connect, "localhost", "pixi", "" , 
	"Application" ,0,NULL,0);
	if (connect){
		std::cout<<"connection Succeeded\n";
	}
	else{
		std::cout<<"connection failed\n";
	}

	MYSQL_RES *res_set;
	MYSQL_ROW row;
	mysql_query (connect,"select * from DB;");
	unsigned int i =0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	while (((row= mysql_fetch_row(res_set)) !=NULL )){ //std::cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
	 std::cout <<"\t | \t" << row[i] << "\t | \t";
	 std::cout <<  row[i+1] <<  "\t |"<< std::endl;
	}
	mysql_close (connect);
	return 0;
}