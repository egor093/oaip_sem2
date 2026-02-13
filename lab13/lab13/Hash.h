#pragma once
#define HASHDEL (void*) -1
struct Object
{
	void** data;
	Object(int, int(*)(void*));
	int size;  int N;
	int(*getKey)(void*);
	bool insert(void*);
	int searchInd(int key);
	void* search(int key);
	void* deleteByKey(int key);
	bool deleteByValue(void*);
	void scan(void(*f)(void*));
	bool insert_Multi(void* d, int& b_);
	bool insert_Modul(void* d, int& b_);

};
static void* DEL = (void*)HASHDEL;
Object create(int size, int(*getkey)(void*));
#undef HASHDEL
