/**~*~*~*
 Binary Search Tree ADT - search
 Note: This ADT does not accept duplicate!
================================
*~*/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template <class KeyType>
class BinarySearchTree : public BinaryTree<KeyType>
{
public:
    // insert a node at the correct location
    bool insert(const int &ind, const KeyType &key);
    // remove a node if found
    // bool remove(const KeyType &item);
    // find a target node
    bool search(const KeyType &target, int &returnedIdx) const;

    bool setIndex(const KeyType &target, const int &index);

    // find the smallest node
    bool findSmallest(int &returnedIdx) const;
    // find the largest node
    bool findLargest(int &returnedIdx) const;
    // remove a node if found
    bool remove(const KeyType &key);

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<KeyType> *_insert(BinaryNode<KeyType> *nodePtr, BinaryNode<KeyType> *newNode);

    // search for target node
    BinaryNode<KeyType> *_search(BinaryNode<KeyType> *treePtr, const KeyType &target) const;

    // find the smallest node
    BinaryNode<KeyType> *_findSmallest(BinaryNode<KeyType> *nodePtr) const;

    // find the largest node
    BinaryNode<KeyType> *_findLargest(BinaryNode<KeyType> *nodePtr) const;

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<KeyType> *_remove(BinaryNode<KeyType> *nodePtr, const KeyType target, bool &success);

