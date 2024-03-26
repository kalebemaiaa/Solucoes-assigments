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

Node *transformation(Node *head, int k) {
	Node *tmp;
	if(head -> next == nullptr) return head;
	
	for(tmp = head -> next; tmp -> next != nullptr; tmp = tmp -> next);
	tmp -> next = head;
	
	for(;k > 0; k--)
		tmp = tmp -> next;
		
	head = tmp -> next;
	tmp -> next = nullptr;
	return head;
}

void print(Node *head) {
	while(head){
		cout << head -> iData << " ";
		head = head -> next;
	}
	cout << endl;
}

int main() {
	// Lista normal
    Node *head2 = new Node;
    head2 -> iData = 1;
    head2 -> next = nullptr;
    insert(head2, 2);
    insert(head2, 8);
    insert(head2, 3);
    insert(head2, 4);
    cout << "Lista original: \t\t";
    print(head2);
    
    head2 = transformation(head2, 4);
    cout << "Lista transformada em 4: \t";
    print(head2);
    
    head2 = transformation(head2, 3);
    cout << "Lista transformada em 4+3: \t";
    print(head2);
	return 0;
}