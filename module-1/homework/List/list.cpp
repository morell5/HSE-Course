#include "list.h"

using namespace task;

// find front | back elements
int list::find_back_element(list*& element, int counter)
{
    if (counter == 0 && element->next == nullptr)
    {
       if (element->last != nullptr)
       {
        this->back_element = element->last->value;
       }
       return counter;
    }
    if (element->next == nullptr)
    {
        this->back_element = element->value;
        return counter;
    }
    else
    {
        find_back_element(element->next, counter + 1);
    }
}

int list::find_front_element(list*& element, int counter)
{
    if (counter == 0 && element->last == nullptr)
    {
        if (element->next != nullptr) 
        {
            this->front_element = element->next->value;
        }
        return counter;
    }
    if (element->last == nullptr) 
    {
    
        this->front_element = element->value;
        return counter;
    }
    else
    {
        find_front_element(element->last, counter + 1);
    }
}

// out elements
void list::out()
{
    list* element = this;
    walk(element->last);
    for (element = this->next; element != nullptr; element = element->next)
    {
        std::cout << element->value << ' ';
    }
    std::cout << std::endl;
}

void list::walk(list* element)
{
    if (element == nullptr)
    {
        return;
    }
    walk(element->last);
    std::cout << element->value << ' ';
}

// merge sort
void list::merge(int left_1, int right_1, int left_2, int right_2, int* arr)
{
    int* sort_arr = new int[right_1 - left_1 + right_2 - left_2 + 2];
    int left = left_1;
    int right = right_2;
    for (int index = 0; left_1 <= right_1 || left_2 <= right_2; index++)
    {
        if (left_1 > right_1)
        {
            sort_arr[index] = arr[left_2];
            left_2++;
        }
        else if (left_2 > right_2)
        {
            sort_arr[index] = arr[left_1];
            left_1++;
        }
        else {
            if (arr[left_1] < arr[left_2])
            {
                sort_arr[index] = arr[left_1];
                left_1++;
            }
            else
            {
                sort_arr[index] = arr[left_2];
                left_2++;
            }
        }
    }
    for (int i = left; i <= right; i++)
    {
        arr[i] = sort_arr[i - left];
        //std::cout << arr[i] << ' ';
    }
    //std::cout << std::endl;
    delete[] sort_arr;
}

void list::merge_sort(int left, int right, int* arr)
{
    if (left == right)
    {
        return;
    }
    int middle = (left + right) / 2;
    merge_sort(left, middle, arr);
    merge_sort(middle + 1, right, arr);
    merge(left, middle, middle + 1, right, arr);
}

void list::arr_to_list(list*& element, int* arr, int index, int n)
{
    if (index == n)
    {
        return;
    }
    element = new list;
    element->value = arr[index];
    arr_to_list(element->next, arr, index + 1, n);
}

void list::copy_back(list*& element, int* arr, int& n)
{
    if (element == nullptr)
    {
        return;
    }
    copy_back(element->next, arr, n);
    arr[n] = element->value;
    n--;
}

void list::copy_front(list*& element, int* arr, int& n)
{
    if (element == nullptr)
    {
        return;
    }
    arr[n] = element->value;
    n--;
    copy_front(element->last, arr, n);
}

void list::sort()
{
    int* arr = new int[this->size_list];
    list* element = this;
    int n = this->size_list - 1;
    copy_back(element->next, arr, n);
    copy_front(element->last, arr, n);
    /*for (int i = 0; i < 6; i++)
    {
        std::cout << arr[i] << ' ';
    }
    //std::cout << std::endl;*/
    merge_sort(0, this->size_list - 1, arr);
    n = this->size_list;
    this->last = nullptr;
    arr_to_list(element->next, arr, 0, n);
    delete[] arr;
    rebuild(element);
}

// constructor
list::list()
{
    this->front_element = 0;
    this->back_element = 0;
    this->next = nullptr;
    this->last = nullptr;
    this->size_list = 0;
    this->value = 0;
}

list::list(size_t count, const int& value)
{
    list* element = this;
    this->size_list = count;
    this->front_element = value;
    this->back_element = value;
    this->next = nullptr;
    this->last = nullptr;
    this->value = 0;
    for (int i = 0; i < count; i++)
    {
        element->next = new list;
        element->next->value = value;
        element = element->next;
    }
}

// destructor
void list::destructor_clear_back(list*& element)
{
    if (element->next != nullptr)
    {
        destructor_clear_back(element->next);
        element->next = nullptr;
    }
    return;
}

void list::destructor_clear_front(list*& element)
{
    if (element->last != nullptr)
    {
        destructor_clear_front(element->last);
        element->last = nullptr;
    }
    return;
}

list::~list()
{
    this->front_element = 0;
    this->back_element = 0;
    this->size_list = 0;
    this->value = 0;
    list* element = this;
    destructor_clear_back(element);
    destructor_clear_front(element);
    this->next = nullptr;
    this->last = nullptr;
}

