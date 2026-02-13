#include<iostream>
using namespace std;

struct Item 
{
    int data;
    Item* next;
};
Item* head, * tail;

bool isNull() 
{
    return (head == NULL);
}

void deletLast() 
{
    if (isNull())
        cout << "Очередь пуста" << endl;
    else 
    {
        if (head == tail) 
        {
            delete head;
            head = tail = NULL;
        }
        else
        {
            Item* p = head;

            while (p->next != tail)
            {
                p = p->next;
            }
            delete tail;
            tail = p;
            tail->next = NULL;
        }
    }
}

void getFromHead()
{
    if (isNull())
        cout << "Очередь пуста" << endl;
    else
        cout << "Начало = " << head->data << endl;
}

void insertToQueue(int x)
{
    Item* p = new Item;
    p->data = x;
    p->next = NULL;

    if (isNull())
    {
        head = tail = p;
    }
    else
    {
        Item* current = head;
        Item* prev = NULL;
        Item* lastEqual = NULL;

        while (current != NULL && x >= current->data) 
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL)
        {
            p->next = head;
            head = p;
        }
        else
        {
            prev->next = p;
            p->next = current;
            if (current == NULL) 
            {
                tail = p;
            }
        }
    }
}

void printQueue() 
{
    if (isNull())
        cout << "Очередь пуста" << endl;
    else 
    {
        cout << "Очередь = ";
        Item* p = head;
        while (p != NULL) 
        {
            cout << p->data << " -> ";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
}

void clrQueue()
{
    while (!isNull()) deletLast();
}

int main() 
{
    setlocale(LC_CTYPE, "Russian");
    int choice = 1, z;
    head = NULL;
    tail = NULL;

    while (choice != 0) 
    {
        cout << "1 - добавить элемент" << endl;
        cout << "2 - получить элемент с начала" << endl;
        cout << "3 - извлечь элемент с конца" << endl;
        cout << "4 - вывести элементы" << endl;
        cout << "5 - очистить очередь" << endl;
        cout << "0 - выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            cout << "Введите элемент: ";
            cin >> z;
            insertToQueue(z);
            break;
        case 2:
            getFromHead();
            break;
        case 3:
            deletLast();
            printQueue();
            break;
        case 4:
            printQueue();
            break;
        case 5:
            clrQueue();
            break;
        }
    }
    return 0;
}