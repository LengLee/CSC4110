#include"player.h"
#include<iostream>
using namespace std; 


#ifndef DEFENSE_H
#define DEFENSE_H

class Defense : public Player {

public:
	Defense(string name);		
	void setMinutesPlayed(int minutes);			// doesnt return a value, therefore its void	
	void setTackles(int tackles);			// doesnt return a value, therefore its void	
	void printStats() const;			// prints values 

	 
private:
	int tack;		// sets tack to a private variable 

};
#endif 