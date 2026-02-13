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

void deletFirst() 
{
    if (isNull())
        cout << "Очередь пуста" << endl;
    else 
    {
        Item* p = head;
        head = head->next;
        delete p;
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
        bool inserted = false;

        while (current != NULL) 
        {
            if (x > current->data)
            {
                if (prev == NULL) 
                {
                    p->next = head;
                    head = p;
                }
                else 
                {
                    prev->next = p;
                    p->next = current;
                }
                inserted = true;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!inserted) 
        {
            tail->next = p;
            tail = p;
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
    while (!isNull()) deletFirst();
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
        cout << "3 - извлечь элемент с начала" << endl;
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
            deletFirst();
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