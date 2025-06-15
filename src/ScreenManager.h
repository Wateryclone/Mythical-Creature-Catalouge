#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

#include "Creature.h"
#include "BinarySearchTree.h"
#include "HashTable.h"

void iDisplay(const string &item, int level);

void printWelcome()
{
    string indentation(2, ' ');

    cout << "Main Menu:" << endl;
    cout << indentation << "[L] - Load data file" << endl;
    cout << indentation << "[A] - Add data" << endl;
    cout << indentation << "[S] - Search data (Primary key: creature_id)" << endl;
    cout << indentation << "[D] - Delete data" << endl;
    cout << indentation << "[P] - Print data" << endl;
    cout << indentation << "[T] - Show statistics" << endl;
    cout << indentation << "[W] - Write to file" << endl;
    cout << indentation << "[H] - Help" << endl;
    cout << indentation << "[Q] - Quit" << endl;

}

// void buildDataStructure(const string &filename, BinarySearchTree<Creature> &bst, HashMap<Creature> &hashMap)
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

        aCreature.vPrintCreature();
        
        int ind = hashTable.insert(aCreature); // TODO to implemnet
        bool resInsert = bst.insert(ind, aCreature.getCreatureID()); // TODO to implemnet

        // For debugging
        if ( ind > -1 && resInsert ) 
            cout << aCreature.getCreatureID() << " is inserted successfully." << endl;
        else
            cout << aCreature.getCreatureID() << " is NOT inserted." << endl;
        
    }

    // For debugging
    cout << "====== Built HashTable =====" << endl;
    hashTable.printTable();    
    cout << "====== Built BST =====" << endl;
    bst.printTree(iDisplay);

    return 1;

}

void iDisplay(const string &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
    
}