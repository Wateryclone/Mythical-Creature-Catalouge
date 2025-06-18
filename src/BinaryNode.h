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
    BinaryNode(const int &idx, const KeyType &k)
    {
        index = idx;
        key = k;
        leftPtr = nullptr;
        rightPtr = nullptr;
    }
    BinaryNode(const int &index,
               const KeyType &k,
               BinaryNode<KeyType> *left,
               BinaryNode<KeyType> *right) : index(index), key(k), leftPtr(left), rightPtr(right)
    {
    }
    // setters
    void setIdx(const int &index) {this->index = index; }
    void setKey(const KeyType &key) { this->key = key; }
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
