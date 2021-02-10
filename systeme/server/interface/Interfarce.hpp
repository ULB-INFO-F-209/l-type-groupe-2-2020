#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Client.hpp"
#include "Menu.hpp"

class Interfarce final
{
	Client client{};
	ConnexionMenu _cm{&client};
	FriendMenu _fm{&client};
	MainMenu _mm{&client};
public:
	Interfarce()=default;

	void start_session(){
		int status;
		status = _cm.start_menu();
		if(status){
			//lancé menu
			status =_mm.start_menu();
		}
		else{
			//terminer le processus client
		}
	}


	~Interfarce()=default;
	
};




#endif // INTERFACE_HPP