#include<iostream>
#include"Stack.h"
using namespace std; 


Stack::Stack() {
	top = NULL; 
}


void Stack::push(double v) {
	Node *n = new Node;
	if (top == NULL) {
		n -> data = v;
		n->next = NULL; 
	}
	else {
		n->data = v; 
		n->next = top;
	}
	top = n;
	count++; 
}

double Stack::pop() {
	Node * temp = new Node;
	double t; 
	temp = top; 
	top = top->next; 
	t = temp->data; 
	delete temp; 
	--count; 
	return t;
}

int Stack::isEmpty() {
	if (top == NULL) {
		return 1;
	}
	else
		return 0; 
}

int Stack::numOfElements() {
	return count; 
}

void Stack::printElements() {
	Node * current = new Node; 
	current = top; 
	if (current == NULL) {
		cout << "Stack is Empty" << endl;
	}
	else {
		while (current->next != NULL) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << current->data;
	}
	
}
 