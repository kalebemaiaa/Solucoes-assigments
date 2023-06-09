#include <iostream>
#include <cmath>

using namespace std;

struct Node
{
    string data;
    Node *next, *prev;
};

// ~Transforma letra em numero para saber se e valida
int transformLetter(char letter)
{
    string vogais = "AUY";
    string consoantes = "BJRST";

    for (int i = 0; vogais[i] != '\0'; i++)
        if (letter == vogais[i])
            return 1;

    for (int i = 0; consoantes[i] != '\0'; i++)
        if (letter == consoantes[i])
            return 0;

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

void insert(Node *head, string palavra)
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
    cout << head->data << "  ";

    printDoubleLinkedList(head->next);
}

// ~Deleta por palavra (somente a primeira ocorrencia);
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
        free(tmp);
        (*head)->prev = nullptr;
        return;
    }

    tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;
    free(tmp);
}

// ~Deleta por endereco
static void deleteNode(Node *lixo)
{
    // ~Supomos lixo diferente de head
    lixo->prev->next = lixo->next;
    if (lixo->next)
        lixo->next->prev = lixo->prev;
    free(lixo);
}

int convert(char letter)
{
    string base = "AUYBJSRT";
    int i = 0;
    while (base[i] != '\0')
    {
        if (base[i++] == letter)
            return i - 1;
    }
    return -1;
}

// ~Ordem alfabetica lingua estranha
bool comparasionC(string s1, string s2)
{
    if (s1 == s2)
        return false;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] == s2[i++])
            continue;

        if (convert(s1[i - 1]) < convert(s2[i - 1]))
            return false;
        else
            return true;
    }

    if (s2[i - 1] == '\0')
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
            if (compare(nextCur->data, cur->data))
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
    temp->prev = nullptr;
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

void deleteMostFrequently(Node **head)
{
    Node *tmp = *head;
    if (tmp == nullptr || tmp->next == nullptr)
        return;
    int maxCount = 1, searcherCount;

    // ~Computa o numero de vezes que a primeira palavra aparece;
    while (tmp->data == tmp->next->data)
    {
        maxCount++;
        tmp = tmp->next;
    }

    tmp = tmp->next;
    // ~Procurar maxima frequencia

    while (tmp->next != nullptr)
    {
        searcherCount = 1;

        // ~Enquanto for a mesma palavra, incrementar searcher;
        while (tmp->data == tmp->next->data)
        {
            searcherCount++;
            tmp = tmp->next;

            // ~Chegou no final da lista pelo loop de dentro
            if (tmp->next == nullptr)
                break;
        }

        // ~Se a nova palavra aparece mais, susbstituir;
        if (searcherCount > maxCount)
            maxCount = searcherCount;

        // ~Chegou no final da lista pelo loop de dentro
        if (tmp->next == nullptr)
            break;
        tmp = tmp->next;
    }

    // ~Deletando as que tem frequencia maxima;
    while (tmp->prev != nullptr)
    {
        searcherCount = 1;

        while (tmp->data == tmp->prev->data)
        {
            searcherCount++;
            tmp = tmp->prev;

            // ~Chegou no final da lista pelo loop de dentro
            if (tmp->prev == nullptr)
                break;
        }

        // ~Palavra tem frequencia igual a maior
        if (searcherCount == maxCount)
        {
            cout << "Palavra [" << tmp->data << "] deletada pois apareceu " << maxCount << " vezes na lista." << endl;
            // ~Se o no for a head
            if (!tmp->prev)
            {
                // ~Apagra proximas n - 1 palavras
                for (int i = maxCount - 1; i > 0; i--)
                {
                    deleteNode(tmp->next);
                }
                // ~Apaga head e libera memoria.
                *head = tmp->next;
                (*head)->prev = nullptr;
                free(tmp);
                return;
            }
            else
            {
                tmp = tmp->prev;
                for (int i = maxCount; i > 0; i--)
                {
                    deleteNode(tmp->next);
                }
            }
        }
        // ~Proxima celula/palavra
        else
        {
            if (!tmp->prev)
                break;
            tmp = tmp->prev;
        }
    }
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
        insert(head, buffer);
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

    Node *head = openFile(sNomeArquivo);

    if(head == nullptr) return 1;
    /*
    //printDoubleLinkedList(head);

    // ~Inserindo palavra invalida
    cout << endl;
    cout << "\tInserindo palavras 'nao validas'\n\n";
    insert(head, "DESGOSTO");
    insert(head, "A");
    insert(head, "BABABABABABABA");

    // ~Procurando palavra
    cout << endl;
    cout << "\tLocalizando palavras (se esta em 0 nao foi encontrada)\n\n";
    cout << "Palavra 'BABA' em: " << findNode(head, "BABA") << endl;
    cout << "Palavra 'AS' em: " << findNode(head, "AS") << endl;

    */
    // ~Merge sort

    /*
    cout << endl;
    Node *second = split(head);
    //head = mergeSort(head, comparasionC);
    printDoubleLinkedList(head);
    printDoubleLinkedList(second);
    sortBubble(&head, comparasionC);
    sortBubble(&second, comparasionC);
    printDoubleLinkedList(second);
    cout << second -> prev -> data << endl;
    cout << endl;
    cout << myMerge(head, second, comparasionC) -> data;
    */
    // ~Ordenando com bubble
    cout << endl;
    sortBubble(&head, comparasionC);
    // ~Deletando a mais frequente;
    cout << endl;
    cout << "\tLista apos deletar palavra mais frequente\n\n";
    deleteMostFrequently(&head);
    return 0;
}