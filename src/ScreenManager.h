#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stack>

#include "FileIO.h"

using namespace std;

#include "Creature.h"
#include "BinarySearchTree.h"
#include "HashTable.h"

void printWelcome();
// int buildDataStructure(const string &filename, BinarySearchTree<string> &bst, HashTable &hashTable);
// void searchManager(const HashTable &hashTable);
// void insertManager(BinarySearchTree<string> &bst, HashTable &hashTable);
// void deleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
// void undoDeleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
// void statisticsManager(const HashTable &hashTable);
void iDisplay(const string &item, int level);
void hDisplay(const string &item);

void printWelcome()
{
    string indentation(2, ' ');

    cout << "Main Menu:" << endl;
    cout << indentation << "[L] - Load data file" << endl;
    cout << indentation << "[A] - Add data" << endl;
    cout << indentation << "[S] - Search data (Primary key: creature_id)" << endl;
    cout << indentation << "[D] - Delete data" << endl;
    cout << indentation << "[U] - Undo delete" << endl;
    cout << indentation << "[P] - Print data" << endl;
    cout << indentation << "[T] - Show statistics" << endl;
    cout << indentation << "[W] - Write to file" << endl;
    cout << indentation << "[H] - Help" << endl;
    cout << indentation << "[Q] - Quit" << endl;
}

int buildDataStructure(const string &filename, FileIO &file)
{
    cout << "Reading data from \"" << filename << "...\"" << endl;
    bool ok = file.init(filename);
    if (!ok)
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        return -1;
    }
    return 1;
}

void searchManager(FileIO &file)
{
    cout << "Please enter a creature ID: ";
    string targetID;
    getline(cin, targetID);

    bool found = file.search(targetID);
    if (found)
    {
        cout << "\nFound the creature \"" << targetID << "\":" << endl
             << endl;
        file.getCreature(targetID).vPrintCreature();
    }
    else
    {
        cout << "Creature \"" << targetID << "\" - not found" << endl;
    }
}

void insertManager(FileIO &file)
{
    string creatureID;  // Primary key eg. "FNKS-BD"
    string name;        // eg. "Phoenix"
    string category;    // eg. "Bird"
    string history;     // famous legend or myth associated with the creature
                        // eg."A mythical bird that cyclically regenerates or is reborn from its ashes, known in Greek, Egyptian, and Persian traditions."
    string habitat;     // eg. "Deserts and mountains"
    string description; // eg. "Fiery bird with radiant plumage, capable of resurrection through immolation and rebirth."
    int releventYear;   // year of first mention in history

    cout << "Please enter a creature ID: ";
    getline(cin, creatureID);
    while (file.search(creatureID))
    {
        cout << "\"" + creatureID + "\" already exists!" << endl;
        cout << "Please re-enter: ";
        getline(cin, creatureID);
    }

    cout << "Please enter a creature name: ";
    getline(cin, name);

    cout << "Please enter a creature category: ";
    getline(cin, category);

    cout << "Please enter a creature history: ";
    getline(cin, history);

    cout << "Please enter a creature habitat: ";
    getline(cin, habitat);

    cout << "Please enter a creature description: ";
    getline(cin, description);

    cout << "Please enter a creature year: ";
    string year;
    getline(cin, year);
    releventYear = stoi(year);

    Creature newCreature(creatureID, name, category, history, habitat, description, releventYear);

    if (file.insert(newCreature))
    {
        cout << "New creature " << creatureID << " was inserted!" << endl;
    }
    else
    {
        cout << "Cannot insert creature: " << creatureID << endl;
        cout << "It might exist in the database already!" << endl;
    }
}

void deleteManager(FileIO &file, stack<Creature> &stk)
{
    cout << "Please enter a creature ID to delete: ";
    string targetID;
    getline(cin, targetID);

    Creature temp;
    // const Creature *returnCreature = hashTable.search(targetID);
    Creature returnCreature;
    if (file.search(targetID))
    {
        returnCreature = file.getCreature(targetID);
    }
    else
    {
        cout << "Creature " << targetID << "does NOT exist!" << endl;
        return;
    }

    temp = returnCreature;

    // temp.setCreatureID(returnCreature->getCreatureID());
    // temp.setName(returnCreature->getName());
    // temp.setHistory(returnCreature->getHistory());
    // temp.setCategory(returnCreature->getCategory());
    // temp.setHabitat(returnCreature->getHabitat());
    // temp.setDescription(returnCreature->getDescription());
    // temp.setReleventYear(returnCreature->getReleventYear());

    stk.push(temp);

    if (file.del(targetID))
    {
        cout << "Creature " << targetID << " was successfully deleted!" << endl;
        // For debugging
        // cout << "Top of stack: " << stk.top().getCreatureID() << endl;
    }
    else
    {
        cout << "CANNOT delete creature " << targetID << "!" << endl;
        // // insert back if delete failed
        // int ind = hashTable.insert(temp); // no operation if duplicated
        // bool resInsert = bst.insert(ind, temp.getCreatureID());
    }
}

void undoDeleteManager(FileIO &file, stack<Creature> &stk)
{
    if (stk.empty())
    {
        cout << "Undo delete impossible!" << endl;
    }
    else
    {
        Creature temp = stk.top();

        if (file.insert(temp))
        {
            cout << "Undo delete succeeded!" << endl;
            stk.pop();
            // For debugging
            cout << "There are " << stk.size() << " elements in stack." << endl;
        }
        else
        {
            cout << "CANNOT undo delete!" << endl;
        }
    }
}

void statisticsManager(FileIO &file)
{
    cout << "===== Statistics in HashTable =====\n";
    cout << "Number of data: " << file.getHashTableSize() << endl;
    cout << "Load factor: " << file.getHashTableloadFactor() << endl;
    cout << "Longest chain in hash table: " << file.getHashTableLongestChain() << endl;
    cout << "Empty buckets: " << file.getHashTableEmptyBuckets() << endl;
    cout << endl;
}

void iDisplay(const string &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
}

void hDisplay(const string &item)
{
    cout << "(" << item << ") ";
}