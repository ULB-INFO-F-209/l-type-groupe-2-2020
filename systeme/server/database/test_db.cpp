#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();
    
	Account helin(11, "helin", "123");
	db.add(&helin);
    /*
    Account aissa(17, "aissa", "blabla");
    db.add(&aissa);
    
*/
	db.dbSave();
	return 0;
}