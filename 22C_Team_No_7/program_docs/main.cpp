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
using namespace Color;

int main()
{
    string filename = "Creatures.txt";
    string cmd;
    // BinarySearchTree<string> bst;
    // HashTable hashTable;
    stack<Creature> stk;
    FileIO file;
    cout << BOLD << RED << "\nWarning: " << RESET << "Data file not loaded. All commands except for loading file are currently unavailable.\n"
        << endl;
    printWelcome();
    cout << BOLD << CYAN << "User command: " << RESET;
    getline(cin, cmd);

    while (true)
    {
        for (char &c : cmd)
        {
            c = toupper(static_cast<unsigned char>(c));
        }

        bool ok = file.is_ready();
        if (!ok && (cmd[0] != 'Q'))
            cout << BOLD << RED << "\nWarning: " << RESET << "Data file not loaded. All commands except for loading file are currently unavailable.\n"
                << endl;

        // If the file is not open
        if (!ok)
        {
            switch (cmd[0])
            {
            case 'H':
            {
                printWelcome();
                break;
            }

            case 'L':
            {
                int loadSuc = -1;
                cout << BOLD << CYAN << "What is the input file's name? Press Enter for Default " << BOLD << YELLOW << "\"Creatures.txt\"" << BOLD << CYAN << ": " << RESET;
                do{
                    getline(cin, filename);
                    if (filename.empty())
                    filename = "Creatures.txt";

                    loadSuc = buildDataStructure(filename, file);

                    if (loadSuc == -1)
                    {
                        cout << BOLD << CYAN << "Reenter your data file or leave blank for default..." << RESET << endl;
                    }
                    else
                    {
                        cout << BOLD << GREEN << "File " << BOLD << YELLOW << filename << BOLD << GREEN << " was successfully loaded!" << RESET << endl;
                    }

                }while(loadSuc == -1);
                break;
            }

            case 'Q':
            {
                cout << BOLD << GREEN << "Thank you for visiting!" << RESET << endl;
                return 0;
            }

            default:
            {
                cout << BOLD << RED << "Invalid command " << BOLD << YELLOW << cmd << RESET << endl;
                printWelcome();
                break;
            }
            }
        }

        // If the file is open
        else
        {
            switch (cmd[0])
            {
            case 'H':
            {
                printWelcome();
                break;
            }
            case 'L':
            {
                cout << BOLD << CYAN << "What is the input file's name? Press Enter for Default " << BOLD << YELLOW << "\"Creatures.txt\"" << BOLD << CYAN << ": " << RESET;
                getline(cin, filename);

                if (filename.empty())
                    filename = "Creatures.txt";

                int loadSuc = buildDataStructure(filename, file);

                if (loadSuc == -1)
                {
                    cout << BOLD << CYAN << "Reenter your data file..." << RESET << endl;
                    cmd = "L";
                }
                else
                {
                    cout << BOLD << GREEN << "File " << BOLD << YELLOW << filename << BOLD << GREEN << " was successfully loaded!" << RESET << endl;
                }
                break;
            }
            case 'S':
            {
                cout << BOLD << CYAN << "=========== Searching ===========" << RESET << endl;
                searchManager(file);

                break;
            }
            case 'A':
            {
                cout << BOLD << CYAN << "=========== Adding a new creature ===========" << RESET << endl;
                insertManager(file);
                break;
            }

            case 'D':
            {
                cout << BOLD << CYAN << "=========== Deleting a creature ===========" << RESET << endl;
                deleteManager(file, stk);

                break;
            }
            case 'U':
            {
                cout << BOLD << CYAN << "=========== Undo deleting ===========" << RESET << endl;
                undoDeleteManager(file, stk);
                break;
            }

            case 'P':
            {
                cout << BOLD << CYAN << "=========== All stored data in order ===========" << RESET << endl;
                file.inOrder(hDisplay);
                cout << endl;
                break;
            }
            case 'T':
            {
                statisticsManager(file);

                break;
            }

            case 'W':
            {
                cout << BOLD << CYAN << "Saving data to file: " << RESET;
                string outputFileName;
                getline(cin, outputFileName);

                // -------------TODO: place holder for file save data-------------
                file.saveData(outputFileName);
                // ---------------- End placeholder---------------

                cout << BOLD << CYAN << "Data is saved in \"" << BOLD << YELLOW << outputFileName << ".txt" << BOLD << CYAN << "\"" << RESET << endl;

                while (!stk.empty())
                {
                    stk.pop();
                }
                assert(stk.empty());
                break;
            }

            case 'Q':
            {
                cout << BOLD << GREEN << "Thank you for visiting!" << RESET << endl;
                return 0;
            }

            case 'N':
            {
                cout << BOLD << GREEN << "Print indented tree!" << RESET << endl;
                cout << "\n===== BST indented tree ===== " << endl;
                file.indentedTree(iDisplay);
                break;
            }

            default:
            {
                cout << BOLD << RED << "Invalid command " << BOLD << YELLOW << cmd << RESET << endl;
                printWelcome();
                break;
            }
            }
        }

        cout << BOLD << CYAN << "\nUser command: " << RESET;
        getline(cin, cmd);
    }
}
