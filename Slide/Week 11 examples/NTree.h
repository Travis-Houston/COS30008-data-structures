
// COS30008, NTree, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

template<typename T, size_t N>
class NTree
{
private:
    T fKey;                                         // T() for empty NTree
    NTree<T,N>* fNodes[N];                          // N subtrees of degree N

    void initLeaves()
    {
        for ( size_t i = 0; i < N; i++ )
        {
            fNodes[i] = &NIL;
        }
    }
    
    NTree() : fKey(T())                             // sentinel constructor
    {
        initLeaves();
    }
    
public:
    static NTree<T,N> NIL;                          // Empty NTree
    
    NTree( const T& aKey ) : fKey(aKey)             // NTree leaf
    {
        initLeaves();
    }

    NTree( T&& aKey ) : fKey(std::move(aKey))       // NTree leaf
    {
        initLeaves();
    }

    NTree( const NTree& aOtherNTree )               // copy constructor
    {
        initLeaves();
        
        *this = aOtherNTree;
    }

    NTree( NTree&& aOtherNTree )                    // move constructor
    {
        initLeaves();
        
        *this = std::move(aOtherNTree);
    }

    virtual ~NTree()                                // destructor
    {
        if ( empty() )
        {
            std::cout << "Delete NIL" << std::endl;
        }
        
        for ( size_t i = 0; i < N; i++ )
        {
            if ( !fNodes[i]->empty() )              // don't delete NIL
            {
                std::cout << "Delete node: " << fNodes[i]->fKey << std::endl;
                delete fNodes[i];
            }
        }
    }
    
    NTree& operator=( const NTree& aOtherNTree )    // copy assignment operator
    {
        if ( this != &aOtherNTree )
        {
            if ( !aOtherNTree.empty() )
            {
                this->~NTree();
                
                fKey = aOtherNTree.fKey;
                
                for ( size_t i = 0; i < N; i++ )
                {
                    if ( !aOtherNTree.fNodes[i]->empty() )
                    {
                        fNodes[i] = aOtherNTree.fNodes[i]->clone();
                    }
                    else
                    {
                        fNodes[i] = &NIL;
                    }
                }
            }
            else
            {
                throw std::domain_error( "Copying of NIL detected." );
            }
        }
        
        return *this;
    }

    NTree& operator=( NTree&& aOtherNTree )         // move assignment operator
    {
        if ( this != &aOtherNTree )
        {
            if ( !aOtherNTree.empty() )
            {
                this->~NTree();
                
                fKey = std::move(aOtherNTree.fKey);
                
                for ( size_t i = 0; i < N; i++ )
                {
                    if ( !aOtherNTree.fNodes[i]->empty() )
                    {
                        fNodes[i] = const_cast<NTree<T,N>*>(&aOtherNTree.detach( i ));
                    }
                    else
                    {
                        fNodes[i] = &NIL;
                    }
                }
            }
            else
            {
                throw std::domain_error( "Moving of NIL detected." );
            }
        }

        return *this;
    }

    virtual NTree* clone()                          // clone a tree
    {
        if ( !empty() )
        {
            return new NTree( *this );
        }
        else
        {
            throw std::domain_error( "Cloning of NIL detected." );
        }
    }

    bool empty() const                              // is tree empty
    {
        return this == &NIL;
    }
    
    const T& operator*() const                      // get key (node value)
    {
        return fKey;
    }

    const NTree& operator[]( size_t aIndex ) const  // indexer
    {
        if ( !empty() )
        {
            if ( aIndex < N )
            {
                return *fNodes[aIndex];             // return reference to subtree
            }
            else
            {
                throw std::out_of_range( "Illegal subtree index!" );
            }
        }
        else
        {
            throw std::domain_error( "Empty NTree!" );
        }
    }

    // tree manipulators

    void attach( size_t aIndex, const NTree<T,N>& aNTree )
    {
        if ( !empty() )
        {
            if ( aIndex < N )
            {
                if ( fNodes[aIndex]->empty() )
                {
                    fNodes[aIndex] = const_cast<NTree<T,N>*>(&aNTree);
                }
                else
                {
                    throw std::domain_error( "Non-empty subtree present!" );
                }
            }
            else
            {
                throw std::out_of_range( "Illegal subtree index!" );
            }
        }
        else
        {
            throw std::domain_error( "Empty NTree!" );
        }
    }

    const NTree& detach( size_t aIndex )
    {
        if ( !empty() )
        {
            if ( (aIndex < N) && !fNodes[aIndex]->empty() )
            {
                const NTree<T,N>& Result = *fNodes[aIndex];     // obtain reference to subtree
                fNodes[aIndex] = &NIL;                          // set to NIL
                return Result;                                  // return subtree (reference)
            }
            else
            {
                throw std::out_of_range( "Illegal subtree index!" );
            }
        }
        else
        {
            throw std::domain_error( "Empty NTree!" );
        }
    }
};

template<class T, size_t N>
NTree<T,N> NTree<T,N>::NIL;
