#include <iostream>
using namespace std;

// ***** B-Tree properties (m-order) *****
// 1. All the leaf nodes must be at the same level
// 2. Any node cannot have more than m children
// 3. A non-leaf node with k children should have k-1 keys (#2 & #3 imply maximum #keys = m-1)
// 4. Each internal node (non-leaf and non-root) should have at least (m/2) children (rounded up)
//    Implies minimum #keys = ceil(m/2) - 1
// 5. The root should have at least two children – unless it’s a leaf

// ***** B-Tree Split *****
// - Split happens when a node becomes full
// - When a node splits, the middle key goes up and rest of the keys go to the left and right 
//   sub-trees
// - A split may cause the parent node to become full and trigger another recursive split.

// ***** B+ Tree requirements *****
//  - APIs: findKey(key), rangeScan(key1, key2), insert(key), delete(key), update(key)
//  - Internal functions - split(node), merge(node), rebalance(node)?
//  - Should support fast full scan in 1 direction
//  - The node of the tree can contain n #keys
//  - Value can be anything (abstract type/ void *)
//  - non-leaf nodes just contains pointers to the leaf nodes that 
//      contain all keys and actual pointers to records.
//  - Leaf node contains the keys

// template <typename keyType>;
// template <typename valueType>;

class BTreeNode
{
    private:

    keyType      *keysArray;
    valueType    *valueArray;
    BTreeNode   **ptrArray;

    public:

    BTreeNode(int order)
    {
        keysArray = new keyType[order];
        ptrArray = new BTreeNode *[order];
    }

    ~BTreeNode()
    {
        delete keysArray;
        delete ptrArray;
    }
};

class BTree
{
    private:

    public:

    static const int NUM_KEYS = 2;

    BTree(int order)
    {
        
    }

    ~BTree()
    {

    }
};

int main()
{
    
    return 1;
}