/**~*~*~*
 Binary Search Tree ADT - search
 Note: This ADT accepts duplicate!!!
================================
*~*/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template <class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // remove a node if found
    // bool remove(const ItemType &item);
    // find a target node
    bool search(const ItemType &target, ItemType &returnedItem) const;
    // find the smallest node
    bool findSmallest(ItemType &returnedItem) const;
    // find the largest node
    bool findLargest(ItemType &returnedItem) const;
    // remove a node if found
    bool remove(const ItemType &item);

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType> *_insert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType> *newNode);

    // search for target node
    BinaryNode<ItemType> *_search(BinaryNode<ItemType> *treePtr, const ItemType &target) const;

    // find the smallest node
    BinaryNode<ItemType> *_findSmallest(BinaryNode<ItemType> *nodePtr) const;

    // find the largest node
    BinaryNode<ItemType> *_findLargest(BinaryNode<ItemType> *nodePtr) const;

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType> *_remove(BinaryNode<ItemType> *nodePtr, const ItemType target, bool &success);

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType> *_removeNode(BinaryNode<ItemType> *targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType> *_removeLeftmostNode(BinaryNode<ItemType> *nodePtr, ItemType &successor);

    // remove the rightmost node in the right subtree of nodePtr
    BinaryNode<ItemType> *_removeRightmostNode(BinaryNode<ItemType> *nodePtr, ItemType &successor);
};

///////////////////////// public function definitions ///////////////////////////
// Wrapper for _findSmallest - Finding the smallest node in the tree
template <class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType &returnedItem) const
{
    BinaryNode<ItemType> *smallestNode = _findSmallest(this->rootPtr);
    if (smallestNode)
    {
        returnedItem = smallestNode->getItem();
        return true;
    }
    return false;
}

// Wrapper for _findLargest - Finding the largest node in the tree
template <class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType &returnedItem) const
{
    BinaryNode<ItemType> *largestNode = _findLargest(this->rootPtr);
    if (largestNode)
    {
        returnedItem = largestNode->getItem();
        return true;
    }
    return false;
}

template <class ItemType>
inline bool BinarySearchTree<ItemType>::remove(const ItemType &item)
{
    bool success = false;
    this->rootPtr = _remove(this->rootPtr, item, success);
    if (success)
    {
        this->count--;
    }
    return success;
}

// Wrapper for _insert - Inserting items within a tree
template <class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType &newEntry)
{
    BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    this->count++;
    return true;
}

