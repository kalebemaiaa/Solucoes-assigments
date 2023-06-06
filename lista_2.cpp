#include <iostream>
#include <cmath>
#include <chrono> 

using namespace std;
using namespace std::chrono;

struct Node
{
    string data;
    Node *next;
    Node *prev;
};

int transformLetter(char letter)
{
    string vogais = "AUY";
    string consoantes = "BJRST";

    for (int i = 0; i < 3; i++)
    {
        if (letter == vogais[i])
            return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        if (letter == consoantes[i])
            return 0;
    }

    return -1;
}

bool isValid(string str)
{
    int primeiraLetra = transformLetter(str[0]);
    if (primeiraLetra == -1)
        return false;

    int i = 0, verificaAtual;

    while (str[i] != '\0')
    {
        verificaAtual = transformLetter(str[i]);
        if (i % 2 == 0 && verificaAtual != primeiraLetra)
            return false;
        else if (i % 2 == 1 && verificaAtual == primeiraLetra)
            return false;

        i++;
    }

    return true;
}

void insert(Node *head, string palavra)
{
    if (!isValid(palavra))
    {
        cout << "Error: a palavra [" << palavra << "] inserida nao e valida." << endl;
        return;
    }

    while (head->next)
        head = head->next;

    Node *newNode = new Node;
    
    newNode->prev = head;
    newNode->next = nullptr;
    newNode->data = palavra;
    head->next = newNode;
}

Node *findNode(Node *head, string palavra)
{
    if (head == nullptr)
        return nullptr;
    if (head->data == palavra)
        return head;
    return findNode(head->next, palavra);
}

void printDoubleLinkedList(Node *head)
{
    if (!head)
    {
        cout << endl;
        return;
    }
    cout << head->data << "\t";

    printDoubleLinkedList(head->next);
}

void deleta(Node **head, string palavra)
{
    Node *tmp = findNode(*head, palavra);

    if (!tmp)
    {
        cout << "A palavra [" << palavra << "] nao foi encontrada na lista e nao foi possivel deletar ela.\n";
        return;
    }

    if (tmp == *head)
    {
        *head = tmp->next;
        (*head)->prev = nullptr;
        return;
    }

    tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;
    free(tmp);
}

int convert(string palavra)
{
    int n = 0;
    string base = "AUYBJSRT";

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        for (int j = 0; base[j] != '\0'; j++)
        {
            if (palavra[i] == base[j])
                n += (1 + j) * (pow(10, (7 - i)));
        }
    }

    return n;
}

bool comparasionC(string s1, string s2)
{
    if (convert(s2) < convert(s1))
        return true;
    return false;
}

bool comparasionD(string s1, string s2)
{
    if (convert(s1) < convert(s2))
        return true;
    return false;
}

void swap(Node **head, Node *h1, Node *h2)
{
    Node *tmpPrev = h2->prev;
    Node *tmpNext = h2->next;
    if (h1 == h2)
        return;

    h2->prev = h1->prev;
    h2->next = h1->next;
    h1->next = tmpNext;
    h1->prev = tmpPrev;

    // ~Caso estaja do lado (B, C)
    if (h2->next == h2)
        h2->next = h1;
    h1->prev = h2;

    // ~Caso esteja do lado (C, B)
    if (h2->prev == h2)
        h2->prev = h1;
    h2->next = h1;

    // ~Setando os prev e next para apontar no swap;
    if (h2->prev != nullptr)
        h2->prev->next = h2;
    else
    {
        *head = h2;
    }
    if (h1->prev != nullptr)
        h1->prev->next = h1;
    else
    {
        *head = h1;
    }
    if (h2->next != nullptr)
        h2->next->prev = h2;
    if (h1->next != nullptr)
        h1->next->prev = h1;
}

void sortBubble(Node **head, bool (*compare)(string a, string b)) {
    Node *cur;
    Node *nextCur;
    bool swapped = true;
    
    while(swapped) {
        swapped = false;
        cur = *head;
        nextCur = cur -> next;
        
        while(nextCur != nullptr) {
            if(compare( nextCur -> data, cur -> data)){
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
    struct Node *fast = head, *slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

Node *merge(Node *first, Node *second, bool (*compare)(string a, string b))
{
    // If first linked list is empty
    if (first == nullptr)
        return second;

    // If second linked list is empty
    if (second == nullptr)
        return first;

    if (compare(first->data, second->data))
    {
        first->next = merge(first->next, second, compare);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first, second->next, compare);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// Function to do merge sort
Node *mergeSort(Node *head, bool (*compare)(string a, string b))
{
    if (head == nullptr || head->next == nullptr)
        return head;
    Node *second = split(head);

    // Recur for left and right halves
    head = mergeSort(head, compare);
    second = mergeSort(second, compare);

    // Merge the two sorted halves
    return merge(head, second, compare);
}

void delteMostFrequently(Node **head)
{
    Node *tmp = *head;

    string mostFrequently = tmp -> data;
    int maxCount = 1;

    // ~Computa o numero de vezes que a primeira palavra aparece;
    while (tmp->data == tmp->next->data)
    {
        maxCount++;
        tmp = tmp->next;
    }
    
    tmp = tmp -> next;
    // ~Enquanto nao chegar no fim da lista
    while (tmp->next != nullptr)
    {   
        // ~Enquanto for a mesma palavra, incrementar searcher;
        int searcherCount = 1;
        
        while (tmp->data == tmp->next->data)
        {
            searcherCount++;
            tmp = tmp->next;
            
            // ~Chegou no final da lista pelo loop de dentro
            if(tmp -> next == nullptr) break;
        }
        
        // ~Se a nova palavra aparece mais, susbstituir;
        if (searcherCount > maxCount)
        {
            maxCount = searcherCount;
            mostFrequently = tmp->data;
        }
        
        // ~Chegou no final da lista pelo loop de dentro
        if(tmp -> next == nullptr) break;
        tmp = tmp->next;
    }

    // ~Deletando a que mais se repete;
    while (maxCount > 0)
    {
        deleta(head, mostFrequently);
        maxCount--;
    }
}



int main()
{
    Node *head = new Node;
    char t[] = "AB";

    head->prev = nullptr;
    head->next = nullptr;
    head->data = t;
    
    insert(head, "ABA");
    insert(head, "ABUJY");
    insert(head, "TURA");
    
    // ~Lista inicial
    //printDoubleLinkedList(head);

    // ~Lista ordenada em ordem decrescente;
    
    // ~Contabilizando tempo;
    /*
    auto timeStart = high_resolution_clock::now();
    head = mergeSort(head, comparasionD);
    auto timeStop = high_resolution_clock::now();
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    printDoubleLinkedList(head);
    cout << timeDuration.count() << endl;
    */
    
    // ~Lista com a palavra que mais repete deletada;
    //printDoubleLinkedList(head);
    head = mergeSort(head, comparasionD);
    printDoubleLinkedList(head);
    delteMostFrequently(&head);
    printDoubleLinkedList(head);
    return 0;
}
    /*
    FILE *inp = fopen("palavras_100.txt", "r");
    int max;
    fscanf(inp, "%i", &max);
    for(int i = 0; i < max; i++) {
        char buffer[9];
        fscanf(inp, "%s", buffer);
        insert(head, buffer);
    }
    fclose(inp)
    */
