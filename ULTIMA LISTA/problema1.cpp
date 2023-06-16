#include <iostream>

using namespace std;

typedef struct reg{
    int iData;
    struct reg *next;
} t_node;

t_node *createNode(int value){
    t_node *newNode = new t_node;
    newNode -> next = nullptr;
    newNode -> iData = value;
    return newNode;
}

void insert(t_node *head, int value){
    if(!head) return;
    t_node *tmp;
    for(tmp = head; tmp -> next != nullptr; tmp = tmp -> next);
    tmp -> next = createNode(value);
}

void printList(t_node *head){
    if(!head){
        cout << endl;
        return;
    }
    cout << head -> iData << " ";
    printList(head -> next);
}

static int sortD(t_node *h1, t_node *h2){
    return h2 -> iData - h1 -> iData;
}

static int sortC(t_node *h1, t_node *h2){
    return h1 -> iData - h2 -> iData;
}

bool verifyListOrder(t_node *head, string strComp) {
    if(!head) return true;
    if(strComp != "decrescente" && strComp != "crescente"){
        cout << "String passada [" << strComp << "] é inválida como forma de comparação.\n\t-> Insira crescente ou decrescente <-" << endl;
        return false;
    }
    int (*compare)(t_node*, t_node*) = (strComp == "decrescente") ? sortD : sortC;
    
    for(t_node *tmp = head; tmp -> next != nullptr; tmp = tmp -> next)
        if(compare(tmp, tmp->next) > 0) 
            return false;
    return true;
}

int main()
{
    t_node *head = createNode(10);
    insert(head, 12);
    insert(head, 15);
    insert(head, 18);
    insert(head, 23);
    printList(head);
    cout << "Esta ordenada como crescente? " << verifyListOrder(head, "crescente") << endl;
    cout << "Esta ordenada como decrescente? " << verifyListOrder(head, "decrescente") << endl;
    cout << endl;

    t_node *head2 = createNode(15);
    insert(head2, 12);
    insert(head2, 10);
    insert(head2, -12);
    insert(head2, -23);
    printList(head2);
    cout << "Esta ordenada como crescente? " << verifyListOrder(head2, "crescente") << endl;
    cout << "Esta ordenada como decrescente? " << verifyListOrder(head2, "decrescente") << endl;
    cout << endl;
    
    t_node *head3 = createNode(15);
    insert(head3, 12);
    insert(head3, 13);
    insert(head3, -12);
    printList(head3);
    cout << "Esta ordenada como crescente? " << verifyListOrder(head3, "crescente") << endl;
    cout << "Esta ordenada como decrescente? " << verifyListOrder(head3, "decrescente") << endl;
    
    cout << endl << "Testando passar um parametro diferente de crescent ou decrescente para a função:\n\n";
    verifyListOrder(head, "teste");
    return 0;
}