    // delete target node from tree, called by internal remove node
    BinaryNode<KeyType> *_removeNode(BinaryNode<KeyType> *targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<KeyType> *_removeLeftmostNode(BinaryNode<KeyType> *nodePtr, KeyType &successorKey, int &successorIdx);

    // remove the rightmost node in the right subtree of nodePtr
    BinaryNode<KeyType> *_removeRightmostNode(BinaryNode<KeyType> *nodePtr, KeyType &successorKey, int &successorIdx);
};

///////////////////////// public function definitions ///////////////////////////
// Wrapper for _findSmallest - Finding the smallest node in the tree
template <class KeyType>
bool BinarySearchTree<KeyType>::findSmallest(int &returnedIdx) const
{
    BinaryNode<KeyType> *smallestNode = _findSmallest(this->rootPtr);
    if (smallestNode)
    {
        returnedIdx = smallestNode->getIndex();
        return true;
    }
    return false;
}

// Wrapper for _findLargest - Finding the largest node in the tree
template <class KeyType>
bool BinarySearchTree<KeyType>::findLargest(int &returnedIdx) const
{
    BinaryNode<KeyType> *largestNode = _findLargest(this->rootPtr);
    if (largestNode)
    {
        returnedIdx = largestNode->getIndex();
        return true;
    }
    return false;
}

template <class KeyType>
inline bool BinarySearchTree<KeyType>::remove(const KeyType &key)
{
    bool success = false;
    this->rootPtr = _remove(this->rootPtr, key, success);
    if (success)
    {
        this->count--;
    }
    return success;
}

// Wrapper for _insert - Inserting items within a tree
template <class KeyType>
bool BinarySearchTree<KeyType>::insert(const int &ind, const KeyType &newEntry)
{
    int returnIdx;
    if (search(newEntry, returnIdx))
    {
        return false;
    }
    BinaryNode<KeyType> *newNodePtr = new BinaryNode<KeyType>(ind, newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    this->count++;
    return true;
}

// Wrapper for _search
//  - it calls the private _search function that returns a Node pointer or NULL
//  - if found, it sends its hashtable index back to the caller
//    via the output parameter, and returns true, otherwise it returns false.
template <class KeyType>
bool BinarySearchTree<KeyType>::search(const KeyType &anEntry, int &returnedIdx) const
{
    BinaryNode<KeyType> *temp = nullptr;
    temp = _search(this->rootPtr, anEntry);
    if (temp)
    {
        returnedIdx = temp->getIndex();
        return true;
    }
    return false;
}

template <class KeyType>
inline bool BinarySearchTree<KeyType>::setIndex(const KeyType &target, const int &index)
{
    int dummy;
    BinaryNode<KeyType> *node = _search(this->rootPtr, target);
    if (!node)
        return false;
    node->setIdx(index);
    return true;
}

//////////////////////////// private functions ////////////////////////////////////////////

// Rewrite the private insert as a recursive function.
template <class KeyType>
BinaryNode<KeyType> *BinarySearchTree<KeyType>::_insert(BinaryNode<KeyType> *nodePtr,
                                                        BinaryNode<KeyType> *newNodePtr)
{
    if (!nodePtr) // == nullptr
    {
        return newNodePtr;
    }
    else
    {
        if (newNodePtr->getKey() < nodePtr->getKey())
        {
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
        }
        else
        {
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        }
    }
    return nodePtr;
}

// Implement the private search function as a recursive function
// - return nullptr if target not found, otherwise
// - returns a pointer to the node that matched the target
template <class KeyType>
BinaryNode<KeyType> *BinarySearchTree<KeyType>::_search(BinaryNode<KeyType> *nodePtr,
                                                        const KeyType &target) const
{
    BinaryNode<KeyType> *found = nullptr;
    if (nodePtr == nullptr)
    {
        return nullptr;
    }

    if (nodePtr->getKey() == target)
    {
        return nodePtr;
    }
    else
    {
        KeyType key = nodePtr->getKey();
        if (key > target)
        {
            found = _search(nodePtr->getLeftPtr(), target);
        }
        else
        {
            found = _search(nodePtr->getRightPtr(), target);
        }
    }
    return found;
}

// Find the smallest node in the tree
template <class KeyType>
BinaryNode<KeyType> *BinarySearchTree<KeyType>::_findSmallest(BinaryNode<KeyType> *nodePtr) const
{
    if (nodePtr == nullptr || nodePtr->getLeftPtr() == nullptr)
    {
        return nodePtr;
    }
    return _findSmallest(nodePtr->getLeftPtr());
}

// Find the largest node in the tree
template <class KeyType>
BinaryNode<KeyType> *BinarySearchTree<KeyType>::_findLargest(BinaryNode<KeyType> *nodePtr) const
{
    if (nodePtr == nullptr || nodePtr->getRightPtr() == nullptr)
    {
        return nodePtr;
    }
    return _findLargest(nodePtr->getRightPtr());
}

// Remove a node from the tree
template <class KeyType>
BinaryNode<KeyType> *BinarySearchTree<KeyType>::_remove(BinaryNode<KeyType> *nodePtr, const KeyType target, bool &success)
{
    // If the nodePtr is null, the target is not found
    if (nodePtr == nullptr)
    {
        return nullptr;
    }
    // If the target is less than the current node's item, search in the left subtree
    if (target < nodePtr->getKey())
    {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    }
    // If the target is greater than the current node's item, search in the right subtree
    else if (target > nodePtr->getKey())
    {
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    }
    // If the target is equal to the current node's item, we found the node to remove
    else
    {
        success = true;
        return _removeNode(nodePtr);
    }
    // If it does not hit
    // or has been deleted in the lower layer
    // return the current node to the upper layer and continue to hang back recursively
    return nodePtr;
}

// Remove a node from the tree
// This function is called by _remove to actually delete the target node
template <class KeyType>
inline BinaryNode<KeyType> *BinarySearchTree<KeyType>::_removeNode(BinaryNode<KeyType> *targetNodePtr)
{
    // If the target node is a leaf node, delete it and return nullptr
    if (targetNodePtr->isLeaf())
    {
        delete targetNodePtr;
        return nullptr;
    }
    // If the target node has only one child, delete it and return the child
    if (targetNodePtr->getLeftPtr() != nullptr &&
        targetNodePtr->getRightPtr() == nullptr)
    {
        BinaryNode<KeyType> *leftChild = targetNodePtr->getLeftPtr();
        delete targetNodePtr;
        return leftChild;
    }
    if (targetNodePtr->getLeftPtr() == nullptr &&
        targetNodePtr->getRightPtr() != nullptr)
    {
        BinaryNode<KeyType> *rightChild = targetNodePtr->getRightPtr();
        delete targetNodePtr;
        return rightChild;
    }
    // If the target node has two children, find the in-order successor
    // the smallest node in the right subtree, replace the target node's item with it,
    // and then remove the in-order successor from the right subtree
    KeyType successorKey;
    int succIdx;
    BinaryNode<KeyType> *newRightSubtree = _removeLeftmostNode(targetNodePtr->getRightPtr(), successorKey, succIdx);
    targetNodePtr->setKey(successorKey);
    targetNodePtr->setIdx(succIdx);
    targetNodePtr->setRightPtr(newRightSubtree);
    // Return the target node pointer, which now has its item replaced
    return targetNodePtr;
}

// Remove the leftmost node in the left subtree of nodePtr
// This function is used to find the in-order successor when removing a node with two children
// It returns the new subtree with the leftmost node removed and sets the successor value
// to the item of the removed node.
template <class KeyType>
inline BinaryNode<KeyType> *BinarySearchTree<KeyType>::_removeLeftmostNode(BinaryNode<KeyType> *nodePtr, KeyType &successorKey, int &successorIdx)
{
    // If the left child is null, we found the leftmost node
    if (nodePtr->getLeftPtr() == nullptr)
    {
        // Store the item of the leftmost node in successor
        successorKey = nodePtr->getKey();
        successorIdx = nodePtr->getIndex();
        // If the leftmost node has a right child, return it
        BinaryNode<KeyType> *rightChild = nodePtr->getRightPtr();
        delete nodePtr;
        return rightChild;
    }
    // Recursively call _removeLeftmostNode on the left child
    // to find the leftmost node
    // and update the successor value
    nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), successorKey, successorIdx));
    // Return the current node pointer, which now has its left child updated
    return nodePtr;
}

// Remove the rightmost node in the right subtree of nodePtr
// This function is used to find the in-order predecessor when removing a node with two children
// It returns the new subtree with the rightmost node removed and sets the successor value
// to the item of the removed node.
template <class KeyType>
inline BinaryNode<KeyType> *BinarySearchTree<KeyType>::_removeRightmostNode(BinaryNode<KeyType> *nodePtr, KeyType &successorKey, int &successorIdx)
{
    // If the right child is null, we found the rightmost node
    if (nodePtr->getRightPtr() == nullptr)
    {
        // Store the item of the rightmost node in successor
        successorKey = nodePtr->getKey();
        successorIdx = nodePtr->getIndex();

        // If the rightmost node has a left child, return it
        BinaryNode<KeyType> *leftChild = nodePtr->getLeftPtr();
        delete nodePtr;
        return leftChild;
    }
    // Recursively call _removeRightmostNode on the right child
    // to find the rightmost node
    // and update the successor value
    nodePtr->setRightPtr(_removeRightmostNode(nodePtr->getRightPtr(), successorKey, successorIdx));
    // Return the current node pointer, which now has its right child updated
    return nodePtr;
}

#endif
