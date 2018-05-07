
#include<stdexcept> 
#include<iostream>
using namespace std;

#ifndef Stack_h
#define Stack_h 

class Stack {

public:
	Stack();
	void push(double v); 
	double pop(); 
	int isEmpty(); 
	int numOfElements(); 
	void printElements();
	int count = 0; 

private: 
	struct Node {
		double data;
		Node *next;
	};
	Node * top; 
	int maxSize = 30; 
	
};
#endif 
