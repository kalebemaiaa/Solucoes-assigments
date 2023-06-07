#include <iostream>
#include "auxiliar_functions.h"

using namespace std;

/*
    
*/

int main()
{
    /*
    string sNomeArquivo;
    cout << "Digite o nome do arquivo: ";
    cin >> sNomeArquivo;
    cout << endl;
    */
    Node *head = openFile("palavras_10.txt");
    
    if(head == nullptr) return 1;
    /*
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
    
    // ~Ordenando com bubble
    cout << endl;
    cout << "\tLista ordenada com bubble para deletar a palavra mais frequente\n\n";
    sortBubble(&head, comparasionC);
    printDoubleLinkedList(head);
    
    // ~Deletando a mais frequente;
    cout << endl;
    cout << "\tLista apos deletar palavra mais frequente\n\n";
    deleteMostFrequently(&head);
    printDoubleLinkedList(head);
    
    */
    // ~Merge sort
    
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
}