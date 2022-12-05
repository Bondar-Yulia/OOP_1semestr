#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <iostream>

template <class T>
class ArrayList
{
private:
    int length;
    int frontPos;
    int backPos;
    T array[100000];

public:
    ArrayList();

    void push_back(T);

    void push_front(T);

    bool is_empty();

    void clear();

    T pop_back();

    T pop_front();

    void print();

    int get_length(){ return length; }

    void insertion_sort(int, int);

    void quick_sort(int, int);
};

template <class T>
class LinkedList
{
private:
    class ListNode {
    public:
        T value;
        ListNode *next = nullptr;
        ListNode *prev = nullptr;
    } *front, *back;

    int length;

    ListNode *merge(ListNode *first, ListNode *second);

    ListNode *split(ListNode *front);

    ListNode *merge_sort(ListNode *front);

public:
    LinkedList();

    void push_back(T);

    void push_front(T);

    void print();

    bool is_empty();

    T pop_back();

    T pop_front();

    void clear();

    int get_length(){ return length; }

    ListNode * get_front() const { return front; }

    void merge_sort();
};

template<typename T>
ArrayList<T>::ArrayList() {
    length = 0;
    frontPos = 50000;
    backPos = 50001;
}

template<typename T>
void ArrayList<T>::push_back(T n)
{
    if (length == 100000 || backPos == 99999)
        return;
    array[backPos] = n;
    length++;
    backPos++;
}

template<typename T>
void ArrayList<T>::push_front(T n)
{
    if (length == 100000 || backPos == 99999)
        return;
    array[frontPos] = n;
    length++;
    frontPos--;
}

template<typename T>
bool ArrayList<T>::is_empty()
{
    if (length == 0)
        return true;
    else
        return false;
}

template<typename T>
void ArrayList<T>::clear()
{
    length = 0;
    frontPos = 50000;
    backPos = 50001;
}

template<typename T>
T ArrayList<T>::pop_back()
{
    if (is_empty())
        return 0;
    length--;
    backPos--;
    T res = array[backPos];
    if (length == 0)
    {
        frontPos = 50000;
        backPos = 50001;
    }
    return res;
}

template<typename T>
T ArrayList<T>::pop_front()
{
    if (is_empty())
        return 0;
    length--;
    frontPos++;
    T res = array[frontPos];
    if (is_empty())
    {
        frontPos = 50000;
        backPos = 50001;
    }
    return res;
}

template<typename T>
void ArrayList<T>::print()
{
    for(int i = frontPos + 1; i < backPos; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::insertion_sort(int start, int end)
{
    if (start < 0 || start > length-1 ||
        end < 0 || end > length-1)
        return;
    for (int j = frontPos+1+start; j <= frontPos+1+end; j++)
    {
        int i = j-1;
        T key = array[j];
        while (i >= frontPos+1+start && array[i] > key)
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

template<typename T>
void ArrayList<T>::quick_sort(int start, int end)
{
    if (start < 0 || start > length-1 ||
        end < 0 || end > length-1)
        return;
    if(start < end)
    {
        int p;
        T pivot = (array[frontPos+1+start] + array[frontPos+1+end]) / 2;
        int i = start;
        int j = end;
        while(true)
        {
            while(array[frontPos+1+i] < pivot)
                i++;
            while(array[frontPos+1+j] > pivot)
                j--;
            if (i >= j)
            {
                p = j;
                break;
            }
            else
            {
                T addit;
                addit = array[frontPos+1+i];
                array[frontPos+1+i] = array[frontPos+1+j];
                array[frontPos+1+j] = addit;
                i++;
                j--;
            }
        }
        quick_sort(start, p);
        quick_sort(p+1, end);
    }
}

template<typename T>
LinkedList<T>::LinkedList()
{
    length = 0;
    front = nullptr;
    back = nullptr;
}

template<typename T>
void LinkedList<T>::push_back(T n)
{
    ListNode *newListNode;
    newListNode = new class ListNode;
    newListNode->value = n;
    newListNode->next = nullptr;
    length++;
    if (!back)
    {
        newListNode->prev = nullptr;
        front = newListNode;
        back = newListNode;
    }
    else
    {
        newListNode->prev = back;
        back->next = newListNode;
        back = newListNode;
    }
}

template<typename T>
void LinkedList<T>::push_front(T n)
{
    ListNode *newListNode;
    newListNode = new class ListNode;
    newListNode->value = n;
    newListNode->prev = nullptr;
    length++;
    if (!front)
    {
        newListNode->next = nullptr;
        front = newListNode;
        back = newListNode;
    }
    else
    {
        newListNode->next = front;
        front->prev = newListNode;
        front = newListNode;
    }
}

template<typename T>
void LinkedList<T>::print()
{
    ListNode *currentListNode = front;
    while(currentListNode)
    {
        std::cout << currentListNode->value << ' ';
        currentListNode = currentListNode->next;
    }
    std::cout << std::endl;
}

template<typename T>
bool LinkedList<T>::is_empty()
{
    if (length == 0)
        return true;
    else
        return false;
}

template<typename T>
T LinkedList<T>::pop_back()
{
    T res;
    if (is_empty())
        return res;
    length--;
    res = back->value;
    ListNode *currentListNode;
    currentListNode = back->prev;
    if (!currentListNode)
    {
        delete back;
        back = nullptr;
        front = back;
    }
    else
    {
        delete back;
        back = currentListNode;
        back->next = nullptr;
    }

    return res;
}

template<typename T>
T LinkedList<T>::pop_front()
{
    T res;
    if (is_empty())
        return res;
    length--;
    res = front->value;
    ListNode *currentListNode;
    currentListNode = front->next;
    if (!currentListNode)
    {
        delete front;
        front = nullptr;
        back = front;
    }
    else
    {
        delete front;
        front = currentListNode;
        front->prev = nullptr;
    }

    return res;
}

template<typename T>
void LinkedList<T>::clear()
{
    while(!is_empty())
    {
        pop_back();
    }
}

template<typename T>
typename LinkedList<T>::ListNode * LinkedList<T>::merge(ListNode *first, ListNode *second)
{
    if (!first)
        return second;

    if (!second)
        return first;

    if (first->value < second->value)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

template<typename T>
typename LinkedList<T>::ListNode * LinkedList<T>::split(ListNode *front)
{
    ListNode *fast = front, *slow = front;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode *temp = slow->next;
    slow->next = nullptr;
    return temp;
}

template<typename T>
typename LinkedList<T>::ListNode * LinkedList<T>::merge_sort(ListNode *front)
{
    if (!front || !front->next)
        return front;
    ListNode *second = split(front);

    front = merge_sort(front);
    second = merge_sort(second);

    return merge(front,second);
}

template<typename T>
void LinkedList<T>::merge_sort()
{
    front = merge_sort(front);
}

#endif //LAB1_LIST_H