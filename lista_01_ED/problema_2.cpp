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

Node *concat(Node *h1, Node *h2) {
    Node *head = (Node*) malloc(sizeof(Node));
    head -> data = h1 -> data;
    h1 = h1 -> next;
    while(h1 != nullptr) {
        insert(head, h1 -> data);
        h1 = h1 -> next;
    }
    while(h2 != nullptr) {
        insert(head, h2 -> data);
        h2 = h2 -> next;
    }
    
    return head;
}

int main() {
    Node *head1 = (Node*) malloc(sizeof(Node));
    head1 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head1, 2 * i);
    }
    
    Node *head2 = (Node*) malloc(sizeof(Node));
    head2 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head2, 5 * i);
    }
    
    Node *head = concat(head1, head2);
    
    cout << "\tProblema 2\n\n";
    cout << "Input1: ";
    printLinkedList(head1);
    cout << "Input2: ";
    printLinkedList(head2);
    cout << "Concat: ";
    printLinkedList(head);
}