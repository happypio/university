#include <iostream>
using namespace std;

constexpr int on_stack_max = sizeof(string);

template <typename T>
struct On_heap
{
    On_heap() : p(new T) {} //constructor
    ~On_heap() { delete p; } //destructor
    T &operator*() { return *p; }
    T *operator->() { return p; }
    //copy blockade
    On_heap(const On_heap &) = delete;
    On_heap &operator=(const On_heap &) = delete;
    
    private:
    T *p;
};

template <typename T>
struct On_stack
{
    On_stack() {}
    T &operator*() { return x; }
    T *operator->() { return &x; }
    On_stack(const On_stack &) = delete;
    On_stack &operator=(const On_stack &) = delete;

    private:
    T x;
};

template <typename T>
struct Obj_holder
{
   using type = typename conditional<
       (sizeof(T) <= on_stack_max),
       On_stack<T>,
       On_heap<T>>::type;
};

//zad 5 part 2

constexpr int on_stack_max_arr = 128;//sizeof(string);

template <typename T>
struct On_heap_array
{
    using elemtype = typename remove_extent<T>::type;
    On_heap_array() : p(new elemtype[sizeof(T) / sizeof(elemtype)]) {} // new t[size]
    ~On_heap_array() { delete[] p; }                                   // delete[] p
    elemtype &operator*() { return *p; }
    elemtype *operator->() { return p; }

    On_heap_array(const On_heap_array &) = delete;
    On_heap_array &operator=(const On_heap_array &) = delete;
    //const elemtype &operator[](const int i) const { return p[i]; };
    elemtype &operator[](const int i) { return p[i]; };

private:
    elemtype *p;
};

template <typename T>
struct On_stack_array
{
    On_stack_array() {}
    T &operator*() { return x; }
    T *operator->() { return &x; }
    On_stack_array(const On_stack_array &) = delete;
    On_stack_array &operator=(const On_stack_array &) = delete;

private:
   T x;
};

template <typename T>
struct Arr_holder
{
    using type = typename conditional<
    (sizeof(T) <= on_stack_max_arr),
    On_stack_array<T>,
    On_heap_array<T>>::type;
};

int main()
{
    typename Obj_holder<double>::type v1;
    
    typename Arr_holder<int[50]>::type v2;
    typename Arr_holder<int[5]>::type v3;
    *v1 = 7.0;
    cout << *v1 << endl;
    v2[40] = 3;
    (*v3)[0] = 10;
    cout << v2[40] << " " << v2[41] << endl;
    cout << (*v3)[0] << endl;
    return 0;
}