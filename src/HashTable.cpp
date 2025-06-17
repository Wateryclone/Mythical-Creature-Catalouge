#include "hashtable.h"
#include <algorithm>
#include <iostream>

using namespace std;

// HashEntry constructor
HashTable::HashEntry::HashEntry(const string& k, const Creature& c)
    : key(k), creature(c) {
}

// HashTable constructor
HashTable::HashTable(int initialCapacity)
    : capacity(nextPrime(initialCapacity)), size(0) {
    table.resize(capacity);
}

// Hash function implementation
int HashTable::hashFunction(const string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % capacity;
}

// Insert implementation
int HashTable::insert(const Creature& creature) {
    // float lf = loadFactor();
    // if (lf > 0.75) {
    //     rehash();
    // }

    string key = creature.getCreatureID();
    int index = hashFunction(key);

    // Check for duplicates
    for (auto& entry : table[index]) {
        if (entry.key == key) {
            entry.creature = creature; // Update existing
            return index;
        }
    }

    table[index].emplace_back(key, creature);
    size++;
    return index;
}

// Search implementation
const Creature* HashTable::search(const string& creatureID) const {
    int index = hashFunction(creatureID);
    for (auto& entry : table[index]) {
        if (entry.key == creatureID) {
            return &entry.creature;
        }
    }
    return nullptr;
}

Creature HashTable::getCreature(const string &creatureID, const int &idx)
{
    for (auto& entry : table[idx]) {
        if (entry.key == creatureID) {
            return entry.creature;
        }
    }
}

// Remove implementation
bool HashTable::remove(const string& creatureID) {
    int index = hashFunction(creatureID);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == creatureID) {
            table[index].erase(it);
            size--;
            return true;
        }
    }
    return false;
}

// Get all creatures implementation
vector<Creature> HashTable::getAllCreatures() const {
    vector<Creature> creatures;
    for (const auto& bucket : table) {
        for (const auto& entry : bucket) {
            creatures.push_back(entry.creature);
        }
    }
    return creatures;
}

// Rehash implementation
void HashTable::rehash() {
    int newCapacity = nextPrime(capacity * 2);
    vector<list<HashEntry>> newTable(newCapacity);

    for (auto& bucket : table) {
        for (auto& entry : bucket) {
            int newIndex = hashFunction(entry.key);
            newTable[newIndex].push_back(entry);
        }
    }

    table = move(newTable);
    capacity = newCapacity;
}

// Prime number utilities
bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int HashTable::nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

// Statistics implementations
float HashTable::loadFactor() const {
    return static_cast<float>(size) / capacity;
}

int HashTable::getLongestChain() const {
    int max = 0;
    for (const auto& bucket : table) {
        if (bucket.size() > max) max = bucket.size();
    }
    return max;
}

int HashTable::getEmptyBuckets() const {
    int count = 0;
    for (const auto& bucket : table) {
        if (bucket.empty()) count++;
    }
    return count;
}

// Debug print implementation
void HashTable::printTable() const {
    for (int i = 0; i < capacity; ++i) {
        cout << "Bucket " << i << ": ";
        for (const auto& entry : table[i]) {
            cout << "[" << entry.key << "] -> ";
        }
        cout << "NULL\n";
    }
}
