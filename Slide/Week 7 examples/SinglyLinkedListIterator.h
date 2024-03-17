
#pragma once

#include "SinglyLinkedListTemplate.h"

template <typename T>
class SinglyLinkedListIterator
{
private:
    
    using ListNode = SinglyLinkedList<T>;
    
    const ListNode* fList;
    const ListNode* fIndex;
    
public:
    
    using Iterator = SinglyLinkedListIterator<T>;
    
    SinglyLinkedListIterator( const ListNode* aList ) :
        fList(aList),
        fIndex(aList)
    {}
    
    const T& operator*() const
    {
        return fIndex->fData;
    }

    Iterator& operator++()     // prefix
    {
        fIndex = fIndex->fNext;
        
        return *this;
    }
    
    Iterator operator++(int)   // postfix
    {
        Iterator old = *this;
        
        ++(*this);
        
        return old;
    }
    
    bool operator==( const Iterator& aRHS ) const
    {
        return
            fList == aRHS.fList &&
            fIndex == aRHS.fIndex;
    }
    
    bool operator!=( const Iterator& aRHS ) const
    {
        return !(*this == aRHS);
    }
    
    Iterator begin()       // for-range feature
    {
        Iterator iter = *this;
        
        iter.fIndex = iter.fList;
        
        return iter;
    }

    Iterator end()          // for-range feature
    {
        Iterator iter = *this;
        
        iter.fIndex = nullptr;
        
        return iter;
    }
};
