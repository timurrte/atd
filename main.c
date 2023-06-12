#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void menu(const List *plist);
void wait_m(void);

List orders;

int main(void) {
    // ініціалізуємо список порожнім значенням
    InitializeList(&orders);
    
    if (ListIsFull(&orders)) {
        fprintf(stderr, "Немає вільної памʼяті\n");
        exit(1);
    }
    // нескінечний цикл, який виводить меню
    while(1 == 1) {
        menu(&orders);
        wait_m();
    }
}

void menu(const List *plist) {
    printf("Оберіть дію:\n1)Додати замовлення\n2)Редагувати замовлення\nЗ)Знайти замовлення\n4)Всі замовлення\n");
    int number;
    fflush(stdin);
    scanf("%d", &number);
    switch (number){
    case 1:
        addOrder(plist);

        break;
    case 2:
        //editOrder(plist);
        break;
    case 3:
        puts("\nВкажіть номер замовлення, яке потрібно знайти:");
        int id;
        scanf("%d", &id);
        findOrder(id, plist);
        break;
    
    case 4:
        printAll(plist);
        break;
    default:
        exit(1);
    }
    return;
}



void editOrder(const List *plist) {
//todo
}



void wait_m() {
    printf("Press any button to proceed....");
    while(getchar() == "\n");
    scanf("%c");
    system("clear");
}