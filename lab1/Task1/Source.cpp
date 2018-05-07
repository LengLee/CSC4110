#include<cstdlib>
#include"Stack.h"
#include<iostream>

using namespace std; 

int main() 
{
	Stack obj;  
	if (obj.isEmpty() == 1)
		cout << "Empty"<<endl;
	else
		cout << "Not Empty" << endl;

	obj.push(2.0); 
	obj.push(3.0); 
	obj.push(20.0); 
	obj.push(25.0); 
	
	cout << "Popped: " << obj.pop()<<endl;

	if (obj.isEmpty() == 1)
		cout << "Empty" << endl;
	else
		cout << "Not Empty" << endl;

	obj.printElements(); 

	cout << endl;
	cout << "# of Elements: " << obj.numOfElements()<<endl; 

	

	return 0; 
}