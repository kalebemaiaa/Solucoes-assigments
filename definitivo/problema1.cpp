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
bool is_valid(string str)
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
    if (!is_valid(palavra))
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

    if(!(*head)) return;

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

int main(){
    string teste_1 = string("BABA");
    string teste_2 = string("TURATURA");
    string teste_3 = string("TURATURAT");
    string teste_4 = string("A");
    string teste_5 = string("CHORA");
    cout << "\tProblema 1\n\n";
    // ~item a
    cout << "Palavra `BABA` em is_valid: " << is_valid(teste_1) << endl;
    cout << "Palavra `TURATURA` em is_valid: " << is_valid(teste_2) << endl;
    cout << "Palavra `TURATURAT` em is_valid: " << is_valid(teste_3) << endl;
    cout << "Palavra `A` em is_valid: " << is_valid(teste_4) << endl;
    cout << "Palavra `CHORA` em is_valid: " << is_valid(teste_5) << endl;

    cout << endl;
    // ~item b
    cout << "Inserindo algumas palavras, temos:\t";
    Node *head = (Node *)malloc(sizeof(Node));
    head -> prev = nullptr;
    head -> next = nullptr;
    head -> data = string("TURA");
    insertEnd(head, "BABA");
    insertEnd(head, "SARATURY");
    printDoubleLinkedList(head);

    cout << endl;
    // ~item c
    cout << "Procurando `BABA`: " << findNode(head, "BABA") << endl;
    cout << "Procurando `BESTA`: " << findNode(head, "BESTA") << endl;

    cout << endl;
    // ~item d
    printDoubleLinkedList(head);
    cout << "Deletando `BABA`, nova lista:\t";
    deleta(&head, "BABA");
    printDoubleLinkedList(head);
    cout << "Deletando `TURA`, nova lista:\t";
    deleta(&head, "TURA");
    printDoubleLinkedList(head);

    //print ja foi usada nos itens anteriores.

    cout << endl;
    // ~item f
    cout << "Comparacao entre `BABA` e `ABAB`: "<< comparasion("BABA", "ABAB") << endl;
    cout << "Comparacao entre `BABA` e `BABA`: "<< comparasion("BABA", "BABA") << endl;
    cout << "Comparacao entre `TURA` e `ABAB`: "<< comparasion("TURA", "ABAB") << endl;
    cout << "Comparacao entre `ABA` e `TURAT`: "<< comparasion("ABA", "TURAT") << endl;
}