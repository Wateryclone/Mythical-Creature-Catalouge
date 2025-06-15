#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include "Creature.h"

using namespace std;

class HashTable {
private:
    struct HashEntry {
        string key;    // CreatureID (primary key)
        Creature creature;
        HashEntry(const string& k, const Creature& c);
    };

    vector<list<HashEntry>> table;
    int capacity;
    int size;

    int hashFunction(const string& key) const;
    void rehash();
    static bool isPrime(int n);
    static int nextPrime(int n);

public:
    HashTable(int initialCapacity = 101);

    // Insert a creature, returns the bucket index
    int insert(const Creature& creature);

    // Search by creatureID
    Creature* search(const string& creatureID);

    // Delete by creatureID
    bool remove(const string& creatureID);

    // Get all creatures in table order
    vector<Creature> getAllCreatures() const;

    // Statistics
    float loadFactor() const;
    int getLongestChain() const;
    int getEmptyBuckets() const;

    // For debugging
    void printTable() const;
};

#endif // HASHTABLE_H
