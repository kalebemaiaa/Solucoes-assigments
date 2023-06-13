#include <iostream>

using namespace std;

struct Node{
	int iData;
	struct Node *next;
};

void insert(Node *head, int value) {
	Node *newNode = new Node;
	newNode -> next = head -> next;
	newNode -> iData = value;
	head -> next = newNode;
}

void insertOrdem(Node *head, int value){
	Node *max = head, *min = head, *begin = head;
	for(Node *tmp = head->next; tmp != begin; tmp = tmp-> next) {
		if(head -> iData <= value && head -> next -> iData >= value) {
			insert(head, value);
			return;
		}
		if(head -> iData >= max -> iData)
			max = head;
		if(head -> next -> iData <= min -> iData){
			cout << head -> next -> iData << " x " << min -> iData << " " << value << endl;
			min = head;
		}
		head = head -> next;
	}
	if(value <= min -> next -> iData){
		insert(min, value);
		return;
	}
	if(value >= max -> iData){
		insert(max, value);
		return;
	}
}

void printList(Node *ptr){
	cout << ptr -> iData << " ";
	for(Node *tmp = ptr -> next; tmp != ptr; tmp = tmp -> next)
		cout << tmp -> iData << " ";
		
	cout << endl;
}

Node *findMin(Node *ptr){
	Node *min = ptr;
	for(Node *tmp = ptr -> next; tmp != ptr; tmp = tmp -> next)
		if(tmp -> iData < min -> iData)
			min = tmp;
	return min;
}

int main() {
	Node *head = new Node;
	head -> next = head;
	head -> iData = 10;
	insertOrdem(head, 1);
	insertOrdem(head, -11);
	insertOrdem(head, -5);
	insertOrdem(head, 120);
	insertOrdem(head, 12);
	insertOrdem(head, 15);
	insertOrdem(head, 11);
	insertOrdem(head, 1100);
	insertOrdem(head, -1100);
	printList(head);
	Node *min = findMin(head);
	cout << "Printando a partir do menor: "<< endl;
	printList(min);
}
