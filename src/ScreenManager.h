#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

#include "Creature.h"

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
int buildDataStructure( const string &filename )
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

        temp.ignore();              // to ignore space
        getline(temp, creatureID, ';');        // read from temp

        temp.ignore();             // to ignore space
        getline(temp, name, ';');  // stop reading at ';'

        temp.ignore();             // to ignore space
        getline(temp, category, ';');  // stop reading at ';'

        temp.ignore();             // to ignore space
        getline(temp, history, ';');  // stop reading at ';'

        temp.ignore();             // to ignore space
        getline(temp, habitat, ';');  // stop reading at ';'

        temp.ignore();             // to ignore space
        getline(temp, description , ';');  // stop reading at ';'
        
        temp.ignore();             // to ignore space
        temp >> releventYear;  // stop reading at ';'

        // create a Creature object and initialize it with data from file
        Creature aCreature(creatureID, name, category, history, habitat, description, releventYear);

        cout << endl;
        // bst.insert(aCreature); // TODO to implemnet
        // hashMap.insert(aCreature); // TODO to implemnet
    }
    return 1;

}