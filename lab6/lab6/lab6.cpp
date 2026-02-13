#include <iostream>
#include <fstream>
using namespace std;

struct list
{
    int number;
    list* next;
};

void insert(list*&, int);
float del(list*&, int);
int IsEmpty(list*);
void printList(list*);
void menu(void);
void arifm(list*);
void toFile(list*& p);
void fromFile(list*& p);
void find(list*);

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int choice = 0;
    int value;
    menu();
    while (choice != 8)
    {
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice)
        {

        case 1:
            cout << "Введите число: ";

            while (!(cin >> value) || cin.peek() != '\n') {
                cout << "Ошибка! Введите число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            insert(first, value);
            cout << "Элемент добавлен." << endl;

            break;

        case 2:
            printList(first);
            break;


        case 3:   if (!IsEmpty(first))
        {
            cout << "Введите удаляемое число: ";
            cin >> value;
            if (del(first, value))
            {
                cout << "Удалено число " << value << endl;
                printList(first);
            }
            else
                cout << "Число не найдено!" << endl;
        }
              else
            cout << "Список пуст:(" << endl;
            break;

        case 4:   arifm(first);

        case 5: toFile(first);
            break;

        case 6: fromFile(first);
            break;

        case 7: find(first);
            break;

        default:  cout << "Неправильный выбор!" << endl;
            menu();
            break;
        }
    }
    cout << "Конец." << endl;
    return 0;
}

void menu(void)  
{
    cout << "Сделайте выбор:" << endl;
    cout << " 1 - Ввод числа" << endl;
    cout << " 2 - Вывод числа" << endl;
    cout << " 3 - Удаление числа" << endl;
    cout << " 4 - Вычисление суммы отрицательных двухзначных" << endl;
    cout << " 5 - Запись в файл" << endl;
    cout << " 6 - Вывод из файла" << endl;
    cout << " 7 - Поиск элемента" << endl;
    cout << " 8 - Выход" << endl;
}

void insert(list*& p, int value)
{
    list* newP = new list;
    if (newP != NULL)    
    {
        newP->number = value;       
        newP->next = p;
        p = newP;
    }
    else
        cout << "Операция добавления не выполнена:(" << endl;
}

float del(list*& p, int value)  
{
    list* previous, * current, * temp;
    if (value == p->number)   
    {
        temp = p;
        p = p->next;    
        delete temp;
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value) 
        {
            previous = current;
            current = current->next; 
        }
        if (current != NULL)
        {
            temp = current;     
            previous->next = current->next;     
            free(temp); 
            return value;
        }
    }
    return 0;
}
int IsEmpty(list* p)
{      
    return p == NULL;
}
void printList(list* p)  
{
    list* temp = p; 

    if (temp == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (temp != NULL) 
        {
            cout << "\t" << temp->number;
            temp = temp->next;
        }
        cout << endl;
    }
}

void arifm(list* p)  
{
    int sm = 0;
    bool found = false;
    if (p == NULL)      
        cout << "Список пуст:(" << endl;
    else
    {
        while (p != NULL) 
        {
            if (p->number >= -99 && p->number <= -10)
            {
                sm += (p->number);
                found = true; 
            }
            p = p->next;
        }
        if (found)
            cout << "Сумма отрицательных двузначных равна: " << sm << endl;
        else
            cout << "Отрицательных двузначных чисел нет в списке" << endl;
    }
}


void toFile(list*& p)
{
    list* temp = p;
    ofstream file1("text.txt");     
    if (file1.fail())         
    {
        cout << "\n Ошибка открытия файла!";
        exit(1);
    }
    while (temp)       
    {
        int nn = temp->number;     
        file1 << nn << "\n";        
        temp = temp->next;          
    }
    file1.close();      
    cout << "\n";
}

void fromFile(list*& p)
{
    char buf[10];     

    ifstream file1("text.txt");    

    if (file1.fail())           
    {
        cout << "\n Ошибка открытия файла!";
        exit(1);
    }
    while (!file1.eof())       
    {
        file1.getline(buf, 10);         
        if (strlen(buf))        
            insert(p, atoi(buf));      
        cout << "\t" << buf;
    }
    cout << "\tNULL" << endl;
    file1.close();
}

void find(list* p)      
{
    bool isFind = false;
    int element;
    cout << "Введите элемент:" << endl;
    cin >> element;
    list* find = p;
    while (find)        
    {
        if (find->number == element)        
        {
            isFind = true;
            printf("Элемент найден!\n");
            break;
        }
        find = find->next;         
    }
    if (!isFind)
        printf("Элемент не найден:(\n");
}