#include <iostream>
#include <cmath>

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

static int sortC(Node *h1, Node *h2) {
    return (h1 -> data) - (h2 -> data);
}

static int sortD(Node *h1, Node *h2) {
    return (h2 -> data) - (h1 -> data);
}

Node *getPrevious(Node *head, Node* ptr){
    if(head == nullptr) return nullptr;
    if(head -> next == ptr) return head;
    return getPrevious(head -> next, ptr);
}

void swap(Node **head, Node *h1, Node *h2) {
    Node *prevH1 = getPrevious(*head, h1);
    Node *prevH2 = getPrevious(*head, h2);
    
    if(prevH1 == prevH2 || h1 == h2) return;  
    
    Node *tmp = h2 -> next;
    if(prevH1 != nullptr)
        prevH1 -> next = h2;
    h2 -> next = h1 -> next;
    
    if(prevH2 != nullptr)
        prevH2 -> next = h1;
    h1 -> next = tmp; 
    
    if(h1 -> next == h1) h1 -> next = h2;
    if(h2 -> next == h2) h2 -> next = h1;
    if(h1 == *head) *head = h2;
    else if(h2 == *head) *head = h1;
}

void sortBubble(Node **head, int (*compare)(Node*, Node*)) {
    Node *cur;
    Node *nextCur;
    bool swapped = true;
    
    while(swapped) {
        swapped = false;
        cur = *head;
        nextCur = (*head) -> next;
        
        while(nextCur != nullptr) {
            if(compare(cur, nextCur) > 0){
                swap(head, cur, nextCur);
                swapped = true;
            }
            else{
                cur = nextCur;
            }
            nextCur = cur -> next;
        }
    }
}

int main() {
    Node* head4 = (Node *) malloc(sizeof(Node));
    head4 -> data = 1;
    
    for(int i =1; i < 10; i++) {
        insert(head4, pow(-1, i) * i);
    }
    
    cout << "\tProblema 3\n\n";
    cout << "Input: ";
    printLinkedList(head4);
    
    cout << "Bubble sort crescente: ";
    sortBubble(&head4, sortC);
    printLinkedList(head4);
    
    cout << "Bubble sort decrescente: ";
    sortBubble(&head4, sortD);
    printLinkedList(head4);
}