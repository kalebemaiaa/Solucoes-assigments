#include <iostream>
#include <cmath>
#include <chrono> 
#include "auxiliar_functions.h"

using namespace std;
using namespace std::chrono;

// ~Transforma letra em numero para saber se e valida
int transformLetter(char letter)
{
    string vogais = "AUY";
    string consoantes = "BJRST";

    for (int i = 0; i < 3; i++)
        if (letter == vogais[i])
            return 1;

    for (int i = 0; i < 5; i++)
        if (letter == consoantes[i])
            return 0;

    return -1;
}

// ~Verifica se uma palavra e valida
bool isValid(string str)
{
    /*
        A ideia aqui e ver se a primeira e valida, se sim,
        toda letra em posicao par deve ter o mesmo valor 
        que ela e em posicao impar deve ter valor diferente.
    */
    int primeiraLetra = transformLetter(str[0]);
    if (primeiraLetra == -1)
        return false;

    int i = 0, verificaAtual;

    while (str[i] != '\0')
    {
        verificaAtual = transformLetter(str[i++]);
        if (i % 2 == 0 && verificaAtual != primeiraLetra)
            return false;
  
        else if (i % 2 == 1 && verificaAtual == primeiraLetra)
            return false;


    }
    
    // ~Tem menos de 2 letras ou mais de 8.
    if(i <= 1 || i > 8)
        return false;

    return true;
}

void insert(Node *head, string palavra)
{
    if (!isValid(palavra))
    {
        cout << "Error: a palavra [" << palavra << "] nao e valida e nao foi inserida!" << endl;
        return;
    }

    while(head->next)
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
static void deleteNode(Node *lixo) {
    // ~Supomos lixo diferente de head
    lixo -> prev -> next = lixo -> next;
    if(lixo -> next)
        lixo -> next -> prev = lixo -> prev;
    free(lixo);
}

int convert(string palavra)
{
    /*
        A ideia aqui e converte uma string para numero,
        ja que so temos oito letras possiveis.
    */
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

// ~Ordem alfabetica lingua estranha
bool comparasionC(string s1, string s2)
{
    if (convert(s2) < convert(s1))
        return true;
    return false;
}

// ~Ordem alfabetica invertida lingua estranha
bool comparasionD(string s1, string s2)
{
    if (convert(s1) < convert(s2))
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

void sortBubble(Node **head, bool (*compare)(string a, string b)) {
    if(*head == nullptr) return;
    Node *cur, *nextCur;
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
    slow->next = nullptr;
    temp -> prev = nullptr;
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
    if(tmp == nullptr || tmp -> next == nullptr) return;
    int maxCount = 1, searcherCount;
    
    // ~Computa o numero de vezes que a primeira palavra aparece;
    while (tmp->data == tmp->next->data)
    {
        maxCount++;
        tmp = tmp->next;
    }
    
    tmp = tmp -> next;
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
            if(tmp -> next == nullptr) break;
        }
        
        // ~Se a nova palavra aparece mais, susbstituir;
        if (searcherCount > maxCount)
            maxCount = searcherCount;
        
        // ~Chegou no final da lista pelo loop de dentro
        if(tmp -> next == nullptr) break;
        tmp = tmp->next;
    }

    // ~Deletando as que tem frequencia maxima;
    while (tmp -> prev != nullptr) 
    {
        searcherCount = 1;
        
        while (tmp->data == tmp->prev->data)
        {
            searcherCount++;
            tmp = tmp->prev;
            
            // ~Chegou no final da lista pelo loop de dentro
            if(tmp -> prev == nullptr) break;
        }
        
        // ~Palavra tem frequencia igual a maior
        if(searcherCount == maxCount) {
            cout << "Palavra [" << tmp -> data << "] deletada pois apareceu " << maxCount << " vezes na lista." << endl;
            // ~Se o no for a head
            if(!tmp -> prev){
                // ~Apagra proximas n - 1 palavras
                for(int i = maxCount - 1; i > 0; i--) {
                    deleteNode(tmp -> next);
                }
                // ~Apaga head e libera memoria.
                *head = tmp -> next;
                (*head) -> prev = nullptr;
                free(tmp);
                return;
            }
            else{
                tmp = tmp -> prev;
                for(int i = maxCount; i > 0; i--) {
                    deleteNode(tmp -> next);
                }
            }
        }
        // ~Proxima celula/palavra
        else{
            if(!tmp -> prev) break;
            tmp = tmp->prev;
        }
    }
}

// ~Abre arquivo com palavras aleatórias e cria uma lista encadeada
Node *openFile(string sNameFile) {
    char *nameFile = (char *) malloc(sizeof(char) * (sNameFile.length() + 1));
    copy(sNameFile.begin(), sNameFile.end(), nameFile);
    FILE *inp = fopen(nameFile, "r");
    if(inp == nullptr){
        cout << "Error: Nao consegui abrir o arquivo [" << sNameFile << "]" << endl;
        return nullptr;
    }
    
    Node *head = (Node *) malloc(sizeof(Node));
    head -> prev = nullptr;
    head -> next = nullptr;
    
    // ~Total de palavras a serem lidas
    int nPalavras;
    fscanf(inp, "%i", &nPalavras);
    
    
    char buffer[9];
    // ~Carrega primeira palavra para ser head -> data
    fscanf(inp, "%s", buffer);
    head -> data = buffer;
    
    // ~Lendo palavras row by row e inserindo na lista
    for(int i = 0; i < nPalavras - 1; i++) {
        fscanf(inp, "%s", buffer);
        insert(head, buffer);
    }
    fclose(inp);
    
    cout << "Arquivo carregado gerou a lista com head: " << head <<"\nvalores: ";
    printDoubleLinkedList(head);
    return head;
}
