// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_SSII2019
{
   // CONSTRUCTORS and DESTRUCTOR
    sequence::sequence(size_type initial_capacity):used(0),current_index(0),capacity(initial_capacity)
   {
       if (initial_capacity <= 0)
          initial_capacity = 1;
       
       data = new value_type[capacity];
   }

    sequence::sequence(const sequence& source):used(source.used),current_index(source.current_index),capacity(source.capacity)
   {
       data = new value_type[capacity];
       //copy(source.data, source.data + used, data);
       for (size_type index = 0; index < source.used; ++index)
           data[index] = source.data[index];
   }

   sequence::~sequence()
   {
      delete [] data;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
       if(new_capacity < 1)
           new_capacity = 1;
       if(new_capacity < used)
           new_capacity = used;
       
       value_type *newData = new value_type[new_capacity];
       for(size_type index = 0; index < used; ++index)
           newData[index] = data[index];
       
       delete [] data;
       capacity = new_capacity;
       data = newData;
   }

   void sequence::start()
   {
       current_index = 0;
   }

   void sequence::advance()
   {
       assert(is_item());
       current_index = current_index + 1;
   }

   void sequence::insert(const value_type& entry)
   {
       if(used == capacity)
          resize(int(1.5*capacity)+1);
       
       if(!is_item())
       {
           for(size_type index = used; index > 0; --index)
               data[index] = data[index-1];
           
           data[0] = entry;
           ++used;
           current_index = 0;
       }
       else
       {
           for(size_type index = used; index > current_index; --index)
               data[index] = data[index-1];
           
           data[current_index] = entry;
           ++used;
       }
   }

   void sequence::attach(const value_type& entry)
   {
       if(used == capacity)
           resize(size_type(1.5*capacity)+1);
       if(!is_item())
       {
           data[current_index] = entry;
           ++used;
       }
       else
       {
           for(size_type index = used; index >(current_index+1); --index)
               data[index] = data[index-1];
           
           data[current_index+1] = entry;
           ++used;
           ++current_index;
       }
   }

   void sequence::remove_current()
   {
       assert(is_item());
       if(used == 1)
       {
           --used;
           current_index = used;
       }
       else
       {
           for(int index = current_index; index < used-1; ++index)
               data[index] = data[index+1];
           
           --used;
       }
   }

   sequence& sequence::operator = (const sequence& source)
   {
      if(data != source.data)
      {
          delete [] data;
          value_type * newData = new value_type[source.capacity];
          
          //copy(source.data, source.data+used, newData);
          for (size_type index = 0; index < source.used; ++index)
              newData[index] = source.data[index];
          
          data = newData;
          used = source.used;
          current_index = source.current_index;
          capacity = source.capacity;
      }
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
       return used;
   }

   bool sequence::is_item() const
   {
       if(current_index == used)
          return false;
       else
          return true;
   }

   sequence::value_type sequence::current() const
   {
       assert(is_item());
       return data[current_index];
   }
}

