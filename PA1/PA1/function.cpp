#include <iostream>
#include <fstream>

#include "function.h"

using namespace std;



//-------------------------------------------------------------
template <class T>
void linkedlist<T>::addCommand(T c, T d)
{
    node<T>* newNode = new node<T>;
    newNode->command = c;
    newNode->description = d;
    newNode->next = head;
    head = newNode;
}

//-------------------------------------------------------------
template <class T>
node<T>* linkedlist<T>::getCommand(int index)
{
    node<T>* current = head;
    int i = 0;
    while (i < index)
    {
        current = current->next;
        i++;
    }
    return current;
}

//-------------------------------------------------------------
template <class T>
bool linkedlist<T>::searchCommand(T s)
{
    node<T>* current = head;
    while (current != NULL)
    {
        if (current->command == s)
            return true;
        current = current->next;
    }
    return false;
}

//-------------------------------------------------------------
template <class T>
void linkedlist<T>::removeCommand(T c)
{
    node<T>* current = head;
    node<T>* prev = NULL;
    while (current != NULL)
    {
        if (current->command == c)
        {
            if (current == head)
            {
                head = head->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}