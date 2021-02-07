#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
//#include <cstdlib>
//#include <cstdio>

class Menu{
	size_t _size;
	std::string *_choices;
protected: 
	virtual void _dsp (std::ostream&) const;  
public:
	//constructeur
	explicit Menu(const std::initializer_list<std::string>& init)noexcept;
	
	//getters
	virtual const void get_user_choice();

	//application
	virtual void execute_choice(int choice)=0;

	//destructor
	virtual ~Menu() noexcept;

	//extern
	friend inline std::ostream& operator<< (std::ostream& out, const Menu& menu){
		system("clear"); //que sur linux
		menu._dsp(out);
		return out;
	}
	
};

class ConnexionMenu{
public:
	ConnexionMenu();
	~ConnexionMenu();
	
};

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	
};


class FriendMenu{


};





#endif //MENU_HPP