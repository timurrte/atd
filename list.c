#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>

// ініціалізація списку порожнім значенням
void InitializeList(List *plist) {
    *plist = NULL;
}

// повертає true якщо список пустий
int ListIsEmpty(const List *plist) {
    if (*plist == NULL) return 1;
    else return 0;
}

// повертає true якщо список повний
int ListIsFull(const List *plist) {
    Node *pt;
    int full;
    pt = (Node*) malloc(sizeof(Node));
    if (pt == NULL) full = 1;
    else full = 0;
    free(pt);
    return full;
}

// копіює item до pnode
static void CopyToNode(Item item, Node *pnode) {
    pnode->item = item;
}

// рахує кількість елементів у списку
unsigned int ListItemCount(const List *plist) {
    unsigned int count = 0;
    Node *pnode = *plist;
    while(pnode != NULL) {
        ++count;
        pnode = pnode->next;
    }
    return count;
}

// додає елемент до списку
// повертає 1 при успіху, інакше 0
int AddItem(Item item, List *plist) {
    Node *pnew;
    Node *scan = *plist;
    pnew = (Node*) malloc(sizeof(Node));
    if(pnew == NULL) return 0;
    CopyToNode(item, pnew);
    pnew->next = NULL;
    if(scan == NULL) {
        *plist = pnew;
    }
    else {
        while (scan->next != NULL) {
            scan = scan->next;
        }
        scan->next=pnew;
    }
    return 1;
}

// виконує функцію на кожному елементі списку
void Traverse(const List *plist, void (*pfun)(Item item)) {
    Node *pnode = *plist;
    while(pnode != NULL) {
        (*pfun) (pnode->item);
        pnode = pnode->next;
    }
}

// звільняє памʼять зарезервовану malloc()
// встановлює значення посилання на список у значеня NULL
void EmptyTheList(List *plist) {
    Node *psave;
    while(*plist != NULL) {
        psave = (*plist)->next;
        free(*plist);
        *plist=psave;
    }
}



// виводить в стандартний поток виводу інформацію про всі замовлення в списку
void printAll(const List *plist) {
    Node *pnode = *plist;
    while(pnode != NULL) {
        printOrder(pnode);
        pnode = pnode->next; 
    }
}


void writeToFile(const List *plist) {
    char* filename = "orders.dat";
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Не вдалося відкрити файл.\n");
        return;
    }

    Node* current = *plist;
    while (current != NULL) {
        fwrite(&(current->item), sizeof(Item), 1, file);
        current = current->next;
    }

    fclose(file);
}

void readListFromFile(List* listRef) {
    char* filename = "orders.dat";
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Не вдалося відкрити файл.\n");
        return;
    }

    // Очищення існуючого списку, якщо він існує
    Node* current = *listRef;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *listRef = NULL;

    // Читання даних з файлу та створення вузлів списку з відповідними значеннями
    Item item;
    while (fread(&item, sizeof(Item), 1, file) == 1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = NULL;

        if (*listRef == NULL) {
            *listRef = newNode;
        } else {
            Node* lastNode = *listRef;
            while (lastNode->next != NULL) {
                lastNode = lastNode->next;
            }
            lastNode->next = newNode;
        }
    }

    fclose(file);
}