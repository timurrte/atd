#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void menu(const List *plist);
void wait_m(void);

List orders;

int main(void) {
    // ініціалізуємо список порожнім значенням
    InitializeList(&orders);
    
    // перевіряємо чи було виділено памʼять
    if (ListIsFull(&orders)) {
        fprintf(stderr, "Немає вільної памʼяті\n");
        exit(1);
    }

    // нескінечний цикл, який виводить меню користувача
    while(1 == 1) {
        menu(&orders);
        wait_m();
    }
}

// функція для вибору користувачем операцій над списком
void menu(const List *plist) {
    printf("Оберіть дію:\n1)Додати замовлення\n2)Редагувати замовлення\nЗ)Знайти замовлення\n4)Всі замовлення\n5)Зберегти список на диску\n6)Зчитати список з диску\n7)Видалити всі елементи списку\n");
    int number;
    fflush(stdin);
    scanf("%d", &number);
    switch (number){
    case 1:
        addOrder(plist);
        break;
    case 2:
        editStatus(plist);
        break;
    case 3:
        puts("\nВкажіть номер замовлення, яке потрібно знайти:");
        int id;
        scanf("%d", &id);
        Node* search = findOrder(id, plist);
        printOrder(search);
        break;
    
    case 4:
        printAll(plist);
        break;
    case 5:
        writeToFile(plist);
        break;
    case 6:
        readListFromFile(plist);
        break;
    case 7:
        printf("Дійсно хочете видалити всі елементи списку? (y/N): ");
        
        char answer;
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            EmptyTheList(plist);
            printf("Успішно видалено список.\n");
            return;
        } else {
            printf("Нічого не робимо.\n");
            
        }
    default:
        exit(1);
    }
    return;
}

// чекаємо на дію користувача
void wait_m() {
    char ch;
    printf("\nPress any button to proceed....\n");
    while(getchar() != '\n');
    scanf("%c", &ch);
    system("clear");
}