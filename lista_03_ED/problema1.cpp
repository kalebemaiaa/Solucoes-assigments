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

void insertOrdem2(Node *head, int value){
    Node *cur = head;
    for(Node *tmp = head -> next; tmp != head; tmp = tmp -> next){
        if(value < tmp -> iData){
            insert(cur, value);
            return;
        }
        cur = cur -> next;
    }
    insert(cur, value);
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
    // ~Assumindo que a lista pode receber um valor menor que o head.
	Node *head = new Node;
	head -> next = head;
	head -> iData = 10;
	insertOrdem1(head, 1);
	insertOrdem1(head, -11);
	insertOrdem1(head, -5);
	insertOrdem1(head, 120);
	insertOrdem1(head, 130);
	insertOrdem1(head, -120);
	insertOrdem1(head, 12);
	insertOrdem1(head, 15);
	insertOrdem1(head, 11);
	insertOrdem1(head, 1100);
	insertOrdem1(head, -1100);
	cout << "-Caso possam inserir valores menores que o valor inicial de head-\n\n";
	cout << "\tLista:\t";
	printList(head);
	Node *min = findMin(head);
	cout << "\tPrintando a partir do menor:\t";
	printList(min);
	
	// ~O head2 sempre sera o menor valor
	Node *head2 = new Node;
	head2 -> next = head2;
	head2 -> iData = 0;
	insertOrdem2(head2, 1);
	insertOrdem2(head2, 120);
	insertOrdem2(head2, 130);
	insertOrdem2(head2, 12);
	insertOrdem2(head2, 15);
	insertOrdem2(head2, 11);
	insertOrdem2(head2, 1100);
	cout << "\n-Caso NAO possam inserir valores menores que o valor inicial de head-\n\n";
	cout << "\tLista:\t";
	printList(head2);
}