// equals
list& list::operator=(const list& other)
{
    this->front_element = other.front_element;
    this->back_element = other.back_element;
    this->next = other.next;
    this->last = other.last;
    this->size_list = other.size_list;
    return *this;
}

// return front element
int& list::front()
{
    return this->front_element;
}

const int& list::front() const
{
    return this->front_element;
}

// return back element
int& list::back()
{
    return this->back_element;
}

const int& list::back() const
{
    return this->back_element;
}

// check on empty
bool list::empty()
{
    if (this->next == nullptr && this->last == nullptr)
    {
        return true;
    }
    return false;
}

// rebuild
void list::rebuild(list*& element)
{
    this->next = element->next;
    this->last = element->last;
    int size_front = find_front_element(element, 0);
    int size_back = find_back_element(element, 0);
    this->size_list = size_front + size_back;
    if (this->size_list == 0)
    {
        this->back_element = -1e9;
        this->front_element = -1e9;
    }
}

// return size
size_t list::size()
{
    return this->size_list;
}

// clear list
void list::clear()
{
    this->front_element = 0;
    this->back_element = 0;
    this->size_list = 0;
    this->value = 0;
    list* element = this;
    destructor_clear_back(element);
    destructor_clear_front(element);
    this->next = nullptr;
    this->last = nullptr;
}

// push_back
void list::add_back(list*& element, int value)
{
    if (element == nullptr)
    {
        element = new list;
        element->value = value;
        return;
    }
    else {
        add_back(element->next, value);
    }
}

void list::push_back(const int& value)
{
    list* element = this;
    add_back(element, value);
    this->next = element->next;
    rebuild(element);
}

// push_front
void list::add_front(list*& element, int value)
{
    if (element == nullptr)
    {
        element = new list;
        element->value = value;
        return;
    }
    else {
        add_front(element->last, value);

    }
}

void list::push_front(const int& value)
{
    list* element = this;
    add_front(element, value);
    rebuild(element);
}

// pop_back
void list::delete_back(list*& element)
{
    if (element->next == nullptr)
    {
        if (element->last != nullptr)
        {
            element->last = element->last->last;
        }
        return;
    }
    if (element->next->next == nullptr)
    {
        element->next = nullptr;
        return;
    }
    delete_back(element->next);
}

void list::pop_back()
{
    list* element = this;
    delete_back(element);
    rebuild(element);
}

// pop_front
void list::delete_front(list*& element)
{
    if (element->last == nullptr)
    {
        if (element->next != nullptr)
        {
            element->next = element->next->next;
        }
        return;
    }
    if (element->last->last == nullptr)
    {
        element->last = nullptr;
        return;
    }
    delete_front(element->last);
}

void list::pop_front()
{
    list* element = this;
    delete_front(element);
    rebuild(element);
}

// resize
void list::resize(size_t count)
{
    this->clear();
    list* element = this;
    this->size_list = count;
    for (int i = 0; i < count; i++)
    {
        element->next = new list;
        element = element->next;
    }
}

// swap

void swap_p(list*& first, list*& second)
{
    list* third = first;
    first = second;
    second = third;

}

void swap_i(int& first, int& second)
{
    int third = first;
    first = second;
    second = third;
}

void list::swap(list& other)
{
    swap_p(other.next, this->next);
    swap_p(other.last, this->last);
    swap_i(other.size_list, this->size_list);
    swap_i(other.front_element, this->front_element);
    swap_i(other.back_element, this->back_element);
}

//delete elements value
void list::remove_next(list*& element, const int& value)
{

    if (element->next != nullptr)
    {
        if (element->next->value == value)
        {
            element->next = element->next->next;
            remove_next(element, value);
        }
        else 
        {
            remove_next(element->next, value);
        }
    }
    else
    {
        return;
    }

}

void list::remove_last(list*& element, const int& value)
{

    if (element->last != nullptr)
    {
        if (element->last->value == value)
        {
            element->last = element->last->last;
            remove_last(element, value);
        }
        else
        {
            remove_last(element->last, value);
        }
    }
    else
    {
        return;
    }

}

void list::remove(const int& value)
{
    list* element = this;
    remove_last(element, value);
    remove_next(element, value);
    rebuild(element);
}

// delete unique
void list::unique()
{
    int* arr = new int[this->size_list];
    list* element = this;
    int n = this->size_list - 1;
    copy_back(element->next, arr, n);
    copy_front(element->last, arr, n); 
    int* arr2 = new int[this->size_list];
    std :: set<int> rep;
    int ind = 0;
    for (int i = 0; i < this->size_list; i++)
    {
        if (rep.find(arr[i]) == rep.end())
        {
            arr2[ind] = arr[i];
            ind++;
        }
        rep.insert(arr[i]);
    }
    arr_to_list(element->next, arr2, 0, ind);
    rebuild(element);
    delete[] arr;
    delete[] arr2;
    /*unique_back(element->next);
    this->next = element->next;
    unique_front(element->last);
    this->last = element->last;
    if (this->last != nullptr && this->next != nullptr && this->next->value == this->last->value)
    {
        this->last = this->last->last;
    }*/
}
