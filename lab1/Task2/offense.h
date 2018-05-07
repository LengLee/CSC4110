#ifndef offense_H
#define offense_H

#include"player.h"
#include<iostream>
using namespace std; 

class Offense : public Player {
public:
	Offense(string name); 
	void setMinutesPlayed(int minutes);		// doesnt return a value, therefore its void	
	void setYards(int yard);		// doesnt return a value, therefore its void	
	void printStats() const;		// prints values 	
					
private:
	int yards; // yards is private variable 
	
	 
};
#endif