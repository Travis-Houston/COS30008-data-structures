
// COS30008, Final Exam, 2023

#pragma once

#include "TernaryTree.h"

#include <stack>

template<typename T>
class TernaryTreePrefixIterator
{
private:
    using TTree = TernaryTree<T>;
    using TTreeNode = TTree*;
    using TTreeStack = std::stack<const TTree*>;

    const TTree* fTTree;                // ternary tree
    TTreeStack fStack;                  // traversal stack

public:

    using Iterator = TernaryTreePrefixIterator<T>;

    Iterator operator++(int)
    {
        Iterator old = *this;

        ++(*this);

        return old;
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 4: TernaryTree Prefix Iterator

private:

    // push subtree of aNode [30]
    void push_subtrees(const TTree* aNode)
    {

    }

public:

    // iterator constructor [12]
    TernaryTreePrefixIterator(const TTree* aTTree);

    // iterator dereference [8]
    const T& operator*() const;

    // prefix increment [12]
    Iterator& operator++();

    // iterator equivalence [12]
    bool operator==(const Iterator& aOtherIter) const;

    // auxiliaries [4,10]
    Iterator begin() const;
    Iterator end() const;
};