// Wrapper for _search
//  - it calls the private _search function that returns a Node pointer or NULL
//  - if found, it copies data from that node and sends it back to the caller
//    via the output parameter, and returns true, otherwise it returns false.
template <class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType &anEntry, ItemType &returnedItem) const
{
    BinaryNode<ItemType> *temp = nullptr;
    temp = _search(this->rootPtr, anEntry);
    if (temp)
    {
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

// Rewrite the private insert as a recursive function.
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType> *nodePtr,
                                                          BinaryNode<ItemType> *newNodePtr)
{
    if (!nodePtr) // == nullptr
    {
        return newNodePtr;
    }
    else
    {
        if (newNodePtr->getItem() < nodePtr->getItem())
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
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_search(BinaryNode<ItemType> *nodePtr,
                                                          const ItemType &target) const
{
    BinaryNode<ItemType> *found = nullptr;
    if (nodePtr == nullptr)
    {
        return nullptr;
    }

    if (nodePtr->getItem() == target)
    {
        return nodePtr;
    }
    else
    {
        ItemType item = nodePtr->getItem();
        if (item > target)
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
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType> *nodePtr) const
{
    if (nodePtr == nullptr || nodePtr->getLeftPtr() == nullptr)
    {
        return nodePtr;
    }
    return _findSmallest(nodePtr->getLeftPtr());
}

// Find the largest node in the tree
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType> *nodePtr) const
{
    if (nodePtr == nullptr || nodePtr->getRightPtr() == nullptr)
    {
        return nodePtr;
    }
    return _findLargest(nodePtr->getRightPtr());
}

// Remove a node from the tree
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType> *nodePtr, const ItemType target, bool &success)
{
    // If the nodePtr is null, the target is not found
    if (nodePtr == nullptr) {
        return nullptr;
    }
    // If the target is less than the current node's item, search in the left subtree
    if (target < nodePtr->getItem()) {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    }
    // If the target is greater than the current node's item, search in the right subtree
    else if (target > nodePtr->getItem()) {
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    }
    // If the target is equal to the current node's item, we found the node to remove
    else {
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
template <class ItemType>
inline BinaryNode<ItemType> *BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType> *targetNodePtr)
{
    // If the target node is a leaf node, delete it and return nullptr
    if (targetNodePtr->isLeaf()) {
        delete targetNodePtr;
        return nullptr;
    }
    // If the target node has only one child, delete it and return the child
    if (targetNodePtr->getLeftPtr() != nullptr &&
        targetNodePtr->getRightPtr() == nullptr)
    {
        BinaryNode<ItemType>* leftChild = targetNodePtr->getLeftPtr();
        delete targetNodePtr;
        return leftChild;
    }
    if (targetNodePtr->getLeftPtr() == nullptr &&
        targetNodePtr->getRightPtr() != nullptr)
    {
        BinaryNode<ItemType>* rightChild = targetNodePtr->getRightPtr();
        delete targetNodePtr;
        return rightChild;
    }
    // If the target node has two children, find the in-order successor
    // the smallest node in the right subtree, replace the target node's item with it,
    // and then remove the in-order successor from the right subtree
    ItemType successorValue;
    BinaryNode<ItemType>* newRightSubtree = _removeLeftmostNode(targetNodePtr->getRightPtr(), successorValue);
    targetNodePtr->setItem(successorValue);
    targetNodePtr->setRightPtr(newRightSubtree);
    // Return the target node pointer, which now has its item replaced
    return targetNodePtr;
}

// Remove the leftmost node in the left subtree of nodePtr
// This function is used to find the in-order successor when removing a node with two children
// It returns the new subtree with the leftmost node removed and sets the successor value
// to the item of the removed node.
template <class ItemType>
inline BinaryNode<ItemType> *BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType> *nodePtr, ItemType &successor)
{
    // If the left child is null, we found the leftmost node
    if (nodePtr->getLeftPtr() == nullptr) {
        // Store the item of the leftmost node in successor
        successor = nodePtr->getItem();
        // If the leftmost node has a right child, return it
        BinaryNode<ItemType>* rightChild = nodePtr->getRightPtr();
        delete nodePtr;
        return rightChild;
    }
    // Recursively call _removeLeftmostNode on the left child
    // to find the leftmost node
    // and update the successor value
    nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), successor));
    // Return the current node pointer, which now has its left child updated
    return nodePtr;
}

// Remove the rightmost node in the right subtree of nodePtr
// This function is used to find the in-order predecessor when removing a node with two children
// It returns the new subtree with the rightmost node removed and sets the successor value
// to the item of the removed node.
template <class ItemType>
inline BinaryNode<ItemType> *BinarySearchTree<ItemType>::_removeRightmostNode(BinaryNode<ItemType> *nodePtr, ItemType &successor)
{
    // If the right child is null, we found the rightmost node
    if (nodePtr->getRightPtr() == nullptr) {
        // Store the item of the rightmost node in successor
        successor = nodePtr->getItem();
        // If the rightmost node has a left child, return it
        BinaryNode<ItemType>* leftChild = nodePtr->getLeftPtr();
        delete nodePtr;
        return leftChild;
    }
    // Recursively call _removeRightmostNode on the right child
    // to find the rightmost node
    // and update the successor value 
    nodePtr->setRightPtr(_removeRightmostNode(nodePtr->getRightPtr(), successor));
    // Return the current node pointer, which now has its right child updated
    return nodePtr;
}

#endif
