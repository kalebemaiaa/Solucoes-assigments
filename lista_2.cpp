#include <iostream>
#include <cmath>

using namespace std;

struct Node{
    string data;
    Node *next;
    Node *prev;
};

int transformLetter(char letter) {
    string vogais = "AUY";
    string consoantes = "BJRST";
    
    for(int i = 0; i < 3; i++) {
        if(toupper(letter) == vogais[i] ) 
            return 1;
    }
    
    for(int i = 0; i < 5; i++) {
        if(toupper(letter) == consoantes[i] ) 
            return 0;
    }
    
    return -1;
}

bool isValid(string str) {
    int primeiraLetra =transformLetter(str[0]);
    if(primeiraLetra == -1)
        return false;
    
    int i = 0;
    for(; str[i] != '\0'; i++) {
        int verificaAtual = transformLetter(str[i]);
        
        if(i % 2 == 0 && verificaAtual != primeiraLetra)
            return false;
        else if(i % 2 == 1 && verificaAtual == primeiraLetra)
            return false;
    }
    
    return true;
}

void insert(Node *head, string palavra) {
    if(!isValid(palavra)) {
        cout << "Error: a palavra inserida nao e valida. " << endl;
        return;
    }
    
    while(head -> next)
        head = head -> next;
        
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> prev = head;
    newNode -> next = nullptr;
    newNode -> data = palavra;
    head -> next = newNode;
    return ;
}

Node *findNode(Node *head, string palavra) {
    while(head != nullptr) {
        if(palavra.compare(head -> data) == 0)
            return head;
        head = head -> next;
    }
    
    return nullptr;
}

void printDoubleLinkedList(Node *head){
    if(!head){
        cout << endl;
        return;
    }
    
    cout << head -> data << "\t";
    
    printDoubleLinkedList(head -> next);
}

void deleta(Node **head, string palavra) {
    Node *tmp = findNode(*head, palavra);
    
    if(tmp == *head){
        *head =  tmp -> next;
        (*head) -> prev = nullptr;
        return;
    }
    
    tmp -> prev -> next = tmp -> next;
    tmp -> next -> prev = tmp -> prev;
    free(tmp);
}

static int convert(string palavra) {
    int n = 0;
    string base = "AUYBJSRT";
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        for(int j = 0; base[j] != '\0'; j++) {
            if(toupper(palavra[i]) == base[j])
                n += (1 + j) * (pow(10, (7 - i)));
        }
    }
    
    return n;
}

bool comparasion(string s1, string s2) {
    if( convert(s1) < convert(s2)) 
        return true;
    return false;
}

void swap(Node **head, Node *h1, Node *h2) {
    Node *tmpPrev = h2 -> prev;
    Node *tmpNext = h2 -> next;
    if(h1 == h2) return;
    
    h2 -> prev = h1 -> prev;
    h2 -> next = h1 -> next;
    h1 -> next = tmpNext;
    h1 -> prev = tmpPrev;
    
    // ~Caso estaja do lado (B, C)
    if(h2 -> next == h2) 
        h2 -> next = h1;
        h1 -> prev = h2;
        
    // ~Caso esteja do lado (C, B)
    if(h2 -> prev == h2) 
        h2 -> prev = h1;
        h2 -> next = h1;
    
    // ~Setando os prev e next para apontar no swap;
    if(h2 -> prev != nullptr)
        h2 -> prev -> next = h2;
    else {
        *head = h2;
    }
    if(h1 -> prev != nullptr)
        h1 -> prev -> next = h1;
    else{
        *head = h1;
        cout << "ou" << endl;
    }
    if(h2 -> next != nullptr)        
        h2 -> next -> prev = h2;
    if(h1 -> next != nullptr)
        h1 -> next -> prev = h1;
}

void sortBubble(Node **head) {
    Node *cur;
    Node *nextCur;
    bool swapped = true;
    
    while(swapped) {
        swapped = false;
        cur = *head;
        nextCur = (*head) -> next;
        
        while(nextCur != nullptr) {
            if(!comparasion(cur -> data, nextCur -> data)){
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

Node *split(Node *head)
{
    struct Node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

Node *merge(Node *first,Node *second)
{
    // If first linked list is empty
    if (first == nullptr)
        return second;
 
    // If second linked list is empty
    if (second == nullptr)
        return first;
 
    // Pick the smaller value
    if (!comparasion(first->data, second->data))
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
 
// Function to do merge sort
Node *mergeSort(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    Node *second = split(head);
 
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
 
    // Merge the two sorted halves
    return merge(head,second);
}


int main()
{
    Node *head = (Node *) malloc(sizeof(Node));
    string t = "Ab";
    
    head -> prev = nullptr;
    head -> next = nullptr;
    head -> data = t;
    
    insert(head, "aba");
    insert(head, "ABUJY");
    insert(head, "Tura");
    insert(head, "suraTury");
    insert(head, "suraTura");
    
    sortBubble(&head);
    
    
    
    printDoubleLinkedList(head);
    
    head = mergeSort(head);
    
    printDoubleLinkedList(head);
    
    return 0;
}
