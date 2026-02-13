#include <iostream>
#include <fstream>
#include <unordered_map>
#include "myStack.h"
using namespace std;

void push(char x, Stack*& myStk)   
{
	Stack* e = new Stack;    
	e->data = x;             
	e->next = myStk;         
	myStk = e;              
}

char pop(Stack*& myStk)  
{
	if (myStk == NULL)
	{
		cout << "Стек пуст!" << endl;
		return -1;              
	}
	else
	{
		Stack* e = myStk;      
		char x = myStk->data;   
		if (myStk)
			myStk = myStk->next;   
		delete e;
		return x;
	}
}
void toFile(Stack*& myStk) 
{
	Stack* e = myStk;
	Stack buf;
	ofstream frm("mStack.dat");
	if (frm.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	while (e)
	{
		buf = *e;
		frm.write((char*)&buf, sizeof(Stack));
		e = e->next;
	}
	frm.close();
	cout << "Стек записан в файл mStack.dat\n";
}

void fromFile(Stack*& myStk)      
{
	Stack buf, * p = nullptr, * e = nullptr;
	ifstream frm("mStack.dat");
	if (frm.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	frm.seekg(0);
	frm.read((char*)&buf, sizeof(Stack));
	while (!frm.eof())
	{
		push(buf.data, e);
		frm.read((char*)&buf, sizeof(Stack));
	}
	frm.close();
	while (e != NULL)
	{
		buf.data = pop(e);
		push(buf.data, p);
		myStk = p;
	}
	cout << "\nСтек считан из файла mStack.dat\n\n";
}
void show(Stack*& myStk)
{
	Stack* e = myStk;
	if (e == NULL)
		cout << "Стек пуст!" << endl;
	while (e != NULL)
		cout << pop(e) << " ";
	cout << endl;
}

void clear(Stack*& myStk)
{
	while (myStk != NULL)
	{
		pop(myStk);
	}
	cout << "Стек очищен.\n";
}

void countDuplicates(Stack*& myStk)
{
	Stack* e = myStk;
	bool found = false;

	while (e != NULL)
	{
		char currentData = e->data;
		if (currentData == ' ' || currentData == '\0') {
			e = e->next;
			continue;
		}

		int count = 0;
		Stack* inner = myStk;

		while (inner != NULL)
		{
			if (inner->data == currentData)
			{
				count++;
			}
			inner = inner->next;
		}

		if (count >= 2)
		{
			cout << "Элемент '" << currentData << "' повторяется " << count << " раз.\n";
			found = true;
		}

		e = e->next;
		Stack* check = myStk;
		while (check != NULL)
		{
			if (check->data == currentData)
			{
				check->data = '\0'; 
			}
			check = check->next;
		}
	}

	if (!found)
	{
		cout << "Повторяющихся элементов нет.\n";
	}
}
