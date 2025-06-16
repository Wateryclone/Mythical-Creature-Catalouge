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
// Placeholder for hash table header
// #include "HashTable.h"

struct Record {
    std::string creatureID;
    std::string name;
    std::string category;
    std::string history;
    std::string habitat;
    std::string description;
    int releventYear;
};

class FileIO {
public:
    explicit FileIO(const std::string& filename);
    ~FileIO();

    // Load from file into BST and hash table PS: Only binary trees are loaded for now
    void loadData();

    // Save hash‐table contents in table order back to a file
    void saveData(const std::string& outFilename) const;

private:
    std::string                fileName;
    std::ifstream              inFile;
    BinarySearchTree<Creature> bst;
    // HashTable<Creature>*      hashTable;     // placeholder for HashTable class
    int                        tableSize;

    // Helpers for sizing / rehashing
    static bool isPrime(int n);
    static int  nextPrime(int n);
    void        rehash();

    // Disable copy semantics
    FileIO(const FileIO&) = delete;
    FileIO& operator=(const FileIO&) = delete;
};

// Implementation

inline FileIO::FileIO(const std::string& filename)
  : fileName(filename),
    inFile(filename),
    bst(),
    // hashTable(nullptr), // placeholder for HashTable class
    tableSize(0)
{
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open input file: " + filename);
    }

    // Count lines
    int lines = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        ++lines;
    }

    // rewind to beginning
    inFile.clear();
    inFile.seekg(0);

    // Determine initial hash size = next prime ≥ 2 * lines
    tableSize = nextPrime(lines * 2);

    // construct hash table with size
    // hashTable = new HashTable<Creature>(tableSize); // placeholder for HashTable class

    // Load data
    loadData();
}

inline FileIO::~FileIO()
{
    // if (hashTable) {
    //     delete hashTable;
    // }
    if (inFile.is_open()) {
        inFile.close();
    }
}

// TODO implemented in ScreenManager.h, need to remove duplication
inline void FileIO::loadData()
{
    std::string line;
    
    while (std::getline(inFile, line)) {
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

        // ---------- placeholder for HashTable class ----------

        // int idx = hashTable.insert(c);        

        // only insert (key, idx) into BST
        // bst.insert(std::make_pair(c.getCreatureID(), idx));

        // If load factor > 0.75, rehash is required
        // if (hashTable.loadFactor() > 0.75)
        //     rehash();

        // ---------- end placeholder ----------
    }
}

inline void FileIO::saveData(const std::string& outFilename) const
{
    std::ofstream out(outFilename);
    if (!out.is_open()) {
        throw std::runtime_error("Unable to open output file: " + outFilename);
    }

    // ---------- placeholder for HashTable class ----------
    // e.g. auto items = hashTable->itemsInTableOrder();
    // for (const Creature& c : items) { … }

    // for (/* each Creature c from hashTable in table-order */) {

    //     const Creature& c = /* hashTable item placeholder */;

    //     out  << c.getCreatureID() << ';'
    //          << c.getName()          << ';'
    //          << c.getCategory()      << ';'
    //          << c.getHistory()       << ';'
    //          << c.getHabitat()       << ';'
    //          << c.getDescription()   << ';'
    //          << c.getReleventYear()
    //          << c.getReleventYear()
    //          << '\n';
    // }
    // ---------- end placeholder ----------

    out.close();
}

inline void FileIO::rehash()
{
    int newSize = nextPrime(tableSize * 2);
    // ---------- placeholder for HashTable class ----------
    // HashTable<Creature>* newTable = new HashTable<Creature>(newSize);

    // traverse old table and re-insert each item
    // for (/* each Creature c from hashTable in table-order */) {
    //     newTable->insert(c);
    // }

    // delete hashTable;
    // hashTable = newTable;
    // ---------- end placeholder ----------
    tableSize = newSize;
}

inline bool FileIO::isPrime(int n)
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

inline int FileIO::nextPrime(int n)
{
    while (!isPrime(n)) {
        ++n;
    }
    return n;
}

#endif // FILEIO_H
