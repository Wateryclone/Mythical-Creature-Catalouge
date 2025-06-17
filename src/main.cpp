#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stack>
#include <cassert>

#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Creature.h"
#include "ScreenManager.h"

using namespace std;

int main()
{

    string filename = "Creatures.txt";
    string cmd;
    // BinarySearchTree<string> bst;
    // HashTable hashTable;
    stack<Creature> stk;
    FileIO file;
    cout << "Warning: Data file not loaded. All commands except for loading file are currently unavailable." << endl;
    printWelcome();
    cout << "User command: ";
    getline(cin, cmd);

    while (true)
    {
        bool ok = file.is_ready();
        if (!ok)
            cout << "Warning: Data file not loaded. All commands except for loading a file are currently unavailable." << endl;

        for (char &c : cmd)
        {
            c = toupper(static_cast<unsigned char>(c));
        }

        // If the file is not open
        if (!ok)
        {
            if (cmd == "H")
            {
                printWelcome();
            }
            else if (cmd == "L")
            {
                cout << "What is the input file's name? Press Enter for Default \"Creatures.txt\": ";
                getline(cin, filename);

                if (filename.empty())
                    filename = "Creatures.txt";

                int loadSuc = buildDataStructure(filename, file);

                if (loadSuc == -1)
                {
                    cout << "Reenter your data file..." << endl;
                    cmd = "L";
                }
                else
                {
                    cout << "File " << filename << " was successfully loaded!" << endl;
                }
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
        }
        // If the file is open
        else
        {
            if (cmd == "H")
            {
                printWelcome();
            }
            else if (cmd == "L")
            {
                cout << "What is the input file's name? Press Enter for Default Creatures.txt ";
                getline(cin, filename);

                if (filename.empty())
                    filename = "Creatures.txt";

                int loadSuc = buildDataStructure(filename, file);

                if (loadSuc == -1)
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
                searchManager(file);
            }
            else if (cmd == "A")
            {
                cout << "===== Adding a new creature =====" << endl;
                insertManager(file);
            }
            else if (cmd == "D")
            {
                cout << "===== Deleting a creature =====" << endl;
                deleteManager(file, stk);
            }
            else if (cmd == "U")
            {
                cout << "===== Undo deleting =====" << endl;
                undoDeleteManager(file, stk);
            }
            else if (cmd == "P")
            {
                cout << "===== All stored data in order =====" << endl;
                file.inOrder(hDisplay);
                cout << endl;

                // For debugging: hidden indented tree
                // cout << "\n===== BST indented tree ===== " << endl;
                // bst.printTree(iDisplay);
            }
            else if (cmd == "T")
            {
                statisticsManager(file);
            }
            else if (cmd == "W")
            {
                cout << "===== Saving data to file: ";
                string outputFileName;
                getline(cin, outputFileName);

                // -------------TODO: place holder for file save data-------------
                file.saveData(outputFileName);
                // ---------------- End placeholder---------------

                cout << "Data is saved in \"" << outputFileName << ".txt" << "\"" << endl;

                while (!stk.empty())
                {
                    stk.pop();
                }
                assert(stk.empty());
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
        }

        cout << "\nUser command: ";
        getline(cin, cmd);
    }
}