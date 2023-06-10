#include <iostream>

using namespace std;

struct Node
{
    string data;
    Node *next, *prev;
};

// ~Transforma letra em numero para saber se e valida
int transformLetter(char letter)
{
    string alphabeto = "AUYBJRST";

    for(int i = 0; alphabeto[i] != '\0'; i++) {
        if(letter != alphabeto[i]) continue;
        if(i < 3) return 1;
        return 0;
    }

    return -1;
}

// ~Verifica se uma palavra e valida
bool isValid(string str)
{
    int i = 0, len = str.length(), atual;
    if (len < 2 || len > 8)
        return false;

    while (i < len)
    {
        atual = transformLetter(str[i++]);
        if (atual == -1)
            return false;
        if (atual == transformLetter(str[i]))
            return false;
    }
    return true;
}

void insertEnd(Node *head, string palavra)
{
    if (!isValid(palavra))
    {
        cout << "Error: a palavra [" << palavra << "] nao e valida e nao foi inserida!" << endl;
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

void printDoubleLinkedList(Node *head)
{
    if (!head)
    {
        cout << endl;
        return;
    }
    cout << head->data << "  ";

    printDoubleLinkedList(head->next);
}

// ~Verifica qual letra vem antes 
int convert(char letter)
{
    string alphabeto = "AUYBJSRT";
    int i = 0;
    while (alphabeto[i] != '\0')
    {
        if (alphabeto[i++] == letter)
            return i - 1;
    }
    return -1;
}

// ~Ordem alfabetica lingua estranha
bool comparasion(string s1, string s2)
{
    if (s1 == s2)
        return false;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] == s2[i]) {
            i++;
            continue;
        }

        if (convert(s1[i]) < convert(s2[i]))
            return false;
        else
            return true;
    }

    if (s2[i] == '\0')
        return true;
    return false;
}

// ~Funcao para trocar celulas em lista
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

void sortBubble(Node **head, bool (*compare)(string a, string b))
{
    if (*head == nullptr)
        return;
    Node *cur, *nextCur;
    bool swapped = true;

    while (swapped)
    {
        swapped = false;
        cur = *head;
        nextCur = cur->next;

        while (nextCur != nullptr)
        {
            if (!compare(nextCur->data, cur->data))
            {
                swap(head, cur, nextCur);
                swapped = true;
            }
            else
            {
                cur = nextCur;
            }
            nextCur = cur->next;
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
    slow->next = nullptr;
    return temp;
}

Node *merge(Node *h1, Node *h2, bool (*compare)(string a, string b)) {
    Node *head, *aux, *pseudoHead = nullptr;
    
    while(h1 && h2) {
        if(compare(h1 -> data, h2 -> data)){
            aux = h2;
            h2 = h2 -> next;
        }
        else{
            aux = h1;
            h1 = h1 -> next;
        }
        if(!pseudoHead) {
            head = aux;
            pseudoHead = head;
            aux -> prev = nullptr;
            aux -> next = nullptr;
        }
        else{
            pseudoHead -> next = aux;
            aux -> prev = pseudoHead;
            pseudoHead = aux;
            pseudoHead -> next = nullptr;
        }
    }


    while (h1 != nullptr)
    {
        aux = h1;
        h1 = h1-> next;
        pseudoHead -> next = aux;
        aux -> prev = pseudoHead;
        pseudoHead = pseudoHead -> next;
    }
    while (h2)
    {
        aux = h2;
        h2 = h2-> next;
        pseudoHead -> next = aux;
        aux -> prev = pseudoHead;
        pseudoHead = pseudoHead -> next;
    }

    return head;
}

bool is_ordened(Node *head, bool (*compare)(string a, string b)) {
    while(head -> next) {
        if(compare(head->data, head->next->data))
            return false;
        head = head -> next;
    }
    return true;
}

Node *mergeSort(Node *head, bool (*compare)(string a, string b))
{
    if(head == nullptr || is_ordened(head, compare)) return head;
    
    Node *half = split(head);
    head = mergeSort(head, compare);
    half = mergeSort(half, compare);

    return merge(head, half, compare);
}

// ~Abre arquivo com palavras aleatórias e cria uma lista encadeada
Node *openFile(string sNameFile)
{
    FILE *inp = fopen(sNameFile.c_str(), "r");
    if (inp == nullptr)
    {
        cout << "Error: Nao consegui abrir o arquivo [" << sNameFile << "]" << endl;
        return nullptr;
    }

    Node *head = new Node;
    head->prev = nullptr;
    head->next = nullptr;

    // ~Total de palavras a serem lidas
    int nPalavras;
    fscanf(inp, "%i", &nPalavras);

    char buffer[10];
    // ~Carrega primeira palavra para ser head -> data
    fscanf(inp, "%s", buffer);
    head->data = buffer;
    // ~Lendo palavras row by row e inserindo na lista
    for (int i = 0; i < nPalavras - 1; i++)
    {
        fscanf(inp, "%s", buffer);
        insertEnd(head, buffer);
    }
    fclose(inp);

    cout << "Arquivo carregado gerou a lista com head: " << head << "\nvalores: ";
    printDoubleLinkedList(head);
    return head;
}

int main()
{
    string sNomeArquivo;
    cout << "Digite o nome do arquivo: ";
    cin >> sNomeArquivo;
    cout << endl;

    Node *headB = openFile(sNomeArquivo);
    if(headB == nullptr) return 1;
    cout << "Ordenando com bubble: ";
    auto t1B = chrono::high_resolution_clock::now();
    sortBubble(&headB, comparasion);
    auto t2B = chrono::high_resolution_clock::now();
    auto durationB = chrono::duration_cast<chrono::nanoseconds>( t2B - t1B ).count();
    cout << "Tempo de execucao bubble: " << durationB << endl;
    cout << "lista: ";
    printDoubleLinkedList(headB);

    cout << "\n\n";
    Node *headM = openFile(sNomeArquivo);
    if(headM == nullptr) return 1;
    cout << "Ordenando com merge: ";
    auto t1M = chrono::high_resolution_clock::now();
    headM = mergeSort(headM, comparasion);
    auto t2M = chrono::high_resolution_clock::now();
    auto durationM = chrono::duration_cast<chrono::nanoseconds>( t2M - t1M ).count();
    cout << "Tempo de execucao merge: " << durationM << endl;
    cout << "lista: ";
    printDoubleLinkedList(headM);
    return 0;
}