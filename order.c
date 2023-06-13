#include <stdio.h>
#include "list.h"

// модифікує статус замовлення
// приймає посилання на список List
void editStatus(List *plist) {
    printf("\nВведіть номер замовлення, статус якого потрібно змінити:\n");
    int orderId;
    scanf("%d", &orderId);

    Node *search = findOrder(orderId, plist);
    if (search == NULL) {
        printf("Замовлення з номером %d не знайдено!\n", orderId);
        return;
    }

    Item *order = &(search->item);

    printf("Оберіть новий статус замовлення:\n");
    printf("1) В очікуванні\n");
    printf("2) Обробляємо\n");
    printf("3) Доставка\n");
    printf("4) Доставлено\n");

    int statusChoice;
    scanf("%d", &statusChoice);

    switch (statusChoice) {
        case 1:
           strncpy(order->status, "В очікуванні", 30);
            break;
        case 2:
            strncpy(order->status, "Обробляємо", 30);
            break;
        case 3:
            strncpy(order->status, "Доставка", 30);
            break;
        case 4:
            strncpy(order->status, "Доставлено", 30);
            break;
        default:
            printf("Некоректний вибір статусу!\n");
            return;
    }

    printf("Статус замовлення з номером %d успішно змінено на \"%s\".\n", orderId, order->status);
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
    tmp.order_date = time(NULL);
    strncpy(tmp.status, "В очікуванні", 30);
    printOrder(&tmp);
    AddItem(tmp, plist);
}

// пошук замовлення по id в списку
Node* findOrder(int id, const List* plist) {
    Node* current = *plist;
    while (current != NULL) {
        if (current->item.order_id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// виводить в стандартний поток виводу інформацію про замовлення
// приймає посилання на елемент типу Item
void printOrder(Node *pnode) {
    Item* pitem = &pnode->item;
    printf("\nНомер замовлення: %d\nІмʼя замовника: %sДані про замовлення: %sСтатус замовлення: %s\nСума замовлення: %d\nКількість товару: %d\n\n",
    pitem->order_id, pitem->customer_name,pitem->order_info, pitem->status, pitem->order_cost, pitem->total_amount );
    printf("Дата замовлення: ");
    time_t t = pitem->order_date;
    struct tm tm = *localtime(&t);

    printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}