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

// ~Deleta por endereco
static void deleteNode(Node *lixo)
{
    // ~Supomos lixo diferente de head
    lixo->prev->next = lixo->next;
    if (lixo->next)
        lixo->next->prev = lixo->prev;
    free(lixo);
}

void deleteMostFrequently(Node **head)
{
    Node *tmp = *head;
    if (tmp == nullptr || tmp->next == nullptr)
        return;
    int maxCount, searcherCount;

    // ~Computa o numero de vezes que a primeira palavra aparece;
    for(maxCount = 1; tmp -> data == tmp->next->data; maxCount++, tmp = tmp->next);

    // ~Proxima palavra
    tmp = tmp->next;

    // ~Procurar maxima frequencia
    while (tmp->next != nullptr)
    {
        // ~Enquanto for a mesma palavra, incrementar searcher;
        for(searcherCount = 1; tmp -> data == tmp->next->data; searcherCount++, tmp = tmp->next)
            if (tmp->next == nullptr)
                break;

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
        // ~Computa frequencia da oakavra atual em searcount
        for(searcherCount = 1; tmp -> data == tmp->prev->data; searcherCount++, tmp = tmp->prev)
            if (tmp->prev == nullptr)
                break;

        // ~Palavra tem frequencia igual a maior deletada
        if (searcherCount == maxCount)
        {
            cout << "Palavra [" << tmp->data << "] deletada pois apareceu " << maxCount << " vezes na lista." << endl;
            for(int i = maxCount - 1; i > 0; i--){
                deleteNode(tmp->next);
            }

            // ~Se o no for a head
            if(!tmp->prev){
                tmp = tmp->next;
                *head = tmp;
                free(tmp -> prev);
                tmp->prev = nullptr;
                return;
            }
            tmp = tmp -> prev;
            deleteNode(tmp -> next);
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
        insertEnd(head, buffer);
    }
    fclose(inp);

    cout << "Arquivo carregado gerou a lista com head: " << head << "\nvalores: ";
    printDoubleLinkedList(head);
    return head;
}

int main() {
    string sNomeArquivo;
    cout << "Digite o nome do arquivo: ";
    cin >> sNomeArquivo;
    cout << endl;

    Node *head = openFile(sNomeArquivo);

    if(head == nullptr) 
        return 1;
    
    deleteMostFrequently(&head);
    printDoubleLinkedList(head);
}