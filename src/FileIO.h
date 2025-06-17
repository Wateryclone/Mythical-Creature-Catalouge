/*
File I/O
*/
#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "BinarySearchTree.h"
#include "Creature.h"
#include "HashTable.h"

struct Record
{
    std::string creatureID;
    std::string name;
    std::string category;
    std::string history;
    std::string habitat;
    std::string description;
    int releventYear;
};

class FileIO
{
public:
    FileIO();

    // This function will read a text document and then build and manage a binary search tree and a hash table
    bool init(const std::string &filename);

    ~FileIO();

    void setFileName(const std::string &filename);

    bool insert(const Creature &c);

    bool search(const std::string &ID) const;

    bool del(const std::string &ID);

    int getHashTableSize();

    float getHashTableloadFactor();

    int getHashTableLongestChain();

    int getHashTableEmptyBuckets();

    void inOrder(void visit(const std::string &ID));

    bool is_ready();

    Creature getCreature(const std::string &ID) const;

    // Load from file into BST and hash table PS: Only binary trees are loaded for now
    void loadData();

    // Save hash‐table contents in table order back to a file
    void saveData(const std::string &outFilename) const;

private:
    std::string fileName;
    std::ifstream inFile;
    BinarySearchTree<string> bst;
    HashTable *hashTable;
    int tableSize;

    // Helpers for sizing / rehashing
    static bool isPrime(int n);
    static int nextPrime(int n);
    void rehash();

    // Disable copy semantics
    FileIO(const FileIO &) = delete;
    FileIO &operator=(const FileIO &) = delete;
};

// Implementation

inline FileIO::FileIO()
    : bst(),
      hashTable(nullptr),
      tableSize(0)
{
}

bool inline FileIO::init(const std::string &filename)
{
    this->fileName = filename;
    inFile.open(this->fileName);
    if (!inFile.is_open())
    {
        return false;
    }

    // Count lines
    int lines = 0;
    std::string line;
    while (std::getline(inFile, line))
    {
        ++lines;
    }

    // rewind to beginning
    inFile.clear();
    inFile.seekg(0);

    // Determine initial hash size = next prime ≥ 2 * lines
    tableSize = nextPrime(lines * 2);

    // construct hash table with size
    hashTable = new HashTable(tableSize); // placeholder for HashTable class

    // Load data
    loadData();
    return true;
}

inline FileIO::~FileIO()
{
    if (hashTable)
    {
        delete hashTable;
    }

    if (inFile.is_open())
    {
        inFile.close();
    }
}

inline void FileIO::setFileName(const std::string &filename)
{
    fileName = filename;
}

inline bool FileIO::insert(const Creature &c)
{
    if (search(c.getCreatureID()))
    {
        return false;
    }
    int idx = hashTable->insert(c);
    // only insert (key, idx) into BST
    if (bst.insert(idx, c.getCreatureID()))
    {
        return true;
    }
    return false;
}

// Searche for ID in binary search tree
inline bool FileIO::search(const std::string &ID) const
{
    int dummy;
    if (bst.search(ID, dummy))
    {
        return true;
    }
    return false;
}

inline bool FileIO::del(const std::string &ID)
{
    if (!search(ID))
        return false;
    bst.remove(ID);
    hashTable->remove(ID);
    return true;
}

inline int FileIO::getHashTableSize()
{
    return hashTable->getSize();
}

inline float FileIO::getHashTableloadFactor()
{

    return hashTable->loadFactor();
}

inline int FileIO::getHashTableLongestChain()
{
    return hashTable->getLongestChain();
}

inline int FileIO::getHashTableEmptyBuckets()
{
    return hashTable->getEmptyBuckets();
}

inline void FileIO::inOrder(void visit(const std::string &ID))
{
    bst.inOrder(visit);
}

inline bool FileIO::is_ready()
{
    if (inFile.is_open())
        return true;
    else 
        return false;
}

inline Creature FileIO::getCreature(const std::string &ID) const
{
    int index;
    bst.search(ID, index);
    return hashTable->getCreature(ID, index);
}

// Implemented in ScreenManager.h, need to remove duplication
inline void FileIO::loadData()
{
    std::string line;

    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string releventYear;
        Record record;
        std::getline(ss, record.creatureID, ';');
        std::getline(ss, record.name, ';');
        std::getline(ss, record.category, ';');
        std::getline(ss, record.history, ';');
        std::getline(ss, record.habitat, ';');
        std::getline(ss, record.description, ';');
        std::getline(ss, releventYear, ';');
        record.releventYear = std::stoi(releventYear);

        Creature c = Creature(record.creatureID, record.name, record.category, record.history, record.habitat, record.description, record.releventYear);

        int idx = hashTable->insert(c);
        // only insert (key, idx) into BST
        bool ok = bst.insert(idx, c.getCreatureID());
        // If load factor > 0.75, rehash is required
        // if (hashTable->loadFactor() > 0.75)
        //     rehash();

        // For debugging
        // if ( idx > -1 && ok )
        //     cout << c.getCreatureID() << " is inserted successfully." << endl;
        // else
        //     cout << c.getCreatureID() << " is NOT inserted." << endl;
    }
}

inline void FileIO::saveData(const std::string &outFilename) const
{
    std::ofstream out(outFilename + ".txt");
    if (!out.is_open())
    {
        throw std::runtime_error("Unable to open output file: " + outFilename);
    }

    for (const Creature &c : hashTable->getAllCreatures())
    {
        out << c.getCreatureID() << ';'
            << c.getName() << ';'
            << c.getCategory() << ';'
            << c.getHistory() << ';'
            << c.getHabitat() << ';'
            << c.getDescription() << ';'
            << c.getReleventYear()
            << '\n';
    }
    out.close();
}

inline void FileIO::rehash()
{
    int newSize = nextPrime(tableSize * 2);
    HashTable *newTable = new HashTable(newSize);
    // traverse old table and re-insert each item
    for (const Creature &c : hashTable->getAllCreatures())
    {
        newTable->insert(c);
    }
    delete hashTable;
    hashTable = newTable;
    tableSize = newSize;
}

inline bool FileIO::isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

inline int FileIO::nextPrime(int n)
{
    while (!isPrime(n))
    {
        ++n;
    }
    return n;
}

#endif // FILEIO_H
