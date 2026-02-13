#include "Heap.h"
#include <iostream>
using namespace std;
heap::CMP cmpAAA(void* a1, void* a2)
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
    heap::CMP
        rc = heap::EQUAL;
    if (A1->x > A2->x)
        rc = heap::GREAT;
    else
        if (A2->x > A1->x)
            rc = heap::LESS;
    return rc;
#undef A2
#undef A1
}

int main()
{
    setlocale(LC_ALL, "rus");
    int k, choice, index;
    heap::Heap h1 = heap::create(30, cmpAAA);
    heap::Heap h2 = heap::create(30, cmpAAA); // Создаем вторую кучу для объединения

    for (;;)
    {
        cout << "1 - вывод кучи 1 на экран" << endl;
        cout << "2 - добавить элемент в кучу 1" << endl;
        cout << "3 - удалить минимальный элемент из кучи 1" << endl;
        cout << "4 - удалить i-ый элемент из кучи 1" << endl;
        cout << "5 - вывод кучи 2 на экран" << endl;
        cout << "6 - добавить элемент в кучу 2" << endl;
        cout << "7 - объединить кучи" << endl;
        cout << "0 - выход" << endl;
        cout << "сделайте выбор" << endl;  cin >> choice;
        switch (choice)
        {
        case 0:  exit(0);
        case 1:  h1.scan(0);
            break;
        case 2: {
            AAA* a = new AAA;
            cout << "введите ключ" << endl;  cin >> k;
            a->x = k;
            h1.insert(a);
        }
              break;
        case 3:    h1.extractMin();
            break;
        case 4:
            cout << "введите индекс элемента для удаления: ";
            cin >> index;
            h1.extractI(index);
            break;
        case 5:  h2.scan(0);
            break;
        case 6: {
            AAA* a = new AAA;
            cout << "введите ключ для кучи 2" << endl;  cin >> k;
            a->x = k;
            h2.insert(a);
        }
              break;
        case 7: {
            heap::Heap h3 = heap::unionHeap(h1, h2);
            cout << "Результат объединения куч (куча 3):" << endl;
            h3.scan(0);
            cout << "Куча 1 после объединения:" << endl;
            h1.scan(0);
            cout << "Куча 2 после объединения:" << endl;
            h2.scan(0);
        }
              break;
        default:  cout << endl << "Введена неверная команда!" << endl;
        }
    } return 0;
}