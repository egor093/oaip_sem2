#pragma once
struct AAA
{
    int x;
    void print();
};
namespace heap
{
    enum CMP
    {
        LESS = -1, EQUAL = 0, GREAT = 1
    };
    struct Heap
    {
        int size;
        int maxSize;
        void** storage;          // данные
        CMP(*compare)(void*, void*);
        Heap(int maxsize, CMP(*f)(void*, void*))
        {
            size = 0;
            storage = new void* [maxSize = maxsize];
            compare = f;
        };
        ~Heap() {
            delete[] storage;
        }
        int left(int ix);
        int right(int ix);
        int parent(int ix);
        bool isFull() const;
        bool isEmpty() const;
        bool isLess(void* x1, void* x2) const;
        bool isGreat(void* x1, void* x2) const;
        void swap(int i, int j);
        void heapify(int ix);
        void buildHeap();
        void insert(void* x);
        void* extractMin();
        void* extractI(int i);
        void scan(int i) const;
        void merge(Heap& other);
    };
    Heap create(int maxsize, CMP(*f)(void*, void*));
    Heap unionHeap(Heap& h1, Heap& h2);
};