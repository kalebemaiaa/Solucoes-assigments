#ifndef AUXILIAR_FUNCTIONS_H_INCLUDED
#define AUXILIAR_FUNCTIONS_H_INCLUDED

using namespace std;

struct Node
{
    string data;
    Node *next, *prev;
};

// ~Problema 1
// ~Item a
int transformLetter(char letter);
bool isValid(string str);

// ~Item b
void insert(Node *head, string palavra);

// ~Item c
Node *findNode(Node *head, string palavra);

// ~Item d
static void deleteNode(Node *lixo);
void deleta(Node **head, string palavra);

// ~Item e
void printDoubleLinkedList(Node *head);

// ~Item f
int convert(string palavra);
bool comparasionC(string s1, string s2);
bool comparasionD(string s1, string s2);

// ~Problema 2
void insert(Node *h1, Node *h2);
Node *split(Node *head);
Node *mergeSort(Node *head, bool (*compare)(string a, string b));
Node *myMerge(Node *h1, Node *h2, bool (*compare)(string a, string b)) ;
Node *merge(Node *first, Node *second, bool (*compare)(string a, string b));


// ~Problema 3
void deleteMostFrequently(Node **head);

// ~Problema 4
Node *openFile(string sNameFile);
void swap(Node **head, Node *h1, Node *h2);
void sortBubble(Node **head, bool (*compare)(string a, string b));
#endif 