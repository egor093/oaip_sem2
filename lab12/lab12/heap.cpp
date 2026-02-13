#include "Heap.h"
#include <iostream>
#include <iomanip>

void AAA::print()
{
    std::cout << x;
}
namespace heap
{
    bool Heap::isFull() const
    {
        return (size >= maxSize);
    }

    bool Heap::isEmpty() const
    {
        return (size <= 0);
    }

    bool Heap::isLess(void* x1, void* x2) const
    {
        return compare(x1, x2) == LESS;
    }

    bool Heap::isGreat(void* x1, void* x2) const
    {
        return compare(x1, x2) == GREAT;
    }

    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f));
    }
    int Heap::left(int ix)
    {
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);
    }
    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2);
    }
    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;
    }
    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];
        storage[i] = storage[j];
        storage[j] = buf;
    }
    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;
        if (l > 0)
        {
            if (isGreat(storage[l], storage[ix])) irl = l;
            if (r > 0 && isGreat(storage[r], storage[irl]))  irl = r;
            if (irl != ix)
            {
                swap(ix, irl);
                heapify(irl);
            }
        }
    }
    void Heap::insert(void* x)
    {
        int i;
        if (!isFull())
        {
            storage[i = ++size - 1] = x;
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);
                i = parent(i);
            }
        }
    }

    void* Heap::extractMin() {
        void* rc = nullptr;
        if (!isEmpty()) {
            int min_index = 0;
            for (int i = 1; i < size; ++i) {
                if (isLess(storage[i], storage[min_index])) {
                    min_index = i;
                }
            }
            rc = storage[min_index];
            storage[min_index] = storage[size - 1];
            size--;
            buildHeap();
        }
        return rc;
    }

    void Heap::buildHeap() {
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }

    void* Heap::extractI(int i) {
        void* rc = nullptr;
        if (i >= 0 && i < size) {
            rc = storage[i];
            storage[i] = storage[size - 1];
            size--;
            buildHeap();
        }
        return rc;
    }

    void Heap::scan(int i) const     //Вывод значений элементов на экран
    {
        int probel = 20;
        std::cout << '\n';
        if (size == 0)
            std::cout << "Куча пуста";
        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();
            if (u == y)
            {
                std::cout << '\n';
                if (y == 0)
                    y = 2;
                else
                    y += y * 2;
            }
            probel /= 2;
        }
        std::cout << '\n';
    }


    void Heap::merge(Heap& other) {
        for (int i = 0; i < other.size; ++i) {
            storage[size + i] = other.storage[i];
        }
        size += other.size;
        buildHeap();
        other.size = 0;
    }

    Heap unionHeap(Heap& h1, Heap& h2) {
        Heap result(h1.size + h2.size, h1.compare);
        result.merge(h1);
        result.merge(h2);
        return result;
    }
}