#include <iostream>
#include <fstream>
using namespace std;

const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address* next;
    Address* prev;
};

// Функция для отображения меню
int menu(void)
{
    char s[80]; int c;
    cout << endl;
    cout << "1. Ввод имени" << endl;
    cout << "2. Удаление имени" << endl;
    cout << "3. Вывод на экран" << endl;
    cout << "4. Поиск" << endl;
    cout << "5. Выход" << endl;
    cout << "6. Ввод списка L" << endl; 
    cout << "7. Добавить список L в начало" << endl;
   
    cout << endl;
    do
    {
        cout << "Ваш выбор: ";
        cin.sync();
        gets_s(s);
        cout << endl;
        c = atoi(s);
    } while (c < 0 || c > 7); // Увеличили диапазон меню
    return c;
}

// Функция для добавления элемента в конец списка
void insert(Address* e, Address** phead, Address** plast)
{
    Address* p = *plast;
    if (*plast == NULL)
    {
        e->next = NULL;
        e->prev = NULL;
        *plast = e;
        *phead = e;
        return;
    }
    else
    {
        p->next = e;
        e->next = NULL;
        e->prev = p;
        *plast = e;
    }
}

// Функция для создания нового элемента
Address* setElement()
{
    Address* temp = new Address();
    if (!temp)
    {
        cerr << "Ошибка выделения памяти" << endl;
        return NULL;
    }
    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// Функция для вывода списка на экран
void outputList(Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << "" << endl;
}

// Функция для поиска элемента в списке
void find(char name[NAME_SIZE], Address** phead)
{
    Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
        cout << t->name << ' ' << t->city << endl;
}

// Функция для удаления элемента по имени
void delet(char name[NAME_SIZE], Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
    {
        if (*phead == t)
        {
            *phead = t->next;
            if (*phead)
                (*phead)->prev = NULL;
            else
                *plast = NULL;
        }
        else
        {
            t->prev->next = t->next;
            if (t != *plast)
                t->next->prev = t->prev;
            else
                *plast = t->prev;
        }
        delete t;
        cout << "Элемент удален" << endl;
    }
}

void addLBegin(Address** phead, Address** plast, Address* Lhead, Address* Llast)
{

    Address* t = Lhead;
    while (t)
    {
        Address* newElement = new Address();

        strcpy_s(newElement->name, NAME_SIZE, t->name);
        strcpy_s(newElement->city, CITY_SIZE, t->city);

        if (*phead == NULL)
        {
            newElement->next = NULL;
            newElement->prev = NULL;
            *phead = newElement;
            *plast = newElement;
        }
        else
        {
            newElement->next = *phead;
            (*phead)->prev = newElement;
            newElement->prev = NULL;
            *phead = newElement;
        }

        t = t->next;
    }
}

void inputListL(Address** Lhead, Address** Llast)
{
    int n;
    cout << "Введите количество элементов списка L: ";
    cin >> n;
    cin.ignore(); 

    for (int i = 0; i < n; ++i)
    {
        Address* newElement = setElement();  
        if (*Lhead == NULL)  
        {
            *Lhead = newElement;
            *Llast = newElement;
        }
        else 
        {
            (*Llast)->next = newElement;
            newElement->prev = *Llast;
            *Llast = newElement;
        }
    }
}

int main(void)
{
    Address* head = NULL;
    Address* last = NULL;
    Address* Lhead = NULL;
    Address* Llast = NULL;
    setlocale(LC_ALL, "rus");

    while (true)
    {
        switch (menu())
        {
        case 1:
            insert(setElement(), &head, &last);
            break;
        case 2: {
            char dname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(dname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            delet(dname, &head, &last);
        }
              break;
        case 3:
            outputList(&head, &last);
            break;
        case 4: {
            char fname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(fname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            find(fname, &head);
        }
              break;
        case 5:
            exit(0);
        case 6: {
            inputListL(&Lhead, &Llast); 
        }
              break;
        case 7: {
            addLBegin(&head, &last, Lhead, Llast);
        }
              break;
        default:
            exit(1);
        }
    }
    return 0;
}