#include <iostream>

using namespace std;

struct Node{
    int iData;
    bool isAlive;
    struct Node* next;
};

Node *createNode(int value){
    Node *newNode = new Node;
    newNode -> iData = value;
    newNode -> isAlive = true;
    newNode -> next = nullptr; 
    
    return newNode;
}

void insert(Node * head, int value) {
    Node *newNode = createNode(value);
    newNode -> next = head -> next; 
    head -> next = newNode;
}

void insertOrdem(Node *head, int value){
	Node *max = head, *min = head;
	for(Node *tmp = head->next; tmp != head; tmp = tmp-> next) {
		if(tmp -> iData <= value && tmp->next->iData >= value) {
			insert(tmp, value);
			return;
		}
		if(tmp -> iData >= max -> iData)
			max = tmp;
		if(tmp -> next -> iData <= min -> iData)
			min = tmp;
	}
	if(value <= min -> next -> iData){
		insert(min, value);
		return;
	}
	insert(max, value);
}

void printList(Node *ptr){
	cout << ptr -> iData << " ";
	for(Node *tmp = ptr -> next; tmp != ptr; tmp = tmp -> next)
		cout << tmp -> iData << " ";
}

Node *josefo(Node *head, int k, int nTotal) {
	while(nTotal > 1) {
		int i = k;
		while(i > 1) {
			head = head -> next;
			if(head -> isAlive)
				i--;
		}
		head -> isAlive = false;
		nTotal--;
		while(!(head -> isAlive))
			head = head -> next;
	}
	
	return head;
}

void deleteList(Node *head) {
	Node *aux;
	for(Node *tmp = head -> next; tmp != head; free(aux)){
		aux = tmp;
		tmp = tmp -> next;
	}
	free(head);
}

int main()
{
	int k;
	cout << "Digite um inteiro k para indicar o soldado que sera morto (>=2): ";
	cin >> k;
	if( k < 2){
		cout << "O numero inserido e invalido!" << endl;
		return 1;
	}
	int n;
	cout << "Digite um inteiro n indicando o numero de soldados (>=1): ";
	cin >> n;
	if( n < 1){
		cout << "O numero inserido e invalido!" << endl;
		return 1;
	}
		
    Node *head = new Node;
    head->iData = 1;
  	head -> next = head;
    head -> isAlive = true;
    for(int j = 2; j <= n; j ++){
    	insertOrdem(head, j);
	}
	cout << "Quem sobrevive em ";
	printList(head);
	cout << " (matando o " << k << "-esimo soldado do lado) e o soldado "<< (josefo(head, k, n) -> iData) << endl;
	deleteList(head);
    return 0;
}