#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <string.h>
struct order {
    unsigned int order_id;
    char customer_name[50];
    char order_date[20];
    char status[20];
    char order_info[50];
    int order_cost;
    int total_amount;
};

typedef struct order Item;

typedef struct node {
    Item item;
    struct node *next;
} Node;

typedef Node *List;

void addOrder(const List *plist);

//initializing list
// *plist вказує на список
// ініціалізуємо список порожніми значеннями
void InitializeList(List *plist);

// is list empty
// *plist вказує на список
// перевіряємо чи список пустий
int ListIsEmpty(const List *plist);

// is list full
// *plist вказує на список
// перевіряємо чи список повний
int ListIsFull(const List *plist);

// counting items in list
// *plist вказує на список
// рахуємо кількість елементів у списку
unsigned int ListItemCount(const List *plist);

// add item to list
// *plist вказує на список, item - елемент, який додаємо
// додаємо елемент до списку
int AddItem(Item item, List *plist);

// traverse function to each element in list
// *plist вказує на список, pfun - вказує на функцію
// застосувати функцію до кожного елементу списку
void Traverse(const List *plist, void(*pfun) (Item item));

// empty element in list
// *plist вказує на список
// видалити елементи списку
void EmptyTheList(List *plist);

// find item in list
// *plist вказує на список, id - номер замовлення для пошуку
Node * findOrder(int id,const List *plist);

// виводить в стандартний поток виводу інформацію про всі замовлення в списку
// приймає посилання на початок списку
void printAll(const List *plist);

// змінбє дані елементу списку
void editOrder(const List *plist);

int write_to_file(const List *plist);

#endif