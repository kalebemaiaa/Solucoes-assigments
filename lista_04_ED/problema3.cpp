#include <iostream>
#include <cmath>

using namespace std;

typedef struct reg{
    int iData;
    struct reg *next;
} t_node;

typedef struct Node{
    t_node *head;
    Node *next;
} Node;

t_node *createNode(int value){
    t_node *newNode = new t_node;
    newNode -> next = nullptr;
    newNode -> iData = value;
    return newNode;
}

Node *createNewNode(t_node *ptrValue) {
    Node *newNode = new Node;
    newNode -> next = nullptr;
    newNode -> head = ptrValue;
    return newNode;
}

void insert(t_node *head, int value){
    if(!head) return;
    t_node *tmp;
    for(tmp = head; tmp -> next != nullptr; tmp = tmp -> next);
    tmp -> next = createNode(value);
}

void insertNode(Node *head, t_node *ptrValue) {
    if(!head) return;
    Node *tmp;
    for(tmp = head; tmp -> next != nullptr; tmp = tmp -> next);
    tmp -> next = createNewNode(ptrValue);
}

void printList(t_node *head){
    if(!head){
        cout << endl;
        return;
    }
    cout << head -> iData << " ";
    printList(head -> next);
}

void printMainList(Node *head) {
    if(!head){
        cout << endl;
        return;
    }
    cout << head << " : \t";
    printList(head -> head);
    printMainList(head -> next);
}

static int sortD(t_node *h1, t_node *h2){
    return h2 -> iData - h1 -> iData;
}

static int sortC(t_node *h1, t_node *h2){
    return h1 -> iData - h2 -> iData;
}

t_node *getPrevious(t_node *head, t_node *ptrNoh){
    if(head == nullptr) return nullptr;
    if(head -> next == ptrNoh) return head;
    return getPrevious(head -> next, ptrNoh);
}

void swap(t_node **head, t_node *h1, t_node *h2){
    if(!head || h1 == h2) return;
    t_node *prevH1 = getPrevious(*head, h1), *prevH2 = getPrevious(*head, h2);
    
    t_node *aux = h2 -> next;
    if(prevH1)
        prevH1 -> next = h2;
    h2 -> next = h1 -> next;
    if(prevH2)
        prevH2 -> next = h1;
    h1 -> next = aux;
    
    if(h1 -> next == h1) h1 -> next = h2;
    if(h2 -> next == h2) h2 -> next = h1;
    if(*head == h1) *head = h2;
    else if(*head == h2) *head = h1;
}

Node *getPrevious(Node *head, Node *ptrNoh){
    if(head == nullptr) return nullptr;
    if(head -> next == ptrNoh) return head;
    return getPrevious(head -> next, ptrNoh);
}

void swapNode(Node **head, Node *h1, Node *h2){
    if(!head || h1 == h2) return;
    Node *prevH1 = getPrevious(*head, h1), *prevH2 = getPrevious(*head, h2);
    
    Node *aux = h2 -> next;
    if(prevH1)
        prevH1 -> next = h2;
    h2 -> next = h1 -> next;
    if(prevH2)
        prevH2 -> next = h1;
    h1 -> next = aux;
    
    if(h1 -> next == h1) h1 -> next = h2;
    if(h2 -> next == h2) h2 -> next = h1;
    if(*head == h1) *head = h2;
    else if(*head == h2) *head = h1;
}

/*
    Procurar o maior ou menor elemento e swapar ele com o atua.
*/
void selectionSort(t_node **head, int (*compare)(t_node*, t_node*)){
    // ~Percorre a lista passada.
    for(t_node *cur = *head; cur -> next != nullptr;) {
        // ~Variável para armazenar o endereço min/max;
        t_node *searcher = cur;
        // ~Procura a partir do próximo. Se achar menor ou maior, troca o searcher.
        for(t_node *tmp = cur -> next; tmp != nullptr; tmp = tmp -> next)
            if(compare(searcher, tmp) > 0)
                searcher = tmp;
        
        // ~Swapa os nos e anda a lista.
        swap(head, cur, searcher);
        cur = searcher -> next;
    }
}

void ordena(Node **mainHead) {
    // ~Ordenando horizontalmente.
    for(Node *cur = *mainHead; cur != nullptr; cur = cur -> next) {
        selectionSort(&(cur -> head), sortC);
    }
    
    cout << "\t Lista Ordenada Horizontalmente:\n " << endl; 
    printMainList(*mainHead);

    // ~Ordenando verticalmente.
    for(Node *cur = *mainHead; cur != nullptr;) {
        Node *searcher = cur;
        for(Node *tmp = cur -> next; tmp != nullptr; tmp = tmp -> next)
            if(sortC(searcher -> head, tmp -> head) > 0)
                searcher = tmp;
        
        swapNode(mainHead, cur, searcher);
        cur = searcher -> next;
    }
}

int main() {
    t_node *h1 = createNode(1), *h2 = createNode(12), *h3 = createNode(-14), *h4 = createNode(15);
    for(int i = 2; i <=10; i++){
        insert(h4, 3 * i * pow(-1, i));
        insert(h1, -2 * i * pow(-1, i));
        insert(h2, i * pow(-1, i));
        insert(h3, (3 * i + i % 2 + i % 3 )* pow(-1, i));
    }

    cout << "\t Lista Original:\n " << endl;
    Node *head = createNewNode(h1);
    insertNode(head, h2);
    insertNode(head, h3);
    insertNode(head, h4);
    printMainList(head);

    // ~Função pedida:
    ordena(&head);
    cout << "\t Ordenando horizontalmente e ferticalmente:\n " << endl;
    printMainList(head);
    return 0;
}