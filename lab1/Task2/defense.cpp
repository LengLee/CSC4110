#include<iostream>
#include"defense.h"
using namespace std; 

Defense::Defense(string name):Player(name) {
	// calls Player constructor 
}

void Defense::setMinutesPlayed(int minute) {
	minutes = minute;		//set minutes = minute
}

void Defense::setTackles(int tackles) {
	tack = tackles;			//set tack = tackles
}

void Defense::printStats() const {
	Player::printStats(); 
	cout<< " \tTackles " << tack << " \tMinutes Played " << minutes<<endl; 
	// calls printstat from Player, then print other values
}