/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

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
    if(head == nullptr){ 
        cout << endl;
        return;
    }
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

int sum(Node *head) {
    if(head == nullptr) return 0;
    return (head -> data) + sum(head -> next);
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

static int sortA(Node *h1, Node *h2) {
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

void swap(Node *head, Node *h1, Node *h2) {
    Node *prevH1 = getPrevious(head, h1);
    Node *prevH2 = getPrevious(head, h2);
    
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
                swap(*head, cur, nextCur);
                swapped = true;
                
                if(getPrevious(*head, cur) == nullptr)
                    *head = nextCur;
            }
            else{
                cur = nextCur;
            }
            nextCur = cur -> next;
        }
    }
}

int main()
{
    /* Problema 1 */
    Node *head1 = (Node*) malloc(sizeof(Node));
    head1 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head1, i + 1);
    }
    
    cout << "Problema 1\n";
    cout << "Input: ";
    printLinkedList(head1);
    cout << "Soma: " << sum(head1);
    
    cout << "\n\n";
    /* Fim problema 1 */
    
    
    /* Problema 2 */
    Node *head2 = (Node*) malloc(sizeof(Node));
    head2 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head2, 2 * i);
    }
    
    Node *head3 = (Node*) malloc(sizeof(Node));
    head3 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head3, 5 * i);
    }
    
    Node *head = concat(head2, head3);
    
    cout << "Problema 2\n";
    cout << "Input1: ";
    printLinkedList(head2);
    cout << "Input2: ";
    printLinkedList(head3);
    cout << "Concat: ";
    printLinkedList(head);
    
    cout << "\n";
    /* Fim problema 2*/
    
    /* Problema 3 */
    Node* head4 = (Node *) malloc(sizeof(Node));
    head4 -> data = 1;
    for(int i =1; i < 10; i++) {
        insert(head4, pow(-1, i) * i);
    }
    
    cout << "Problema 3\n";
    cout << "Input :";
    printLinkedList(head4);
    cout << "Bubble sort ascendente: ";
    sortBubble(&head4, sortA);
    printLinkedList(head4);
    cout << "Bubble sort decrescente: ";
    sortBubble(&head4, sortD);
    printLinkedList(head4);
    
    cout << "\n";
    /* Fim problema 3 */
    
    /* Problema 4 */ 
    Node *head5 = (Node*) malloc(sizeof(Node));
    head5 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head5, pow(-1, i) * i);
    }
    
    Node *head6 = (Node*) malloc(sizeof(Node));
    head6 -> data = 1;
    for(int i = 1; i < 10; i++){
        insert(head6, 2 * i);
    }
    
    Node2 *head7 = (Node2*) malloc(sizeof(Node2));
    head7 -> node = head1;
    head7 -> next = nullptr;
    insert2(head7, head2);
    
    cout << "\tProblema 4\n";
    cout << "- First Node  -\t" << "Endereco: " << head7 << "\thead linked list: " << head7 -> node << endl;
    cout << "- Secont Node -\t" << "Endereco: " << head7 -> next << "\thead linked list: " << head7 -> next -> node << endl;
    printLinkedList2(head7);
    /* Fim problema 4 */
    
    return 0;
}
