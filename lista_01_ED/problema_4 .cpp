#include <iostream>
#include <cmath>

using namespace std;

struct Node{
    int data;
    Node *next;
};

struct Node2{
    Node *node;
    Node2 *next;
};

void insert(Node *head, int data){
    if (head == nullptr){
        cout << "Não deu para inserir!\n" ;
        return;
    }
    if(head -> next == nullptr) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode -> data = data;
        newNode -> next = nullptr;
        head -> next = newNode;
        return;
    }
    insert(head -> next, data);
}

void insert2(Node2 *head, Node *ptr) {
    if (head == nullptr){
        cout << "Não deu para inserir!\n" ;
        return;
    }
    if(head -> next == nullptr) {
        Node2 * newNode = (Node2 *) malloc(sizeof(Node2));
        newNode -> node = ptr;
        newNode -> next = nullptr;
        head -> next = newNode;
        return;
    }
    insert2(head -> next, ptr);
}

void printLinkedList(Node *head){
    if(head == nullptr) return;
    cout << head -> data << " ";
    printLinkedList(head -> next);
}

void printLinkedList2(Node2 *head){
    if(head == nullptr){ 
        cout << endl;
        return;
    }
    printLinkedList(head -> node);
    printLinkedList2(head -> next);
}

int main() {
    Node *head1 = (Node*) malloc(sizeof(Node));
    head1 -> data = 1;
    
    for(int i = 1; i < 10; i++) {
        insert(head1, pow(-1, i) * i);
    }
    
    Node *head2 = (Node*) malloc(sizeof(Node));
    head2 -> data = 1;
    
    for(int i = 1; i < 10; i++) {
        insert(head2, 2 * i);
    }
    
    Node2 *head = (Node2 *) malloc(sizeof(Node2));
    head -> node = head1;
    head -> next = nullptr;
    
    insert2(head, head2);

    cout << "\tProblema 4\n\n";
    cout << "  Head: " << head << "\nListas: ";
    printLinkedList2(head);
}