#include "Hash.h"
#include <iostream>
int HashFunction(int key, int size, int p)
{
	return (p + key) % size;
}
int HashFunction_Multi(int key, int size, int p)
{
	const int A = 2654435769;

	return (key * A) % size;
}
int HashFunction_Modul(int key, int size)
{
	return key % size;
}
//-------------------------------
int Next_hash(int hash, int size, int p)
{
	return (hash + 5 * p + 3 * p * p) % size;
}
//-------------------------------
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));
}
//-------------------------------
Object::Object(int size, int(*getkey)(void*))
{
	N = 0;
	this->size = size;
	this->getKey = getkey;
	this->data = new void* [size];
	for (int i = 0; i < size; ++i)
		data[i] = NULL;
}
//-------------------------------
bool Object::insert(void* d)
{
	bool b = false;
	if (N != size)
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0);
			i != size && !b;  j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d;
				N++;
				b = true;
			}
	return b;
}

bool Object::insert_Multi(void* d, int& probes)
{
	probes = 0;
	int t = getKey(d);
	int j = HashFunction_Multi(t, size, 0);

	if (data[j] == NULL || data[j] == DEL)
	{
		data[j] = d;
		N++;
		return true;
	}
	else
	{
		probes = 1;
		return false;
	}
}

bool Object::insert_Modul(void* d, int& probes) {
	probes = 0;
	int t = getKey(d);
	int j = HashFunction_Modul(t, size);

	if (data[j] == NULL || data[j] == DEL) {
		data[j] = d;
		N++;
		return true;
	}
	else {
		probes = 1;
		return false;
	}
}
//-------------------------------
int Object::searchInd(int key)
{
	int t = -1;
	bool b = false;
	if (N != 0)
		for (int i = 0, j = HashFunction(key, size, 0); data[j] != NULL && i != size && !b; j = HashFunction(key, size, ++i))
			if (data[j] != DEL)

				if (getKey(data[j]) == key)
				{
					t = j; b = true;
				}
	return t;
}
//-------------------------------
void* Object::search(int key)
{
	int t = searchInd(key);
	return(t >= 0) ? (data[t]) : (NULL);
}
//-------------------------------
void* Object::deleteByKey(int key)
{
	int i = searchInd(key);
	void* t = data[i];
	if (t != NULL)
	{
		data[i] = DEL;
		N--;
	}
	return t;
}
//-------------------------------
bool Object::deleteByValue(void* d)
{
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------

void Object::scan(void(*f)(void*))
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << " Ёлемент" << i;
		if ((this->data)[i] == NULL)
			std::cout << "  пусто" << std::endl;
		else
			if ((this->data)[i] == DEL)
				std::cout << "  удален" << std::endl;
			else
				f((this->data)[i]);
	}
}
