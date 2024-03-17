
// COS30008, NTree, 2022

#include <iostream>
#include <string>

#include "NTree.h"

using namespace std;

void testBasicOperations()
{
    using NS3Tree = NTree<string,3>;

    string s1( "A" );
    string s2( "B" );
    string s3( "C" );
    
    cout << "Test basic operations:" << endl;

    NS3Tree root( "Hello World!" );

    root.attach( 0, *(new NS3Tree( s1 )) );
    root.attach( 1, *(new NS3Tree( s2 )) );
    root.attach( 2, *(new NS3Tree( s3 )) );
    const_cast<NS3Tree&>(root[1]).attach( 1, *(new NS3Tree( "AB" )) );

    cout << "root:       " << *root << endl;
    cout << "root[0]:    " << *root[0] << endl;
    cout << "root[1]:    " << *root[1] << endl;
    cout << "root[1][1]: " << *root[1][1] << endl;
    cout << "root[2]:    " << *root[2] << endl;
    
    cout << "Test copy semantics:" << endl;

    {
        NS3Tree copy = root;

        cout << "copy:       " << *copy << endl;
        cout << "copy[0]:    " << *copy[0] << endl;
        cout << "copy[1]:    " << *copy[1] << endl;
        cout << "copy[1][1]: " << *copy[1][1] << endl;
        cout << "copy[2]:    " << *copy[2] << endl;

        try
        {
            NS3Tree nil_copy = NS3Tree::NIL;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }

        root = copy;

        cout << "root:       " << *root << endl;
        cout << "root[0]:    " << *root[0] << endl;
        cout << "root[1]:    " << *root[1] << endl;
        cout << "root[1][1]: " << *root[1][1] << endl;
        cout << "root[2]:    " << *root[2] << endl;
        
        cout << "Object copy goes out of scope." << endl;
    }

    cout << "Test move semantics:" << endl;

    {
        NS3Tree copyM = std::move(root);

        try
        {
            NS3Tree nil_copy = std::move(NS3Tree::NIL);
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }

        cout << "copyM:       " << *copyM << endl;
        cout << "copyM[0]:    " << *copyM[0] << endl;
        cout << "copyM[1]:    " << *copyM[1] << endl;
        cout << "copyM[1][1]: " << *copyM[1][1] << endl;
        cout << "copyM[2]:    " << *copyM[2] << endl;

        root = std::move(copyM);

        if ( copyM.empty() )
        {
            cout << "Object copyM is empty." << endl;
        }

        try
        {
            NS3Tree nil_copy( "Empty" );

            nil_copy = std::move(NS3Tree::NIL);
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
        
        cout << "root:       " << *root << endl;
        cout << "root[0]:    " << *root[0] << endl;
        cout << "root[1]:    " << *root[1] << endl;
        cout << "root[1][1]: " << *root[1][1] << endl;
        cout << "root[2]:    " << *root[2] << endl;
        
        const_cast<NS3Tree&>(root[2]).attach( 2, const_cast<NS3Tree&>(root[1]).detach( 1 ) );

        cout << "root:       " << *root << endl;
        cout << "root[0]:    " << *root[0] << endl;
        cout << "root[1]:    " << *root[1] << endl;
        cout << "root[2]:    " << *root[2] << endl;
        cout << "root[2][2]: " << *root[2][2] << endl;
        
        cout << "Object copyM goes out of scope." << endl;
    }
    
    cout << "Object root goes out of scope." << endl;
}

int main()
{
    testBasicOperations();

    return 0;
}
