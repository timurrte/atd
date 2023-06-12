#include <stdio.h>
#include <stdlib.h>
#include "list.h"



// пошук замовлення по id в списку
Node * findOrder(int id,const List *plist) {
    Node *search = *plist;
    Item *tmp = &search->item;
    while(tmp != NULL) {
        if (tmp->order_id == id) {
            return search;
        }
        search = search->next;
    }
    return NULL;
}

// відображення елементів списку
// повертає 1 при успіху, інакше 0
int showOrders(List *plist) {
return 0;
}

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

// виводить в стандартний поток виводу інформацію про замовлення
// приймає посилання на елемент типу Item
void printOrder(const Item *pitem) {
    printf("Всі замовлення\nНомер замовлення: %d\nІмʼя замовника: %sДата замовлення: %s\nДані про замовлення: %sСтатус замовлення: %s\nСума замовлення: %d\nКількість товару: %d\n",
    pitem->order_id, pitem->customer_name, pitem->order_date,pitem->order_info, pitem->status, pitem->order_cost, pitem->total_amount );
}

// виводить в стандартний поток виводу інформацію про всі замовлення в списку
void printAll(const List *plist) {
    Node *pnode = *plist;
    while(pnode != NULL) {
        printOrder(&pnode->item);
        pnode = pnode->next;
    }
}

// операція додавання замовлення до списку
// повертає 1 при успіху, інакше 0
void addOrder(const List *plist) {
    Item tmp;
    fflush(stdin);
    printf("Введіть імʼя замовника: ");
    fgets(tmp.customer_name, 50, stdin);
    printf("Введіть інформацію про замовлення:");
    fgets(tmp.order_info, 50, stdin);
    printf("Сума замовлення:");
    scanf("%d", &tmp.order_cost);
    printf("Кількість товару:");
    scanf("%d", &tmp.total_amount);
    tmp.order_id = ListItemCount(plist) + 1;
    printf("\nрандом%dрандом\n", tmp.order_id);
    printOrder(&tmp);
    AddItem(tmp, plist);
}