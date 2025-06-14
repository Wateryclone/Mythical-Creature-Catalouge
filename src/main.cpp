#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

// #include "BinaryTree.h"
#include "Creature.h"
#include "ScreenManager.h"


using namespace std;

// void buildCreatureList(HashTable<Creature> &, BinaryTree<Creature> &, string<Creature> &);
// void runMainMenu(HashTable<Creature> &, BinaryTree<creature> &);
// void printGoodbye();

int main()
{

    string filename = "Creatures.txt";
    string cmd;
    // BinaryTree<Creature> Ctree;
    // HashTable<Creature> Ctable;

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
            
            int loadSuc = buildDataStructure(filename);

            if ( loadSuc == -1)
            {
                cout << "Reenter your data file..." << endl;
                cmd = "L";
            }
        }
        else if (cmd == "Q")
        {
            cout << "Thank you for visiting!" << endl;
            return 0;
        }
    }

    // buildCreatureList(Ctable, Ctree, filename);
    // runMainMenu(Ctable, Ctree);
    // printGoodbye();
    // cout << "Enter the name of the file containing the creature data: ";
    // getline(cin, filename);

}

