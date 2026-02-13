#include "Hash_Chain.h"
#include <iostream>
namespace hashTC
{
	Object create(int size, int(*f)(void*))
	{
		return *(new Object(size, f));
	}

	int Object::hashFunction(void* data)
	{
		int haf = 231;
		return ((FunKey(data) ^ haf) % size);
	};

	bool Object::insert(void* data)
	{
		return (Hash[hashFunction(data)].insert(data));
	};

	bool Object::deleteByData(void* data)
	{
		return (Hash[hashFunction(data)].deleteByData(data));
	};

	listx::Element* Object::search(void* data)
	{
		return Hash[hashFunction(data)].search(data);
	};

	void Object::Scan()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "ячейка " << i << ": ";
			Hash[i].scan();  // «десь будет вызов, который теперь тоже показывает номера
			std::cout << '\n';
		}
	}

}
