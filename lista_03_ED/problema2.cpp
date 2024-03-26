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

void insertOrdem1(Node *head, int value){
    Node *cur = head, *min= head, *max = head;
    for(Node *controle = head -> next; controle != head; controle = controle -> next){
        if(value < controle -> iData && value >= cur->iData){
            insert(cur, value);
            return;
        }
        if(min -> next -> iData >= controle -> iData)
            min = cur;
        if(cur -> iData >= max -> iData)
            max = cur;
        cur = cur -> next;
    }
    if(value > max -> iData){
        insert(max, value);
        return;
    }
    if(value < min -> next -> iData){
        insert(min, value);
        return;
    }
}

bool verifyList(Node *head) {
    if(head == nullptr)
        return false;
	for(Node *tmp = head -> next; tmp != head; tmp = tmp -> next)
		if(tmp == nullptr)
			return false;
	return true;
}

int main() {
	// Lista circular
	Node *head = new Node;
	head -> next = head;
	head -> iData = 10;
	insertOrdem1(head, 11);
	insertOrdem1(head, -11);
	insertOrdem1(head, -5);
	insertOrdem1(head, 120);
	
	// Lista normal
    Node *head2 = new Node;
    head2 -> iData = 1;
    head2 -> next = nullptr;
    // insert preserva o null para o final
    insert(head2, 2);
    insert(head2, 8);
    insert(head2, 3);
    insert(head2, 4);
	cout << verifyList(head) << endl;
	cout << verifyList(head2) << endl;
	
	return 0;
}