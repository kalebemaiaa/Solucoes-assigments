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

int length(Node* head){
    Node* temp = head ;
    int len = 0 ;
     while(temp!=NULL)
     {
         len++;
         temp=temp->next ;
     }
    
    return  len;
}

void bubbleSort(struct Node** head, int count)
{
    struct Node** h;
    int i, j, swapped;
 
    for (i = 0; i <= count; i++)
    {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < count - i - 1; j++)
        {
 
            struct Node* p1 = *h;
            struct Node* p2 = p1->next;
 
            if (comparasion(p1->data, p2->data))
            {
                swap(head, p1, p2);
                swapped = 1;
            }
 
            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
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
    return head;
}

int main()
{
    /*
    Forma: (wr_nPalavras _> tempo e nanosegundos)

    Tempos de execucao:
        merge:
            (wr_100 -> 236576)
            (wr_1000 -> 3351216)
            (wr_10000 -> 37353399)
            (wr_100000 -> 469294836)
        bubble:
            (wr_100 -> 1478986)
            (wr_1000 -> 141114262)
            (wr_10000 -> 12966195023)
            (wr_100000 -> 1245513327688) //Quase desisti de esperar
    */
    string sNomeArquivo;
    cout << "Digite o nome do arquivo: ";
    cin >> sNomeArquivo;
    cout << endl;

    Node *headB = openFile(sNomeArquivo);
    if(headB == nullptr) return 1;
    auto t1B = chrono::high_resolution_clock::now();
    bubbleSort(&headB, length(headB));
    auto t2B = chrono::high_resolution_clock::now();
    auto durationB = chrono::duration_cast<chrono::nanoseconds>( t2B - t1B ).count();
    cout << "Tempo de execucao bubble: " << durationB << endl;

    Node *headM = openFile(sNomeArquivo);
    if(headM == nullptr) return 1;
    auto t1M = chrono::high_resolution_clock::now();
    headM = mergeSort(headM, comparasion);
    auto t2M = chrono::high_resolution_clock::now();
    auto durationM = chrono::duration_cast<chrono::nanoseconds>( t2M - t1M ).count();
    cout << "Tempo de execucao merge: " << durationM << endl;

    return 0;
}