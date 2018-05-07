#include<iostream>
#include"offense.h"
using namespace std; 

Offense::Offense(string name) :Player(name) {
			// calls Player constructor
}

void Offense::setMinutesPlayed(int minute) {
	minutes = minute;		// sets minutes = minute
}

void Offense::setYards(int yard) {
	yards = yard;			// sets yards = yard
}

void Offense::printStats() const {
	Player::printStats(); 
	cout<< " \tYards " << yards << " \tMinutes Played " << minutes<<endl;
}		// // calls printstat from Player, then print other values