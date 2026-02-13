#include "Hash.h"
#include <iostream>
using namespace std;
struct AAA
{
	int key;
	char* mas;
	AAA(int k, char* z)
	{
		key = k;  mas = z;
	} AAA() {}
};
//-------------------------------
int key(void* d)
{
	AAA* f = (AAA*)d;
	return f->key;
}
//-------------------------------
void AAA_print(void* d)
{
	cout << " ключ " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}
//-------------------------------
int main()
{
	setlocale(LC_ALL, "rus");
	int siz = 10, choice, k;
	int k_2;
	int b = 0, b_2 = 0;
	cout << "Введите размер хеш-таблицы" << endl;
	cin >> siz;
	Object H = create(siz, key);
	for (;;)
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "5 - функции мультипликативного и модульного хеширования. Сравнить количество коллизий при введении одинаковых ключей." << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl;   cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 1: H.scan(AAA_print);  break;
		case 2: {
			AAA* a = new AAA;
			char* str = new char[20];
			cout << "введите ключ" << endl;
			cin >> k;
			a->key = k;
			cout << "введите строку" << endl;
			cin >> str;
			a->mas = str;
			if (H.N == H.size)
				cout << "Таблица заполнена" << endl;
			else
				H.insert(a);
		} break;
		case 3: {
			cout << "введите ключ для удаления" << endl;
			cin >> k;
			H.deleteByKey(k);
		}  break;
		case 4: {
			cout << "введите ключ для поиска" << endl;
			cin >> k;
			if (H.search(k) == NULL)
				cout << "Элемент не найден" << endl;
			else
				AAA_print(H.search(k));
		}  break;
		case 5:
		{
			Object tableMulti = create(10, key);
			Object tableModul = create(10, key);

			int collisionsMulti = 0;
			int collisionsModul = 0;
			int probesMulti = 0;
			int probesModul = 0;

			cout << "Введите ключ для теста коллизий: ";
			cin >> k_2;
			cout << "Введите строку: ";
			char* str_2 = new char[20];
			cin >> str_2;

			for (int i = 0; i < 5; ++i)
			{
				AAA* z = new AAA(k_2, str_2);

				int probes = 0;
				tableMulti.insert_Multi(z, probes);
				probesMulti += probes;
				if (probes > 0) collisionsMulti++;

				probes = 0;
				tableModul.insert_Modul(z, probes);
				probesModul += probes;
				if (probes > 0) collisionsModul++;
			}

			cout << "Мультипликативное хеширование:\n";
			cout << "Коллизии: " << collisionsMulti << "\n";
			cout << "Всего проб: " << probesMulti << "\n";

			cout << "Модульное хеширование:\n";
			cout << "Коллизии: " << collisionsModul << "\n";
			cout << "Всего проб: " << probesModul << "\n";

			break;
		}
		}
	}
	return 0;
}

