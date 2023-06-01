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

int convert(string palavra) {
    int n = 0;
    string base = "AUYBJSRT";
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        for(int j = 0; base[j] != '\0'; j++) {
            if(toupper(palavra[i]) == base[j])
                n += (1 + j) * (pow(10, palavra.length() - i - 1));
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
    /*
        Falta fzr para o caso C, B
        para o head e o end;
    */
    
    Node *tmpPrev = h2 -> prev;
    Node *tmpNext = h2 -> next;
    
    if(h1 -> next == h2) {
        h2 -> next = h1;
        h2 -> prev = h1 -> prev;
        h1 -> prev -> next = h2;
        h1 -> prev = h2;
        h1 -> next = tmpNext;
        h1 -> next -> prev = h1;
        return;
    }
    
    
    h2 -> prev = h1 -> prev;
    h2 -> next = h1 -> next;
    if(h2 -> prev != nullptr)
        h2 -> prev -> next = h2;
    if(h2 -> next != nullptr)        
        h2 -> next -> prev = h2;
        
    h1 -> next = tmpNext;
    h1 -> prev = tmpPrev;
    if(h1 -> prev != nullptr)
        h1 -> prev -> next = h1;
    if(h1 -> next != nullptr)
        h1 -> next -> prev = h1;
        
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
    
    Node *h1 = findNode(head, "Ab");
    Node *h2 = findNode(head, "aba");
    Node *h3 = findNode(head, "ABUJY");
    Node *h4 = findNode(head, "Tura");
    Node *h5 = findNode(head, "suraTury");
    
    printDoubleLinkedList(h1);
    swap(&head, h2, h3);
    
    printDoubleLinkedList(h1);
    return 0;
}
