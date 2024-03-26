#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *next;
};

void insert(Node *head, int data){
    if(head -> next == nullptr) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode -> data = data;
        newNode -> next = nullptr;
        head -> next = newNode;
        return;
    }
    insert(head -> next, data);
}

void printLinkedList(Node *head){
    if(head == nullptr){ 
        cout << endl;
        return;
    }
    cout << head -> data << " ";
    printLinkedList(head -> next);
}

int sum(Node *head) {
    if(head == nullptr) return 0;
    return (head -> data) + sum(head -> next);
}

int main(){
    // ~Cria lista
    Node *head = (Node*) malloc(sizeof(Node));
    head -> data = 1;
    
    // ~Insere elementos
    for(int i = 1; i < 10; i++){
        insert(head, i + 1);
    }
    
    cout << "\tProblema 1\n\n";
    cout << "Input: ";
    
    // ~Printa lista
    printLinkedList(head);
    
    // ~Printa soma
    cout << "Soma: " << sum(head);
    return 0;
}