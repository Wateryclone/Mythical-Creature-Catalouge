#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stack>

using namespace std;

#include "Creature.h"
#include "BinarySearchTree.h"
#include "HashTable.h"

void printWelcome();
int buildDataStructure( const string &filename, BinarySearchTree<string> &bst, HashTable &hashTable );
void searchManager(const HashTable &hashTable);
void insertManager(BinarySearchTree<string> &bst, HashTable &hashTable);
void deleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
void undoDeleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
void statisticsManager(const HashTable &hashTable);
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

int buildDataStructure( const string &filename, BinarySearchTree<string> &bst, HashTable &hashTable )
{
    ifstream fin(filename);
    cout << "Reading data from \"" << filename << "...\"" << endl;

    if(!fin)
    {
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        return -1;
    }

    string line;
    while (getline(fin, line))
    {
        string creatureID; // Primary key eg. "FNKS-BD"
        string name; // eg. "Phoenix"
        string category; // eg. "Bird"
        string history; // famous legend or myth associated with the creature 
                //eg."A mythical bird that cyclically regenerates or is reborn from its ashes, known in Greek, Egyptian, and Persian traditions."
        string habitat; // eg. "Deserts and mountains"
        string description; // eg. "Fiery bird with radiant plumage, capable of resurrection through immolation and rebirth."
        int releventYear; // year of first mention in history
        
        stringstream temp(line);   // create temp with data from line

        getline(temp, creatureID, ';');        // read from temp
        getline(temp, name, ';');  // stop reading at ';'
        getline(temp, category, ';');  // stop reading at ';'
        getline(temp, history, ';');  // stop reading at ';'
        getline(temp, habitat, ';');  // stop reading at ';'
        getline(temp, description , ';');  // stop reading at ';'    
        temp >> releventYear;  // stop reading at ';'

        // create a Creature object and initialize it with data from file
        Creature aCreature(creatureID, name, category, history, habitat, description, releventYear);

        // For debugging
        // aCreature.vPrintCreature();
        
        int ind = hashTable.insert(aCreature);
        bool resInsert = bst.insert(ind, aCreature.getCreatureID());

        // For debugging
        // if ( ind > -1 && resInsert ) 
        //     cout << aCreature.getCreatureID() << " is inserted successfully." << endl;
        // else
        //     cout << aCreature.getCreatureID() << " is NOT inserted." << endl;
        
    }

    // For debugging
    // cout << "====== Built HashTable =====" << endl;
    // hashTable.printTable();    
    // cout << "====== Built BST =====" << endl;
    // bst.printTree(iDisplay);

    return 1;

}

void searchManager(const HashTable &hashTable)
{
    cout << "Please enter a creature ID: ";
    string targetID;
    getline(cin, targetID);

    const Creature* returnCreature = hashTable.search(targetID);
    if (returnCreature != nullptr)
    {
        cout << "\nFound the creature \"" << targetID << "\":" << endl << endl;
        returnCreature->vPrintCreature();
    }
    else
    {
        cout << "Creature \"" << targetID << "\" - not found" << endl;
    }
}

void insertManager(BinarySearchTree<string> &bst, HashTable &hashTable)
{
    string creatureID; // Primary key eg. "FNKS-BD"
    string name; // eg. "Phoenix"
    string category; // eg. "Bird"
    string history; // famous legend or myth associated with the creature 
            //eg."A mythical bird that cyclically regenerates or is reborn from its ashes, known in Greek, Egyptian, and Persian traditions."
    string habitat; // eg. "Deserts and mountains"
    string description; // eg. "Fiery bird with radiant plumage, capable of resurrection through immolation and rebirth."
    int releventYear; // year of first mention in history
    
    cout << "Please enter a creature ID: ";
    getline(cin, creatureID);

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

    int ind = hashTable.insert(newCreature);
    bool resInsert = bst.insert(ind, newCreature.getCreatureID());

    if ( resInsert )
    {
        cout << "New creature " << creatureID << " was inserted!" << endl;
    }
    else
    {
        cout << "Cannot insert creature: " << creatureID << endl;
        cout << "It might exist in the database already!" << endl;
    }

}

void deleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk)
{
    cout << "Please enter a creature ID to delete: ";
    string targetID;
    getline(cin, targetID);

    Creature temp;
    const Creature* returnCreature = hashTable.search(targetID);
    if (returnCreature == nullptr)
    {
        cout << "Creature " << targetID << "does NOT exist!" << endl;
        return;
    }
    else
    {
        temp.setCreatureID(returnCreature->getCreatureID());
        temp.setName(returnCreature->getName());
        temp.setHistory(returnCreature->getHistory());
        temp.setCategory(returnCreature->getCategory());
        temp.setHabitat(returnCreature->getHabitat());
        temp.setDescription(returnCreature->getDescription());
        temp.setReleventYear(returnCreature->getReleventYear());

        stk.push(temp);
    }

    bool resBST = bst.remove(targetID);
    bool resHashTable = hashTable.remove(targetID);
    if (resBST and resHashTable)
    {
        cout << "Creature " << targetID << " was successfully deleted!" << endl;
        // For debugging
        // cout << "Top of stack: " << stk.top().getCreatureID() << endl;
    }
    else
    {
        cout << "CANNOT delete creature " << targetID << "!" << endl;
        // insert back if delete failed
        int ind = hashTable.insert(temp); // no operation if duplicated
        bool resInsert = bst.insert(ind, temp.getCreatureID());
            
    }
}

void undoDeleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk)
{
    if ( stk.empty() )
    {
        cout << "Undo delete impossible!" << endl;
    }
    else
    {
        Creature temp = stk.top();

        int ind = hashTable.insert(temp);
        bool resInsert = bst.insert(ind, temp.getCreatureID());

        if (resInsert)
        {
            cout << "Undo delete succeeded!" << endl;
            stk.pop();
            //For debugging
            cout << "There are " << stk.size() << " elements in stack." << endl;
        }
        else
        {
            cout << "CANNOT undo delete!" << endl;
        }

    }
}

void statisticsManager(const HashTable &hashTable)
{
    cout << "===== Statistics in HashTable =====\n";
    cout << "Number of data: " << hashTable.getSize() << endl;
    cout << "Load factor: " << hashTable.loadFactor() << endl;
    cout << "Longest chain in hash table: " << hashTable.getLongestChain() << endl;
    cout << "Empty buckets: " << hashTable.getEmptyBuckets() << endl << endl; 
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