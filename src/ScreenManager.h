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

// External declaration of global FileIO defined in main
extern FileIO* globalFileIO;

namespace Color {
    constexpr const char* RESET   = "\033[0m";
    constexpr const char* RED     = "\033[31m";
    constexpr const char* GREEN   = "\033[32m";
    constexpr const char* YELLOW  = "\033[33m";
    constexpr const char* BLUE    = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN    = "\033[36m";
    constexpr const char* WHITE   = "\033[37m";
    constexpr const char* BOLD    = "\033[1m";
}
using namespace Color;

void printWelcome();
// int buildDataStructure(const string &filename, BinarySearchTree<string> &bst, HashTable &hashTable);
// void searchManager(const HashTable &hashTable);
// void insertManager(BinarySearchTree<string> &bst, HashTable &hashTable);
// void deleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
// void undoDeleteManager(BinarySearchTree<string> &bst, HashTable &hashTable, stack<Creature> &stk);
// void statisticsManager(const HashTable &hashTable);
void iDisplay(const string &item, int level);
void _hDisplay(const string &item, FileIO &file);
void hDisplay(const string &item);

void printWelcome()
{
    cout << BOLD << CYAN << "Main Menu:" << RESET << endl;
    cout << "  " << BOLD << GREEN   << "[L]" << RESET << " - Load data file" << endl;
    cout << "  " << BOLD << BLUE    << "[A]" << RESET << " - Add data" << endl;
    cout << "  " << BOLD << MAGENTA << "[S]" << RESET << " - Search data (Primary key: creature_id)" << endl;
    cout << "  " << BOLD << RED     << "[D]" << RESET << " - Delete data" << endl;
    cout << "  " << BOLD << YELLOW  << "[U]" << RESET << " - Undo delete" << endl;
    cout << "  " << BOLD << WHITE   << "[P]" << RESET << " - Print data" << endl;
    cout << "  " << BOLD << CYAN    << "[T]" << RESET << " - Show statistics" << endl;
    cout << "  " << BOLD << GREEN   << "[W]" << RESET << " - Write to file" << endl;
    cout << "  " << BOLD << BLUE    << "[H]" << RESET << " - Help" << endl;
    cout << "  " << BOLD << MAGENTA << "[Q]" << RESET << " - Quit" << endl;
}

int buildDataStructure(const string &filename, FileIO &file)
{
    cout << BOLD << CYAN << "Reading data from " << BOLD << YELLOW << "\"" << filename << "...\"" << RESET << endl;
    bool ok = file.init(filename);
    if (!ok)
    {
        cout << BOLD << RED << "Error opening the input file: " << BOLD << YELLOW << "\""<< filename << "\"" << RESET << endl;
        return -1;
    }
    return 1;
}

void searchManager(FileIO &file)
{
    cout << BOLD << CYAN << "Please enter a creature ID: " << RESET ;
    string targetID;
    getline(cin, targetID);

    bool found = file.search(targetID);
    if (found)
    {
        cout << BOLD << GREEN << "\nFound the creature " << BOLD << YELLOW << "\"" << targetID << "\":" << BOLD << CYAN << endl << endl;
        file.getCreature(targetID).vPrintCreature();
        cout << RESET;
    }
    else
    {
        cout << BOLD << RED << "Creature " << BOLD << YELLOW << "\"" << targetID << "\"" << BOLD << RED << " - not found" << RESET << endl;
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

    cout << BOLD << CYAN << "Please enter a creature ID: " << RESET ;
    getline(cin, creatureID);
    while (file.search(creatureID))
    {
        cout << BOLD << YELLOW << "\"" <<  creatureID << "\"" << BOLD << RED <<" already exists!" << RESET << endl;
        cout << BOLD << CYAN << "Please re-enter: "<< RESET;
        getline(cin, creatureID);
    }

    cout << BOLD << CYAN << "Please enter a creature name: " << RESET;
    getline(cin, name);

    cout << BOLD << CYAN << "Please enter a creature category: " << RESET;
    getline(cin, category);

    cout << BOLD << CYAN << "Please enter a creature history: " << RESET;
    getline(cin, history);

    cout << BOLD << CYAN << "Please enter a creature habitat: " << RESET;
    getline(cin, habitat);

    cout << BOLD << CYAN << "Please enter a creature description: " << RESET;
    getline(cin, description);

    cout << BOLD << CYAN << "Please enter a creature year: " << RESET;
    string year;
    getline(cin, year);
    releventYear = stoi(year);

    Creature newCreature(creatureID, name, category, history, habitat, description, releventYear);

    if (file.insert(newCreature))
    {
        cout << BOLD << GREEN << "New creature " << BOLD << YELLOW << creatureID << BOLD << GREEN << " was inserted!" << RESET << endl;
    }
    else
    {
        cout << BOLD << RED << "Cannot insert creature: " << BOLD << YELLOW << creatureID << RESET << endl;
        cout << BOLD << RED << "It might exist in the database already!" << RESET << endl;
    }
}

void deleteManager(FileIO &file, stack<Creature> &stk)
{
    cout << BOLD << CYAN << "Please enter a creature ID to " << BOLD << RED << "delete: " << RESET;
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
        cout << BOLD << RED << "Creature " << BOLD << YELLOW << targetID << BOLD << RED << "does NOT exist!" << RESET << endl;
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
        cout << BOLD << GREEN << "Creature " << BOLD << YELLOW << targetID << BOLD << GREEN << " was successfully deleted!" << RESET << endl;
        // For debugging
        // cout << "Top of stack: " << stk.top().getCreatureID() << endl;
    }
    else
    {
        cout << BOLD << RED << "CANNOT delete creature " << BOLD << YELLOW << targetID << BOLD << RED << "!" << RESET << endl;
        // // insert back if delete failed
        // int ind = hashTable.insert(temp); // no operation if duplicated
        // bool resInsert = bst.insert(ind, temp.getCreatureID());
    }
}

void undoDeleteManager(FileIO &file, stack<Creature> &stk)
{
    if (stk.empty())
    {
        cout << BOLD << RED << "Undo delete impossible!" << RESET << endl;
    }
    else
    {
        Creature temp = stk.top();

        if (file.insert(temp))
        {
            cout << BOLD << GREEN << "Undo delete succeeded!" << RESET << endl;
            stk.pop();
            // For debugging
            // cout << "There are " << stk.size() << " elements in stack." << endl;
        }
        else
        {
            cout << BOLD << RED << "CANNOT undo delete!" << RESET << endl;
        }
    }
}

void statisticsManager(FileIO &file)
{
    cout << BOLD << CYAN << "=========== Statistics in HashTable ===========\n";
    cout << BOLD << BLUE << "Number of data: " << BOLD << YELLOW << file.getHashTableSize() << endl;
    cout << BOLD << BLUE << "Load factor: " << BOLD << YELLOW << file.getHashTableloadFactor() << endl;
    cout << BOLD << BLUE << "Longest chain in hash table: " << BOLD << YELLOW << file.getHashTableLongestChain() << endl;
    cout << BOLD << BLUE << "Empty buckets: " << BOLD << YELLOW << file.getHashTableEmptyBuckets() << endl;
    cout << RESET << endl;
}

void iDisplay(const string &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
}

void hDisplay(const string &item)
{
    if (globalFileIO != nullptr)
    {
        _hDisplay(item, *globalFileIO);
    }
}

void _hDisplay(const string &item, FileIO &file)
{
    cout << BOLD << YELLOW << item << BOLD << BLUE << " | " 
         << BOLD << CYAN << file.getCreature(item).getName() << RESET << endl;
}