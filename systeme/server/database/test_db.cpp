#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();
    
	/*Account helin(11, "helin", "123");
	db.add(&helin);
    
    Account aissa(17, "aissa", "blabla");
    db.add(&aissa);

	Account vin(17, "Vin", "toto");
    db.add(&vin);
*/
	std::cout << db.find("Vin") << std::endl;
	db.dbSave();
	//db.dbLoad();
	return 0;
}