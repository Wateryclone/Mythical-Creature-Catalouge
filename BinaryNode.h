/**~*~*~*
 Specification file for the BinaryNode class
============================================
*~*/
#ifndef _BINARY_NODE
#define _BINARY_NODE

template <class KeyType>
class BinaryNode
{
private:
    int index;                     // index
    KeyType key;                   // Data portion
    BinaryNode<KeyType> *leftPtr;  // Pointer to left child
    BinaryNode<KeyType> *rightPtr; // Pointer to right child

public:
    // constructors
    BinaryNode(const int &index, KeyType &anItem)
    {
        index = index;
        key = anItem;
        leftPtr = nullptr;
        rightPtr = nullptr;
    }
    BinaryNode(const int &index,
               const KeyType &anItem,
               BinaryNode<KeyType> *left,
               BinaryNode<KeyType> *right)
    {
        key = anItem;
        leftPtr = left;
        rightPtr = right;
    }
    // setters
    void setKey(const int &index) {this->index = index; }
    void setItem(const KeyType &anItem) { key = anItem; }
    void setLeftPtr(BinaryNode<KeyType> *left) { leftPtr = left; }
    void setRightPtr(BinaryNode<KeyType> *right) { rightPtr = right; }

    // getters
    int getIndex() const { return index; }
    KeyType getKey() const { return key; }
    BinaryNode<KeyType> *getLeftPtr() const { return leftPtr; }
    BinaryNode<KeyType> *getRightPtr() const { return rightPtr; }

    // other functions
    bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif
