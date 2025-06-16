#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Creature.h"
#include "ScreenManager.h"

using namespace std;

int main()
{

    string filename = "Creatures.txt";
    string cmd;
    BinarySearchTree<string> bst;
    HashTable hashTable;

    printWelcome();
    cout << "User command: ";
    getline(cin, cmd);

    while (true)
    {

        for (char& c : cmd) 
        {
            c = toupper(static_cast<unsigned char>(c));
        }

        if (cmd == "H")
        {
            printWelcome();
        } 
        else if (cmd == "L")
        {
            cout << "What is the input file's name? 'Y' for Default: Creatures.txt ";
            getline(cin, filename);
    
            if ( filename == "Y" or filename == "y")
                filename = "Creatures.txt";
            
            int loadSuc = buildDataStructure(filename, bst, hashTable);

            if ( loadSuc == -1)
            {
                cout << "Reenter your data file..." << endl;
                cmd = "L";
            }
            else
            {
                cout << "File " << filename << " was successfully loaded!" << endl;
            }
        }
        else if (cmd == "S")
        {
            cout << "===== Searching =====" << endl;
            searchManager(hashTable);

        }
        else if (cmd == "A")
        {
            cout << "===== Adding a new creature =====" << endl;
            insertManager(bst, hashTable);

        }
        else if (cmd == "P")
        {
            cout << "===== All stored data in order =====" << endl;
            bst.inOrder(hDisplay);
            cout << endl;

            // For debugging: hidden indented tree
            // cout << "\n===== BST indented tree ===== " << endl;
            // bst.printTree(iDisplay);
        }
        else if (cmd == "T")
        {
            statisticsManager(hashTable);
        }
        else if (cmd == "Q")
        {
            cout << "Thank you for visiting!" << endl;
            return 0;
        }
        else
        {
            cout << "Invalid command " << cmd << endl;
            printWelcome();
        }

        cout << "\nUser command: ";
        getline(cin, cmd);
    }
}