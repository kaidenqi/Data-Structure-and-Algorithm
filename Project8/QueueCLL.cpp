// FILE: QueueCLL.cpp
// IMPLEMENTS: QueueCLL (see QueueCLL.h for documentation.)
//
// INVARIANT for the QueueCLL class:
//   1. The number of items in the QueueCLL is stored in the member
//      variable numItems.
//   2. The items themselves are stored in a circular linked list
//      of Nodes.
//      2.1 The member variable rear_ptr points to the rear of the
//          QueueCLL (tail node of the circular linked list).
//          heap[0] through heap[used - 1].
//      2.2 The rear_ptr is set to the null address if the circular
//          linked list (thus queue) is empty.

#include <iostream>
#include <cassert>  // provides assert
#include <cstdlib>  // provides size_t
using namespace std;

#include "QueueCLL.h"   

QueueCLL::QueueCLL():numItems(0){}

QueueCLL::QueueCLL(const QueueCLL& src) :numItems(0)
{
    for(value_type index = 1; index <= src.numItems; ++index)
        push(src.peek(index));
}

QueueCLL::~QueueCLL()
{
   while (!empty())
       pop();
}

QueueCLL& QueueCLL::operator=(const QueueCLL& rhs)
{
   if(this != &rhs)
   {
       for(value_type index = 1; index <= rhs.numItems; ++index)
           this -> push(rhs.peek(index));
       numItems = rhs.numItems;
   }
    return *this;
}

void QueueCLL::push(const value_type& entry)
{
    Node *temp = new Node;
    temp->data = entry;
    
    if (empty())
        rear_ptr = temp;
    else if (numItems == 1)
    {
        temp->link = rear_ptr;
        rear_ptr -> link = temp;
        rear_ptr = temp;
    }
    else
    {
        temp->link = rear_ptr -> link;
        rear_ptr -> link = temp;
        rear_ptr = temp;
    }
    ++numItems;
}

QueueCLL::value_type QueueCLL::front( ) const
{
    assert(size() > 0);
   
    if (numItems == 1)
        return rear_ptr -> data;
    else
        return rear_ptr -> link -> data;
}

void QueueCLL::pop( )
{
    assert(size() > 0);
    
    if(numItems == 1)
    {
        delete rear_ptr;
        rear_ptr = NULL;
    }
    else
    {
        Node *temp = rear_ptr -> link;
        rear_ptr -> link = temp -> link;
        delete temp;
    }
    --numItems;
}

QueueCLL::size_type QueueCLL::size() const
{
    return numItems;
}

bool QueueCLL::empty() const
{
    return numItems == 0;
}

QueueCLL::value_type QueueCLL::peek(size_type n) const
{
    assert(size() > 0);
    
    if(numItems == 1)
        return rear_ptr -> data;
    else
    {
        Node *temp = rear_ptr;
        for (value_type index = 0; index < n; ++index)
            temp = temp -> link;
        return temp -> data;
    }
}

