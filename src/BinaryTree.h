/**~*~*~*
 Binary tree abstract base class
===========================================
*~*/
// Note: All calls to the `visit` function in this header file are made using the key of the object stored in the binary search tree.
// To perform operations like traversal or printing, please implement the `visit` function such that it retrieves the full object 
// information from the hash table using the index corresponding to the given key.

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template <class KeyType>
class BinaryTree
{
protected:
    BinaryNode<KeyType> *rootPtr;  // ptr to root node
    int count;                     // number of nodes in tree

public:
    // "admin" functions
    BinaryTree()
    {
        rootPtr = nullptr;
        count = 0;
    }
    BinaryTree(const BinaryTree<KeyType> &) = delete; // disable COPY constructor!
    BinaryTree &operator=(const BinaryTree<KeyType> &) = delete; // disable COPY assignment operator!
    virtual ~BinaryTree() { destroyTree(rootPtr); }

    // common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int getCount() const { return count; }
    void clear()
    {
        destroyTree(rootPtr);
        rootPtr = 0;
        count = 0;
    }
    void preOrder(void visit(const KeyType &)) const { _preorder(visit, rootPtr); }
    void inOrder(void visit(const KeyType &)) const { _inorder(visit, rootPtr); }
    void postOrder(void visit(const KeyType &)) const { _postorder(visit, rootPtr); }
    void printTree(void visit(const KeyType &, int)) const { _printTree(visit, rootPtr, 1); }
    void printLeaf(void visit(const KeyType &)) const { _printLeaf(visit, rootPtr); }

    // abstract functions to be implemented by derived class
    virtual bool insert(const int &idx, const KeyType &newData) = 0;
    // virtual bool remove(const KeyType &data) = 0;
    virtual bool search(const KeyType &target, int &returnedItem) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<KeyType> *nodePtr);

    // internal traverse
    void _preorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const;
    void _inorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const;
    void _postorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const;
    void _printTree(void visit(const KeyType &, int), BinaryNode<KeyType> *nodePtr, int level) const;
    void _printLeaf(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const;
};

// Destroy the entire tree
template <class KeyType>
void BinaryTree<KeyType>::destroyTree(BinaryNode<KeyType> *nodePtr)
{
    if (nodePtr) // != nullptr
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        // cout << "DEBUG - Destructor: Now deleting " << nodePtr->getKey().getName() << endl;
        delete nodePtr;
    }
}

// Preorder Traversal
template <class KeyType>
void BinaryTree<KeyType>::_preorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const
{
    if (nodePtr)
    {
        KeyType key = nodePtr->getKey();
        visit(key);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

// Inorder Traversal
template <class KeyType>
void BinaryTree<KeyType>::_inorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const
{
    if (nodePtr) // != NULL
    {
        KeyType key = nodePtr->getKey();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(key);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

// Postorder Traversal
template <class KeyType>
void BinaryTree<KeyType>::_postorder(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const
{
    if (nodePtr) // != NULL
    {
        KeyType key = nodePtr->getKey();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(key);
    }
}

// Prints tree as an indented list
template <class KeyType>
void BinaryTree<KeyType>::_printTree(void visit(const KeyType &, int), BinaryNode<KeyType> *nodePtr, int level) const
{
    if (nodePtr) // != NULL
    {
        KeyType key = nodePtr->getKey();
        visit(key, level);
        _printTree(visit, nodePtr->getLeftPtr(), level + 1);
        _printTree(visit, nodePtr->getRightPtr(), level + 1);
    }
}

// Prints leaf nodes
template <class KeyType>
inline void BinaryTree<KeyType>::_printLeaf(void visit(const KeyType &), BinaryNode<KeyType> *nodePtr) const
{
    if (!nodePtr)
        return;
    if (!nodePtr->getLeftPtr() && !nodePtr->getRightPtr())
    {
        visit(nodePtr->getKey());
    }
    else
    {
        _printLeaf(visit, nodePtr->getLeftPtr());
        _printLeaf(visit, nodePtr->getRightPtr());
    }
}
#endif
