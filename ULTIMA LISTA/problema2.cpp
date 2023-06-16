#include <iostream>
#include <cmath>

using namespace std;

typedef struct reg{
    int iData;
    struct reg *next;
} t_node;

t_node *createNode(int value){
    t_node *newNode = new t_node;
    newNode -> next = nullptr;
    newNode -> iData = value;
    return newNode;
}

void insert(t_node *head, int value){
    if(!head) return;
    t_node *tmp;
    for(tmp = head; tmp -> next != nullptr; tmp = tmp -> next);
    tmp -> next = createNode(value);
}

void printList(t_node *head){
    if(!head){
        cout << endl;
        return;
    }
    cout << head -> iData << " ";
    printList(head -> next);
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

void selectionSort(t_node **head, int (*compare)(t_node*, t_node*)){
    for(t_node *cur = *head; cur -> next != nullptr;) {
        t_node *searcher = cur;
        for(t_node *tmp = cur -> next; tmp != nullptr; tmp = tmp -> next){
            if(compare(searcher, tmp) > 0)
                searcher = tmp;
        }
        swap(head, cur, searcher);
        cur = searcher -> next;
    }
}

void insertAfter(t_node *head, t_node *ptrNoh) {
    t_node *aux = head -> next;
    head -> next = ptrNoh;
    ptrNoh -> next = aux;
}

void insertionSort(t_node **head, int (*compare)(t_node *, t_node *)) {
    t_node *retorno = *head, *aux;
    
    for(t_node *tmp = retorno -> next; tmp != nullptr; tmp = aux){
        aux = tmp -> next;
        if(compare(retorno, tmp) > 0) {
            tmp -> next = retorno;
            retorno = tmp;
            continue;
        }
        for(t_node *baseAtual = retorno; baseAtual != nullptr; baseAtual = baseAtual -> next) {
            t_node *cur = baseAtual -> next;
            if(!cur){
                insertAfter(baseAtual, tmp);
                break;
            }
            if(compare(cur, tmp) > 0) {
                insertAfter(baseAtual, tmp);
                break;
            }
        }
    }
    *head = retorno;
}

int main()
{
    t_node *h1 = createNode(1), *h2 = createNode(12), *h3 = createNode(-14), *h4 = createNode(15);
    for(int i = 2; i <=10; i++){
        insert(h1, 3 * i * pow(-1, i));
        insert(h3, -2 * i * pow(-1, i));
        insert(h2, i * pow(-1, i));
        insert(h4, 3 * i + i % 2 + i % 3 * pow(-1, i));
    }
    
    
    // INSERTION SORT   
    cout << "\t- INSERTION SORT -\n\n";
    cout << "LISTA ORIGINAL: \t";
    printList(h3);
    cout << "LISTA CRESCENTE: \t";
    insertionSort(&h3, sortC);
    printList(h3);
    
    cout << "LISTA ORIGINAL: \t";
    printList(h4);
    cout << "LISTA DECRESCENTE: \t";
    insertionSort(&h4, sortD);
    printList(h4);

    cout << endl;
    // SELECTION SORT   
    cout << "\t- SELECTION SORT -\n\n";
    cout << "LISTA ORIGINAL: \t";
    printList(h1);
    
    cout << "LISTA CRESCENTE: \t";
    selectionSort(&h1, sortC);
    printList(h1);
    
    
    cout << "LISTA ORIGINAL: \t";
    printList(h2);
    cout << "LISTA DECRESCENTE: \t";
    selectionSort(&h2, sortD);
    printList(h2);
    return 0;
}

