
#pragma once

#include <stdexcept>

template<typename T, size_t N>
class NTree
{
private:
    T fKey;                                         // T() for empty NTree
    NTree<T,N>* fNodes[N];                          // N subtrees of degree N
    
    void initLeaves();                              // initialize subtree nodes
    
    NTree();                                        // sentinel constructor
    
public:
    static NTree<T,N> NIL;                          // Empty NTree
    
    NTree( const T& aKey );                         // NTree leaf
    NTree( T&& aKey );                              // NTree leaf

    NTree( const NTree& aOtherNTree );              // copy constructor
    NTree( NTree&& aOtherNTree );                   // move constructor
    
    virtual ~NTree();                               // destructor
    
    NTree& operator=( const NTree& aOtherNTree );   // copy assignment operator
    NTree& operator=( NTree&& aOtherNTree );        // move assignment operator
    
    virtual NTree* clone();                         // clone a tree
    
    bool empty() const;                             // is tree empty
    const T& operator*() const;                     // get key (node value)
    
    const NTree& operator[]( size_t aIndex ) const; // indexer
    
    // tree manipulators
    void attach( size_t aIndex, const NTree<T,N>& aNTree );
    const NTree& detach( size_t aIndex );
};

template<class T, size_t N>
NTree<T,N> NTree<T,N>::NIL;
